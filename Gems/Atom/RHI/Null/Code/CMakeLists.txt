#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

o3de_pal_dir(pal_include_dir ${CMAKE_CURRENT_LIST_DIR}/Include/Platform/${PAL_PLATFORM_NAME} ${gem_restricted_path} ${gem_path} ${gem_parent_relative_path})
o3de_pal_dir(pal_source_dir ${CMAKE_CURRENT_LIST_DIR}/Source/Platform/${PAL_PLATFORM_NAME} ${gem_restricted_path} ${gem_path} ${gem_parent_relative_path})


ly_add_target(
    NAME Atom_RHI_Null.Reflect STATIC
    NAMESPACE Gem
    FILES_CMAKE
        atom_rhi_null_reflect_common_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
            ${pal_include_dir}
    BUILD_DEPENDENCIES
        PRIVATE
            AZ::AzCore
            Gem::Atom_RHI.Reflect
)

ly_add_target(
    NAME Atom_RHI_Null.Private.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        atom_rhi_null_private_common_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            .
            Source
            ${pal_source_dir}
        PUBLIC
            Include
            ${pal_include_dir}
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
            AZ::AzFramework
            AZ::AtomCore
            Gem::Atom_RHI.Public
)

ly_add_target(
    NAME Atom_RHI_Null.Private ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        atom_rhi_null_private_common_shared_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            .
            Source
            ${pal_source_dir}
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::Atom_RHI_Null.Reflect
            Gem::Atom_RHI_Null.Private.Static
)

if (PAL_TRAIT_BUILD_HOST_TOOLS)

    ly_add_target(
        NAME Atom_RHI_Null.Builders.Static STATIC
        NAMESPACE Gem
        FILES_CMAKE
            atom_rhi_null_builders_common_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                .
                Source
                ${pal_source_dir}
            PUBLIC
                Include
        BUILD_DEPENDENCIES
            PRIVATE
                AZ::AssetBuilderSDK
                Gem::Atom_RHI.Edit
                Gem::Atom_RHI.Reflect
                Gem::Atom_RHI_Null.Reflect
    )

   ly_add_target(
        NAME Atom_RHI_Null.Builders GEM_MODULE
        NAMESPACE Gem
        FILES_CMAKE
            atom_rhi_null_builders_shared_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
        BUILD_DEPENDENCIES
            PRIVATE
                AZ::AssetBuilderSDK
                Gem::Atom_RHI.Edit
                Gem::Atom_RHI.Reflect
                Gem::Atom_RHI_Null.Builders.Static
    )
endif()
