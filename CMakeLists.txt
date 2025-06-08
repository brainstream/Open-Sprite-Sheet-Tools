cmake_minimum_required(VERSION 3.16)

project("Open Sprite Sheet Tools" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(OSST_SRC_DIR ${SRC_DIR}/OpenSpritSheetTools)

set(PROJECT_SOURCES
  ${OSST_SRC_DIR}/Main.cpp
  ${OSST_SRC_DIR}/Gui/MainWindow.cpp
  ${OSST_SRC_DIR}/Gui/MainWindow.h
  ${OSST_SRC_DIR}/Gui/MainWindow.ui
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.h
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.cpp
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.ui
  ${OSST_SRC_DIR}/Resources/Resources.qrc
  ${OSST_SRC_DIR}/Settings.h
  ${OSST_SRC_DIR}/Settings.cpp
)

set(OSST open-sprite-sheet-tools)

qt_add_executable(${OSST}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(${OSST} PRIVATE Qt6::Widgets)

target_include_directories(${OSST}
  PRIVATE ${SRC_DIR}
)

qt_finalize_executable(${OSST})
