/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <Atom/ImageProcessing/ImageObject.h>
#include <Atom/ImageProcessing/ImageProcessingBus.h>
#include <Atom/RPI.Edit/Common/AssetUtils.h>
#include <AtomToolsFramework/Util/Util.h>
#include <AzCore/IO/ByteContainerStream.h>
#include <AzCore/IO/SystemFile.h>
#include <AzCore/Jobs/JobFunction.h>
#include <AzCore/Settings/SettingsRegistry.h>
#include <AzCore/Settings/SettingsRegistryMergeUtils.h>
#include <AzCore/StringFunc/StringFunc.h>
#include <AzCore/Utils/Utils.h>
#include <AzFramework/API/ApplicationAPI.h>
#include <AzQtComponents/Components/Widgets/FileDialog.h>
#include <AzToolsFramework/API/EditorAssetSystemAPI.h>
#include <AzToolsFramework/AssetBrowser/AssetBrowserBus.h>
#include <AzToolsFramework/AssetBrowser/AssetBrowserEntry.h>
#include <AzToolsFramework/AssetBrowser/AssetSelectionModel.h>

AZ_PUSH_DISABLE_WARNING(4251 4800, "-Wunknown-warning-option") // disable warnings spawned by QT
#include <QApplication>
#include <QMessageBox>
#include <QProcess>
AZ_POP_DISABLE_WARNING

namespace AtomToolsFramework
{
    void LoadImageAsync(const AZStd::string& path, LoadImageAsyncCallback callback)
    {
        AZ::Job* job = AZ::CreateJobFunction(
            [path, callback]()
            {
                ImageProcessingAtom::IImageObjectPtr imageObject;
                ImageProcessingAtom::ImageProcessingRequestBus::BroadcastResult(
                    imageObject, &ImageProcessingAtom::ImageProcessingRequests::LoadImagePreview, path);

                if (imageObject)
                {
                    AZ::u8* imageBuf = nullptr;
                    AZ::u32 pitch = 0;
                    AZ::u32 mip = 0;
                    imageObject->GetImagePointer(mip, imageBuf, pitch);
                    const AZ::u32 width = imageObject->GetWidth(mip);
                    const AZ::u32 height = imageObject->GetHeight(mip);

                    QImage image(imageBuf, width, height, pitch, QImage::Format_RGBA8888);

                    if (callback)
                    {
                        callback(image);
                    }
                }
            },
            true);
        job->Start();
    }

    QString GetDisplayNameFromPath(const QString& path)
    {
        QFileInfo fileInfo(path);
        QString fileName = fileInfo.baseName();
        fileName.replace(QRegExp("[^a-zA-Z\\d\\s]"), " ");
        QStringList fileNameParts = fileName.split(' ', Qt::SkipEmptyParts);
        for (QString& part : fileNameParts)
        {
            part.replace(0, 1, part[0].toUpper());
        }
        return fileNameParts.join(" ");
    }

    QFileInfo GetSaveFileInfo(const QString& initialPath)
    {
        const QFileInfo initialFileInfo(initialPath);
        const QString initialExt(initialFileInfo.completeSuffix());

        // Instead of just passing in the absolute file path, we pass in the absolute folder path and the base name to prevent the file
        // dialog from displaying multiple extensions when the extension contains a "."
        const QFileInfo selectedFileInfo(AzQtComponents::FileDialog::GetSaveFileName(
            QApplication::activeWindow(),
            "Save File",
            initialFileInfo.absolutePath() +
            AZ_CORRECT_FILESYSTEM_SEPARATOR_STRING +
            initialFileInfo.baseName(),
            QString("Files (*.%1)").arg(initialExt)));

        if (selectedFileInfo.absoluteFilePath().isEmpty())
        {
            // Cancelled operation
            return QFileInfo();
        }

        if (!selectedFileInfo.absoluteFilePath().endsWith(initialExt))
        {
            QMessageBox::critical(QApplication::activeWindow(), "Error", QString("File name must have .%1 extension.").arg(initialExt));
            return QFileInfo();
        }

        // Reconstructing the file info from the absolute path and expected extension to compensate for an issue with the save file
        // dialog adding the extension multiple times if it contains "." like *.lightingpreset.azasset
        return QFileInfo(selectedFileInfo.absolutePath() + AZ_CORRECT_FILESYSTEM_SEPARATOR_STRING + selectedFileInfo.baseName() + "." + initialExt);
    }

    QFileInfo GetOpenFileInfo(const AZStd::vector<AZ::Data::AssetType>& assetTypes)
    {
        using namespace AZ::Data;
        using namespace AzToolsFramework::AssetBrowser;

        // [GFX TODO] Should this just be an open file dialog filtered to supported source data extensions?
        auto selection = AssetSelectionModel::AssetTypesSelection(assetTypes);

        // [GFX TODO] This is functional but UI is not as designed
        AssetBrowserComponentRequestBus::Broadcast(&AssetBrowserComponentRequests::PickAssets, selection, QApplication::activeWindow());
        if (!selection.IsValid())
        {
            return QFileInfo();
        }

        auto entry = selection.GetResult();
        const SourceAssetBrowserEntry* sourceEntry = azrtti_cast<const SourceAssetBrowserEntry*>(entry);
        if (!sourceEntry)
        {
            const ProductAssetBrowserEntry* productEntry = azrtti_cast<const ProductAssetBrowserEntry*>(entry);
            if (productEntry)
            {
                sourceEntry = azrtti_cast<const SourceAssetBrowserEntry*>(productEntry->GetParent());
            }
        }

        if (!sourceEntry)
        {
            return QFileInfo();
        }

        return QFileInfo(sourceEntry->GetFullPath().c_str());
    }

    QFileInfo GetUniqueFileInfo(const QString& initialPath)
    {
        int counter = 0;
        QFileInfo fileInfo = initialPath;
        const QString extension = "." + fileInfo.completeSuffix();
        const QString basePathAndName = fileInfo.absoluteFilePath().left(fileInfo.absoluteFilePath().size() - extension.size());
        while (fileInfo.exists())
        {
            fileInfo = QString("%1_%2%3").arg(basePathAndName).arg(++counter).arg(extension);
        }
        return fileInfo;
    }

    QFileInfo GetDuplicationFileInfo(const QString& initialPath)
    {
        const QFileInfo initialFileInfo(initialPath);
        const QString initialExt(initialFileInfo.completeSuffix());

        const QFileInfo duplicateFileInfo(AzQtComponents::FileDialog::GetSaveFileName(
            QApplication::activeWindow(),
            "Duplicate File",
            GetUniqueFileInfo(initialPath).absoluteFilePath(),
            QString("Files (*.%1)").arg(initialExt)));

        if (duplicateFileInfo == initialFileInfo)
        {
            // Cancelled operation or selected same path
            return QFileInfo();
        }

        if (duplicateFileInfo.absoluteFilePath().isEmpty())
        {
            // Cancelled operation or selected same path
            return QFileInfo();
        }

        if (!duplicateFileInfo.absoluteFilePath().endsWith(initialExt))
        {
            QMessageBox::critical(QApplication::activeWindow(), "Error", QString("File name must have .%1 extension.").arg(initialExt));
            return QFileInfo();
        }

        return duplicateFileInfo;
    }

    bool LaunchTool(const QString& baseName, const QStringList& arguments)
    {
        AZ::IO::FixedMaxPath engineRoot = AZ::Utils::GetEnginePath();
        AZ_Assert(!engineRoot.empty(), "Cannot query Engine Path");

        AZ::IO::FixedMaxPath launchPath =
            AZ::IO::FixedMaxPath(AZ::Utils::GetExecutableDirectory()) / (baseName + AZ_TRAIT_OS_EXECUTABLE_EXTENSION).toUtf8().constData();

        return QProcess::startDetached(launchPath.c_str(), arguments, engineRoot.c_str());
    }

    AZStd::string GetExteralReferencePath(
        const AZStd::string& exportPath, const AZStd::string& referencePath, const bool relativeToExportPath)
    {
        if (referencePath.empty())
        {
            return {};
        }

        if (!relativeToExportPath)
        {
            AZStd::string watchFolder;
            AZ::Data::AssetInfo assetInfo;
            bool sourceInfoFound = false;
            AzToolsFramework::AssetSystemRequestBus::BroadcastResult(
                sourceInfoFound, &AzToolsFramework::AssetSystemRequestBus::Events::GetSourceInfoBySourcePath, referencePath.c_str(),
                assetInfo, watchFolder);
            if (sourceInfoFound)
            {
                return assetInfo.m_relativePath;
            }
        }

        AZ::IO::BasicPath<AZStd::string> exportFolder(exportPath);
        exportFolder.RemoveFilename();
        return AZ::IO::PathView(referencePath).LexicallyRelative(exportFolder).StringAsPosix();
    }

    bool SaveSettingsToFile(const AZ::IO::FixedMaxPath& savePath, const AZStd::vector<AZStd::string>& filters)
    {
        auto registry = AZ::SettingsRegistry::Get();
        if (registry == nullptr)
        {
            AZ_Warning("AtomToolsFramework", false, "Unable to access global settings registry.");
            return false;
        }

        AZ::SettingsRegistryMergeUtils::DumperSettings dumperSettings;
        dumperSettings.m_prettifyOutput = true;
        dumperSettings.m_includeFilter = [filters](AZStd::string_view path)
        {
            for (const auto& filter : filters)
            {
                if (filter.starts_with(path.substr(0, filter.size())))
                {
                    return true;
                }
            }
            return false;
        };

        AZStd::string stringBuffer;
        AZ::IO::ByteContainerStream stringStream(&stringBuffer);
        if (!AZ::SettingsRegistryMergeUtils::DumpSettingsRegistryToStream(*registry, "", stringStream, dumperSettings))
        {
            AZ_Warning("AtomToolsFramework", false, R"(Unable to save changes to the registry file at "%s"\n)", savePath.c_str());
            return false;
        }

        if (stringBuffer.empty())
        {
            return false;
        }

        bool saved = false;
        constexpr auto configurationMode =
            AZ::IO::SystemFile::SF_OPEN_CREATE | AZ::IO::SystemFile::SF_OPEN_CREATE_PATH | AZ::IO::SystemFile::SF_OPEN_WRITE_ONLY;
        if (AZ::IO::SystemFile outputFile; outputFile.Open(savePath.c_str(), configurationMode))
        {
            saved = outputFile.Write(stringBuffer.data(), stringBuffer.size()) == stringBuffer.size();
        }

        AZ_Warning("AtomToolsFramework", saved, R"(Unable to save registry file to path "%s"\n)", savePath.c_str());
        return saved;
    }
} // namespace AtomToolsFramework
