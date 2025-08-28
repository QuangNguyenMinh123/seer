cmake_minimum_required(VERSION 3.5.0)

project(seergdb VERSION 2.6.0 LANGUAGES CXX)

set(PROJECT_NAME seergdb)

if(NOT DEFINED QTVERSION)
    set(QTVERSION "QT6" CACHE STRING "" FORCE)
endif()

if(${QTVERSION} STREQUAL "QT6")
    message("-- Compile with QT6")
elseif(${QTVERSION} STREQUAL "QT5")
    message("-- Compile with QT5")
else()
    message(FATAL_ERROR "-- Use -DQTVERSION=QT5|QT6 not \"${QTVERSION}\"")
endif()

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_PREFIX_PATH ${QTDIR})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(${QTVERSION} STREQUAL "QT6")
    find_package(Qt6 COMPONENTS REQUIRED Core)
    find_package(Qt6 COMPONENTS REQUIRED Gui)
    find_package(Qt6 COMPONENTS REQUIRED Widgets)
    find_package(Qt6 COMPONENTS REQUIRED PrintSupport)
    find_package(Qt6 COMPONENTS REQUIRED Charts)
    find_package(Qt6 COMPONENTS REQUIRED Svg)
    find_package(Qt6 COMPONENTS REQUIRED OpenGL)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

elseif(${QTVERSION} STREQUAL "QT5")
    find_package(Qt5 COMPONENTS REQUIRED Core)
    find_package(Qt5 COMPONENTS REQUIRED Gui)
    find_package(Qt5 COMPONENTS REQUIRED Widgets)
    find_package(Qt5 COMPONENTS REQUIRED PrintSupport)
    find_package(Qt5 COMPONENTS REQUIRED Charts)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(HEADER_FILES
    ../src/GdbMonitor.h
    ../src/SeerArrayVisualizerWidget.h
    ../src/SeerEditorWidgetSource.h
    ../src/SeerPlainTextEdit.h
    ../src/SeerStackFramesBrowserWidget.h
    ../src/QAnsiTextEdit.h
    ../src/SeerArrayWidget.h
    ../src/SeerExecutableFilterProxyModel.h
    ../src/SeerPrintpointCreateDialog.h
    ../src/SeerStackLocalsBrowserWidget.h
    ../src/QClearLineEdit.h
    ../src/SeerAsmWidget.h
    ../src/SeerFunctionBrowserWidget.h
    ../src/SeerPrintpointsBrowserWidget.h
    ../src/SeerStackManagerWidget.h
    ../src/QColorButton.h
    ../src/SeerAssemblyConfigPage.h
    ../src/SeerGdbConfigPage.h
    ../src/SeerProgressIndicator.h
    ../src/SeerStaticBrowserWidget.h
    ../src/QColorSwatch.h
    ../src/SeerAssemblyPreferenceDialog.h
    ../src/SeerGdbLogWidget.h
    ../src/SeerRegisterEditValueDialog.h
    ../src/SeerStructVisualizerWidget.h
    ../src/QDetachTabWidget.h
    ../src/SeerBreakpointCreateDialog.h
    ../src/SeerGdbWidget.h
    ../src/SeerRegisterProfileDialog.h
    ../src/SeerThreadFramesBrowserWidget.h
    ../src/QEditDelegate.h
    ../src/SeerBreakpointsBrowserWidget.h
    ../src/SeerHelpPageDialog.h
    ../src/SeerRegisterTreeWidgetItem.h
    ../src/SeerThreadGroupsBrowserWidget.h
    ../src/QHContainerWidget.h
    ../src/SeerCatchpointCreateDialog.h
    ../src/SeerHexWidget.h
    ../src/SeerRegisterValuesBrowserWidget.h
    ../src/SeerThreadIdsBrowserWidget.h
    ../src/QHistoryLineEdit.h
    ../src/SeerCatchpointsBrowserWidget.h
    ../src/SeerHighlighterSettings.h
    ../src/SeerRRConfigPage.h
    ../src/SeerThreadManagerWidget.h
    ../src/QImageViewer.h
    ../src/SeerCheckpointsBrowserWidget.h
    ../src/SeerHistoryLineEdit.h
    ../src/SeerRunStatusIndicator.h
    ../src/SeerTildeLogWidget.h
    ../src/QIndexTreeWidget.h
    ../src/SeerCloseSourceDialog.h
    ../src/SeerImageVisualizerWidget.h
    ../src/SeerSeerConfigPage.h
    ../src/SeerTypeBrowserWidget.h
    ../src/QProcessInfo.h
    ../src/SeerConfigDialog.h
    ../src/SeerKeysConfigPage.h
    ../src/SeerSeerLogWidget.h
    ../src/SeerUtl.h
    ../src/QProcessInfoWidget.h
    ../src/SeerConsoleWidget.h
    ../src/SeerKeySettings.h
    ../src/SeerSkipBrowserWidget.h
    ../src/SeerVariableLoggerBrowserWidget.h
    ../src/QProgressIndicator.h
    ../src/SeerCppSourceHighlighter.h
    ../src/SeerLibraryBrowserWidget.h
    ../src/SeerSkipCreateDialog.h
    ../src/SeerVariableManagerWidget.h
    ../src/QStringPair.h
    ../src/SeerCxxSourceHighlighter.h
    ../src/SeerLogWidget.h
    ../src/SeerSlashProcDialog.h
    ../src/SeerVariableTrackerBrowserWidget.h
    ../src/QZoomChart.h
    ../src/SeerDebugDialog.h
    ../src/SeerMainWindow.h
    ../src/SeerSourceBrowserWidget.h
    ../src/SeerVarVisualizerWidget.h
    ../src/QZoomChartView.h
    ../src/SeerDirectoryFilterProxyModel.h
    ../src/SeerMatrixVisualizerWidget.h
    ../src/SeerSourceConfigPage.h
    ../src/SeerWatchpointCreateDialog.h
    ../src/SeerAboutDialog.h
    ../src/SeerEditorConfigPage.h
    ../src/SeerMatrixWidget.h
    ../src/SeerSourceSymbolLibraryManagerWidget.h
    ../src/SeerWatchpointsBrowserWidget.h
    ../src/SeerAdaExceptionsBrowserWidget.h
    ../src/SeerEditorManagerEntry.h
    ../src/SeerMemoryVisualizerWidget.h
    ../src/SeerStackArgumentsBrowserWidget.h
    ../src/SeerAdaTasksBrowserWidget.h
    ../src/SeerEditorManagerWidget.h
    ../src/SeerMessagesBrowserWidget.h
    ../src/SeerStackDumpBrowserWidget.h
    ../src/SeerArgumentsDialog.h
    ../src/SeerEditorWidgetAssembly.h
    ../src/SeerMessagesDialog.h
    ../src/SeerStackDumpSettingsDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_QColorButton.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerCatchpointsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerHexWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerRegisterValuesBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackManagerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_QHContainerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerCheckpointsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerImageVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerRRConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStaticBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_QProcessInfoWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerCloseSourceDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerKeysConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSeerConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStructVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAboutDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerConfigDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerLibraryBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSkipBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerThreadFramesBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAdaExceptionsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerConsoleWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerLogWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSkipCreateDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerThreadGroupsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAdaTasksBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerDebugDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerMainWindow.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSlashProcDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerThreadIdsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerArgumentsDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerEditorConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerMatrixVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSourceBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerThreadManagerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerArrayVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerEditorManagerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerMemoryVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSourceConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerTypeBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAsmWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerEditorWidgetAssembly.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerMessagesBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerSourceSymbolLibraryManagerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerVariableLoggerBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAssemblyConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerEditorWidgetSource.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerMessagesDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackArgumentsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerVariableManagerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerAssemblyPreferenceDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerFunctionBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerPrintpointCreateDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackDumpBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerVariableTrackerBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerBreakpointCreateDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerGdbConfigPage.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerPrintpointsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackDumpSettingsDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerVarVisualizerWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerBreakpointsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerGdbWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerRegisterEditValueDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackFramesBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerWatchpointCreateDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerCatchpointCreateDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerHelpPageDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerRegisterProfileDialog.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerStackLocalsBrowserWidget.h
    # ../build-DebugSeer-Desktop-Debug/seergdb_autogen/include/ui_SeerWatchpointsBrowserWidget.h
    )

set(SOURCE_FILES
    ../src/GdbMonitor.cpp
    ../src/SeerArrayWidget.cpp
    ../src/SeerFunctionBrowserWidget.cpp
    ../src/SeerPrintpointCreateDialog.cpp
    ../src/SeerStackLocalsBrowserWidget.cpp
    ../src/QAnsiTextEdit.cpp
    ../src/SeerAsmWidget.cpp
    ../src/SeerGdbConfigPage.cpp
    ../src/SeerPrintpointsBrowserWidget.cpp
    ../src/SeerStackManagerWidget.cpp
    ../src/QClearLineEdit.cpp
    ../src/SeerAssemblyConfigPage.cpp
    ../src/seergdb.cpp
    ../src/SeerProgressIndicator.cpp
    ../src/SeerStaticBrowserWidget.cpp
    ../src/QColorButton.cpp
    ../src/SeerAssemblyPreferenceDialog.cpp
    ../src/SeerGdbLogWidget.cpp
    ../src/SeerRegisterEditValueDialog.cpp
    ../src/SeerStructVisualizerWidget.cpp
    ../src/QColorSwatch.cpp
    ../src/SeerBreakpointCreateDialog.cpp
    ../src/SeerGdbWidget.cpp
    ../src/SeerRegisterProfileDialog.cpp
    ../src/SeerThreadFramesBrowserWidget.cpp
    ../src/QDetachTabWidget.cpp
    ../src/SeerBreakpointsBrowserWidget.cpp
    ../src/SeerHelpPageDialog.cpp
    ../src/SeerRegisterTreeWidgetItem.cpp
    ../src/SeerThreadGroupsBrowserWidget.cpp
    ../src/QEditDelegate.cpp
    ../src/SeerCatchpointCreateDialog.cpp
    ../src/SeerHexWidget.cpp
    ../src/SeerRegisterValuesBrowserWidget.cpp
    ../src/SeerThreadIdsBrowserWidget.cpp
    ../src/QHContainerWidget.cpp
    ../src/SeerCatchpointsBrowserWidget.cpp
    ../src/SeerHighlighterSettings.cpp
    ../src/SeerRRConfigPage.cpp
    ../src/SeerThreadManagerWidget.cpp
    ../src/QHistoryLineEdit.cpp
    ../src/SeerCheckpointsBrowserWidget.cpp
    ../src/SeerHistoryLineEdit.cpp
    ../src/SeerRunStatusIndicator.cpp
    ../src/SeerTildeLogWidget.cpp
    ../src/QImageViewer.cpp
    ../src/SeerCloseSourceDialog.cpp
    ../src/SeerImageVisualizerWidget.cpp
    ../src/SeerSeerConfigPage.cpp
    ../src/SeerTypeBrowserWidget.cpp
    ../src/QIndexTreeWidget.cpp
    ../src/SeerConfigDialog.cpp
    ../src/SeerKeysConfigPage.cpp
    ../src/SeerSeerLogWidget.cpp
    ../src/SeerUtl.cpp
    ../src/QProcessInfo.cpp
    ../src/SeerConsoleWidget.cpp
    ../src/SeerKeySettings.cpp
    ../src/SeerSkipBrowserWidget.cpp
    ../src/QProcessInfoWidget.cpp
    ../src/SeerCppSourceHighlighter.cpp
    ../src/SeerLibraryBrowserWidget.cpp
    ../src/SeerSkipCreateDialog.cpp
    ../src/SeerVariableLoggerBrowserWidget.cpp
    ../src/QProgressIndicator.cpp
    ../src/SeerCxxSourceHighlighter.cpp
    ../src/SeerLogWidget.cpp
    ../src/SeerSlashProcDialog.cpp
    ../src/SeerVariableManagerWidget.cpp
    ../src/QZoomChart.cpp
    ../src/SeerDebugDialog.cpp
    ../src/SeerMainWindow.cpp
    ../src/SeerSourceBrowserWidget.cpp
    ../src/SeerVariableTrackerBrowserWidget.cpp
    ../src/QZoomChartView.cpp
    ../src/SeerEditorConfigPage.cpp
    ../src/SeerMatrixVisualizerWidget.cpp
    ../src/SeerSourceConfigPage.cpp
    ../src/SeerVarVisualizerWidget.cpp
    ../src/SeerAboutDialog.cpp
    ../src/SeerEditorManagerWidget.cpp
    ../src/SeerMatrixWidget.cpp
    ../src/SeerSourceSymbolLibraryManagerWidget.cpp
    ../src/SeerWatchpointCreateDialog.cpp
    ../src/SeerAdaExceptionsBrowserWidget.cpp
    ../src/SeerEditorWidgetAssemblyAreas.cpp
    ../src/SeerMemoryVisualizerWidget.cpp
    ../src/SeerStackArgumentsBrowserWidget.cpp
    ../src/SeerWatchpointsBrowserWidget.cpp
    ../src/SeerAdaTasksBrowserWidget.cpp
    ../src/SeerEditorWidgetAssembly.cpp
    ../src/SeerMessagesBrowserWidget.cpp
    ../src/SeerStackDumpBrowserWidget.cpp
    ../src/SeerArgumentsDialog.cpp
    ../src/SeerEditorWidgetSourceAreas.cpp
    ../src/SeerMessagesDialog.cpp
    ../src/SeerStackDumpSettingsDialog.cpp
    ../src/SeerArrayVisualizerWidget.cpp
    ../src/SeerEditorWidgetSource.cpp
    ../src/SeerPlainTextEdit.cpp
    ../src/SeerStackFramesBrowserWidget.cpp
    )

if(${QTVERSION} STREQUAL "QT6")
    qt6_add_resources(HEADER_FILES  )
elseif(${QTVERSION} STREQUAL "QT5")
    qt5_add_resources(HEADER_FILES  )
endif()

# Set non-Debug build as GUI application.
# Debug build remains consle application.
if(NOT CMAKE_BUILD_TYPE MATCHES Debug) #Release, RelWithDebInfo and MinSizeRel
    if(WIN32) # Check if we are on Windows
        set(SYSTEM_TYPE WIN32)
    endif()
    message("-- System type is " ${SYSTEM_TYPE})
endif()

# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
    add_compile_options(-Wall -Wextra -Wunused-result -pedantic)   # -Werror -Wdeprecated-copy
endif()

add_definitions(-DQT_DISABLE_DEPRECATED_UP_TO=0x060300)

add_executable(${PROJECT_NAME} ${SYSTEM_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(seergdb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(${QTVERSION} STREQUAL "QT6")
    target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Gui Qt6::Core Qt6::PrintSupport Qt6::Charts Qt6::Svg Qt6::OpenGL)
elseif(${QTVERSION} STREQUAL "QT5")
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Gui Qt5::Core Qt5::PrintSupport Qt5::Charts)
endif()

