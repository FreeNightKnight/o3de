#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/AtomToolsFramework/Application/AtomToolsApplication.h
    Include/AtomToolsFramework/AssetBrowser/AtomToolsAssetBrowser.h
    Include/AtomToolsFramework/AssetBrowser/AtomToolsAssetBrowserInteractions.h
    Include/AtomToolsFramework/AssetSelection/AssetSelectionComboBox.h
    Include/AtomToolsFramework/AssetSelection/AssetSelectionGrid.h
    Include/AtomToolsFramework/CreateDocumentDialog/CreateDocumentDialog.h
    Include/AtomToolsFramework/Communication/LocalServer.h
    Include/AtomToolsFramework/Communication/LocalSocket.h
    Include/AtomToolsFramework/Debug/TraceRecorder.h
    Include/AtomToolsFramework/Document/AtomToolsDocument.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentInspector.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentSystem.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentApplication.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentMainWindow.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentSystemRequestBus.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentNotificationBus.h
    Include/AtomToolsFramework/Document/AtomToolsDocumentRequestBus.h
    Include/AtomToolsFramework/DynamicProperty/DynamicProperty.h
    Include/AtomToolsFramework/DynamicProperty/DynamicPropertyGroup.h
    Include/AtomToolsFramework/Inspector/InspectorWidget.h
    Include/AtomToolsFramework/Inspector/InspectorRequestBus.h
    Include/AtomToolsFramework/Inspector/InspectorNotificationBus.h
    Include/AtomToolsFramework/Inspector/InspectorGroupWidget.h
    Include/AtomToolsFramework/Inspector/InspectorGroupHeaderWidget.h
    Include/AtomToolsFramework/Inspector/InspectorPropertyGroupWidget.h
    Include/AtomToolsFramework/PerformanceMonitor/PerformanceMetrics.h
    Include/AtomToolsFramework/PerformanceMonitor/PerformanceMonitorRequestBus.h
    Include/AtomToolsFramework/Util/MaterialPropertyUtil.h
    Include/AtomToolsFramework/Util/Util.h
    Include/AtomToolsFramework/Viewport/RenderViewportWidget.h
    Include/AtomToolsFramework/Viewport/ViewportInteractionImpl.h
    Include/AtomToolsFramework/Viewport/ModularViewportCameraController.h
    Include/AtomToolsFramework/Viewport/ModularViewportCameraControllerRequestBus.h
    Include/AtomToolsFramework/Window/AtomToolsMainWindow.h
    Include/AtomToolsFramework/Window/AtomToolsMainWindowRequestBus.h
    Include/AtomToolsFramework/Window/AtomToolsMainWindowNotificationBus.h
    Source/Application/AtomToolsApplication.cpp
    Source/AssetBrowser/AtomToolsAssetBrowser.cpp
    Source/AssetBrowser/AtomToolsAssetBrowser.qrc
    Source/AssetBrowser/AtomToolsAssetBrowser.ui
    Source/AssetBrowser/AtomToolsAssetBrowserInteractions.cpp
    Source/AssetSelection/AssetSelectionComboBox.cpp
    Source/AssetSelection/AssetSelectionGrid.cpp
    Source/AssetSelection/AssetSelectionGrid.ui
    Source/CreateDocumentDialog/CreateDocumentDialog.cpp
    Source/Communication/LocalServer.cpp
    Source/Communication/LocalSocket.cpp
    Source/Debug/TraceRecorder.cpp
    Source/Document/AtomToolsDocument.cpp
    Source/Document/AtomToolsDocumentInspector.cpp
    Source/Document/AtomToolsDocumentApplication.cpp
    Source/Document/AtomToolsDocumentMainWindow.cpp
    Source/Document/AtomToolsDocumentSystem.cpp
    Source/DynamicProperty/DynamicProperty.cpp
    Source/DynamicProperty/DynamicPropertyGroup.cpp
    Source/Inspector/InspectorWidget.cpp
    Source/Inspector/InspectorWidget.ui
    Source/Inspector/InspectorWidget.qrc
    Source/Inspector/InspectorGroupWidget.cpp
    Source/Inspector/InspectorGroupHeaderWidget.cpp
    Source/Inspector/InspectorPropertyGroupWidget.cpp
    Source/PerformanceMonitor/PerformanceMonitorSystemComponent.cpp
    Source/PerformanceMonitor/PerformanceMonitorSystemComponent.h
    Source/Util/MaterialPropertyUtil.cpp
    Source/Util/Util.cpp
    Source/Viewport/RenderViewportWidget.cpp
    Source/Viewport/ModularViewportCameraController.cpp
    Source/Viewport/ViewportInteractionImpl.cpp
    Source/Window/AtomToolsMainWindow.cpp
    Source/Window/AtomToolsMainWindowSystemComponent.cpp
    Source/Window/AtomToolsMainWindowSystemComponent.h
    Include/AtomToolsFramework/PreviewRenderer/PreviewContent.h
    Include/AtomToolsFramework/PreviewRenderer/PreviewRendererCaptureRequest.h
    Include/AtomToolsFramework/PreviewRenderer/PreviewRendererInterface.h
    Include/AtomToolsFramework/PreviewRenderer/PreviewRendererSystemRequestBus.h
    Include/AtomToolsFramework/PreviewRenderer/PreviewerFeatureProcessorProviderBus.h
    Source/PreviewRenderer/PreviewRenderer.cpp
    Source/PreviewRenderer/PreviewRenderer.h
    Source/PreviewRenderer/PreviewRendererState.h
    Source/PreviewRenderer/PreviewRendererIdleState.cpp
    Source/PreviewRenderer/PreviewRendererIdleState.h
    Source/PreviewRenderer/PreviewRendererLoadState.cpp
    Source/PreviewRenderer/PreviewRendererLoadState.h
    Source/PreviewRenderer/PreviewRendererCaptureState.cpp
    Source/PreviewRenderer/PreviewRendererCaptureState.h
    Source/PreviewRenderer/PreviewRendererSystemComponent.cpp
    Source/PreviewRenderer/PreviewRendererSystemComponent.h
    Source/Viewport/ViewportInputBehaviorController/ViewportInputBehaviorController.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/ViewportInputBehaviorController.h
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/ViewportInputBehaviorControllerInterface.h
    Source/Viewport/ViewportInputBehaviorController/ViewportInputBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/ViewportInputBehavior.h
    Source/Viewport/ViewportInputBehaviorController/DollyCameraBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/DollyCameraBehavior.h
    Source/Viewport/ViewportInputBehaviorController/IdleBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/IdleBehavior.h
    Source/Viewport/ViewportInputBehaviorController/MoveCameraBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/MoveCameraBehavior.h
    Source/Viewport/ViewportInputBehaviorController/PanCameraBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/PanCameraBehavior.h
    Source/Viewport/ViewportInputBehaviorController/OrbitCameraBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/OrbitCameraBehavior.h
    Source/Viewport/ViewportInputBehaviorController/RotateEnvironmentBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/RotateEnvironmentBehavior.h
    Source/Viewport/ViewportInputBehaviorController/RotateModelBehavior.cpp
    Include/AtomToolsFramework/Viewport/ViewportInputBehaviorController/RotateModelBehavior.h
)