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
    ../src/QProcessInfo.h
    ../src/QProcessInfoWidget.h
    ../src/QProgressIndicator.h
    ../src/QColorButton.h
    ../src/QColorSwatch.h
    ../src/QDetachTabWidget.h
    ../src/QZoomChartView.h
    ../src/QZoomChart.h
    ../src/QClearLineEdit.h
    ../src/QIndexTreeWidget.h
    ../src/QStringPair.h
    ../src/QHistoryLineEdit.h
    ../src/QEditDelegate.h
    ../src/QHContainerWidget.h
    ../src/QImageViewer.h
    ../src/QAnsiTextEdit.h
    ../src/SeerUtl.h
    ../src/SeerArgumentsDialog.h
    ../src/SeerBreakpointCreateDialog.h
    ../src/SeerMessagesBrowserWidget.h
    ../src/SeerBreakpointsBrowserWidget.h
    ../src/SeerCatchpointCreateDialog.h
    ../src/SeerCatchpointsBrowserWidget.h
    ../src/SeerPrintpointCreateDialog.h
    ../src/SeerPrintpointsBrowserWidget.h
    ../src/SeerCheckpointsBrowserWidget.h
    ../src/SeerSeerLogWidget.h
    ../src/SeerConsoleWidget.h
    ../src/SeerConfigDialog.h
    ../src/SeerGdbConfigPage.h
    ../src/SeerRRConfigPage.h
    ../src/SeerEditorConfigPage.h
    ../src/SeerSourceConfigPage.h
    ../src/SeerAssemblyConfigPage.h
    ../src/SeerSeerConfigPage.h
    ../src/SeerKeysConfigPage.h
    ../src/SeerCloseSourceDialog.h
    ../src/SeerDebugDialog.h
    ../src/SeerDirectoryFilterProxyModel.h
    ../src/SeerEditorManagerEntry.h
    ../src/SeerEditorManagerWidget.h
    ../src/SeerEditorWidgetSource.h
    ../src/SeerEditorWidgetAssembly.h
    ../src/SeerExecutableFilterProxyModel.h
    ../src/SeerGdbWidget.h
    ../src/SeerHexWidget.h
    ../src/SeerAsmWidget.h
    ../src/SeerArrayWidget.h
    ../src/SeerMarixWidget.h
    ../src/SeerLogWidget.h
    ../src/SeerMainWindow.h
    ../src/SeerArrayVisualizerWidget.h
    ../src/SeerMatrixVisualizerWidget.h
    ../src/SeerMemoryVisualizerWidget.h
    ../src/SeerStructVisualizerWidget.h
    ../src/SeerVarVisualizerWidget.h
    ../src/SeerImageVisualizerWidget.h
    ../src/SeerRegisterValuesBrowserWidget.h
    ../src/SeerRegisterEditValueDialog.h
    ../src/SeerRegisterProfileDialog.h
    ../src/SeerRegisterTreeWidgetItem.h
    ../src/SeerRunStatusIndicator.h
    ../src/SeerLibraryBrowserWidget.h
    ../src/SeerSourceBrowserWidget.h
    ../src/SeerFunctionBrowserWidget.h
    ../src/SeerTypeBrowserWidget.h
    ../src/SeerStaticBrowserWidget.h
    ../src/SeerSkipBrowserWidget.h
    ../src/SeerSkipCreateDialog.h
    ../src/SeerSourceSymbolLibraryManagerWidget.h
    ../src/SeerStackArgumentsBrowserWidget.h
    ../src/SeerStackFramesBrowserWidget.h
    ../src/SeerStackLocalsBrowserWidget.h
    ../src/SeerStackDumpBrowserWidget.h
    ../src/SeerStackDumpSettingsDialog.h
    ../src/SeerStackManagerWidget.h
    ../src/SeerThreadFramesBrowserWidget.h
    ../src/SeerThreadIdsBrowserWidget.h
    ../src/SeerThreadGroupsBrowserWidget.h
    ../src/SeerAdaTasksBrowserWidget.h
    ../src/SeerAdaExceptionsBrowserWidget.h
    ../src/SeerThreadManagerWidget.h
    ../src/SeerGdbLogWidget.h
    ../src/SeerTildeLogWidget.h
    ../src/SeerVariableLoggerBrowserWidget.h
    ../src/SeerVariableManagerWidget.h
    ../src/SeerVariableTrackerBrowserWidget.h
    ../src/SeerWatchpointCreateDialog.h
    ../src/SeerWatchpointsBrowserWidget.h
    ../src/SeerCppSourceHighlighter.h
    ../src/SeerAboutDialog.h
    ../src/SeerSlashProcDialog.h
    ../src/SeerHighlighterSettings.h
    ../src/SeerKeySettings.h
    ../src/SeerPlainTextEdit.h
    ../src/SeerHelpPageDialog.h
    ../src/SeerProgressIndicator.h
    ../src/SeerMessagesDialog.h
    ../src/SeerAssemblyPreferenceDialog.h
    ../src/SeerHistoryLineEdit.h
    )

set(SOURCE_FILES
    ../src/GdbMonitor.cpp
    ../src/QProcessInfo.cpp
    ../src/QProcessInfoWidget.cpp
    ../src/QProgressIndicator.cpp
    ../src/QColorButton.cpp
    ../src/QColorSwatch.cpp
    ../src/QDetachTabWidget.cpp
    ../src/QZoomChartView.cpp
    ../src/QZoomChart.cpp
    ../src/QClearLineEdit.cpp
    ../src/QIndexTreeWidget.cpp
    ../src/QHistoryLineEdit.cpp
    ../src/QEditDelegate.cpp
    ../src/QHContainerWidget.cpp
    ../src/QImageViewer.cpp
    ../src/QAnsiTextEdit.cpp
    ../src/SeerUtl.cpp
    ../src/SeerArgumentsDialog.cpp
    ../src/SeerBreakpointCreateDialog.cpp
    ../src/SeerMessagesBrowserWidget.cpp
    ../src/SeerBreakpointsBrowserWidget.cpp
    ../src/SeerCatchpointCreateDialog.cpp
    ../src/SeerCatchpointsBrowserWidget.cpp
    ../src/SeerPrintpointCreateDialog.cpp
    ../src/SeerPrintpointsBrowserWidget.cpp
    ../src/SeerCheckpointsBrowserWidget.cpp
    ../src/SeerSeerLogWidget.cpp
    ../src/SeerConsoleWidget.cpp
    ../src/SeerConfigDialog.cpp
    ../src/SeerGdbConfigPage.cpp
    ../src/SeerRRConfigPage.cpp
    ../src/SeerEditorConfigPage.cpp
    ../src/SeerSourceConfigPage.cpp
    ../src/SeerAssemblyConfigPage.cpp
    ../src/SeerSeerConfigPage.cpp
    ../src/SeerKeysConfigPage.cpp
    ../src/SeerCloseSourceDialog.cpp
    ../src/SeerDebugDialog.cpp
    ../src/SeerEditorManagerWidget.cpp
    ../src/SeerEditorWidgetSource.cpp
    ../src/SeerEditorWidgetSourceAreas.cpp
    ../src/SeerEditorWidgetAssembly.cpp
    ../src/SeerEditorWidgetAssemblyAreas.cpp
    ../src/SeerGdbWidget.cpp
    ../src/SeerHexWidget.cpp
    ../src/SeerAsmWidget.cpp
    ../src/SeerArrayWidget.cpp
    ../src/SeerMatrixWidget.cpp
    ../src/SeerLogWidget.cpp
    ../src/SeerMainWindow.cpp
    ../src/SeerArrayVisualizerWidget.cpp
    ../src/SeerMatrixVisualizerWidget.cpp
    ../src/SeerMemoryVisualizerWidget.cpp
    ../src/SeerStructVisualizerWidget.cpp
    ../src/SeerVarVisualizerWidget.cpp
    ../src/SeerImageVisualizerWidget.cpp
    ../src/SeerRegisterValuesBrowserWidget.cpp
    ../src/SeerRegisterEditValueDialog.cpp
    ../src/SeerRegisterProfileDialog.cpp
    ../src/SeerRegisterTreeWidgetItem.cpp
    ../src/SeerRunStatusIndicator.cpp
    ../src/SeerLibraryBrowserWidget.cpp
    ../src/SeerSourceBrowserWidget.cpp
    ../src/SeerFunctionBrowserWidget.cpp
    ../src/SeerTypeBrowserWidget.cpp
    ../src/SeerStaticBrowserWidget.cpp
    ../src/SeerSkipBrowserWidget.cpp
    ../src/SeerSkipCreateDialog.cpp
    ../src/SeerSourceSymbolLibraryManagerWidget.cpp
    ../src/SeerStackArgumentsBrowserWidget.cpp
    ../src/SeerStackFramesBrowserWidget.cpp
    ../src/SeerStackLocalsBrowserWidget.cpp
    ../src/SeerStackDumpBrowserWidget.cpp
    ../src/SeerStackDumpSettingsDialog.cpp
    ../src/SeerStackManagerWidget.cpp
    ../src/SeerThreadFramesBrowserWidget.cpp
    ../src/SeerThreadIdsBrowserWidget.cpp
    ../src/SeerThreadGroupsBrowserWidget.cpp
    ../src/SeerAdaTasksBrowserWidget.cpp
    ../src/SeerAdaExceptionsBrowserWidget.cpp
    ../src/SeerThreadManagerWidget.cpp
    ../src/SeerGdbLogWidget.cpp
    ../src/SeerTildeLogWidget.cpp
    ../src/SeerVariableLoggerBrowserWidget.cpp
    ../src/SeerVariableManagerWidget.cpp
    ../src/SeerVariableTrackerBrowserWidget.cpp
    ../src/SeerWatchpointCreateDialog.cpp
    ../src/SeerWatchpointsBrowserWidget.cpp
    ../src/SeerCppSourceHighlighter.cpp
    ../src/SeerAboutDialog.cpp
    ../src/SeerSlashProcDialog.cpp
    ../src/SeerHighlighterSettings.cpp
    ../src/SeerKeySettings.cpp
    ../src/SeerPlainTextEdit.cpp
    ../src/SeerHelpPageDialog.cpp
    ../src/SeerProgressIndicator.cpp
    ../src/SeerMessagesDialog.cpp
    ../src/SeerAssemblyPreferenceDialog.cpp
    ../src/SeerHistoryLineEdit.cpp
    ../src/seergdb.cpp
    )

if(${QTVERSION} STREQUAL "QT6")
    qt6_add_resources(SOURCE_FILES ../src/resource.qrc ../src/resources/qdarkstyle/dark/darkstyle.qrc ../src/resources/qdarkstyle/light/lightstyle.qrc)
elseif(${QTVERSION} STREQUAL "QT5")
    qt5_add_resources(SOURCE_FILES ../src/resource.qrc ../src/resources/qdarkstyle/dark/darkstyle.qrc ../src/resources/qdarkstyle/light/lightstyle.qrc)
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

add_executable(${PROJECT_NAME} ${SYSTEM_TYPE} ${SOURCE_FILES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if(${QTVERSION} STREQUAL "QT6")
    target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Gui Qt6::Core Qt6::PrintSupport Qt6::Charts Qt6::Svg Qt6::OpenGL)
elseif(${QTVERSION} STREQUAL "QT5")
    target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Gui Qt5::Core Qt5::PrintSupport Qt5::Charts)
endif()

