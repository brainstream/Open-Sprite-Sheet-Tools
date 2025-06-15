###########################################################################################################
# Copyright © 2025 Sergey Smolyannikov aka brainstream                                                    #
#                                                                                                         #
# This file is part of the Open Sprite Sheet Tools.                                                       #
#                                                                                                         #
# Open Sprite Sheet Tools is free software: you can redistribute it and/or modify it under  the terms of  #
# the GNU General Public License as published by the Free Software Foundation, either version 3 of the    #
# License, or (at your option) any later version.                                                         #
#                                                                                                         #
# Open Sprite Sheet Tools is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;    #
# without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              #
# See the GNU General Public License for more details.                                                    #
#                                                                                                         #
# You should have received a copy of the GNU General Public License along with MailUnit.                  #
# If not, see <http://www.gnu.org/licenses/>.                                                             #
#                                                                                                         #
###########################################################################################################

cmake_minimum_required(VERSION 3.16)

project("Open Sprite Sheet Tools" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Xml)

set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(OSST_SRC_DIR ${SRC_DIR}/OpenSpritSheetTools)

set(PROJECT_SOURCES
  ${OSST_SRC_DIR}/Main.cpp
  ${OSST_SRC_DIR}/Exception.h
  ${OSST_SRC_DIR}/Gui/MainWindow.cpp
  ${OSST_SRC_DIR}/Gui/MainWindow.h
  ${OSST_SRC_DIR}/Gui/MainWindow.ui
  ${OSST_SRC_DIR}/Gui/GraphicsView.h
  ${OSST_SRC_DIR}/Gui/GraphicsView.cpp
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.h
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.cpp
  ${OSST_SRC_DIR}/Gui/SpriteSheetSplitterWidget.ui
  ${OSST_SRC_DIR}/Gui/SpritePackerWidget.h
  ${OSST_SRC_DIR}/Gui/SpritePackerWidget.cpp
  ${OSST_SRC_DIR}/Gui/SpritePackerWidget.ui
  ${OSST_SRC_DIR}/Gui/ZoomModel.h
  ${OSST_SRC_DIR}/Gui/ZoomModel.cpp
  ${OSST_SRC_DIR}/Gui/ZoomWidget.h
  ${OSST_SRC_DIR}/Gui/ZoomWidget.cpp
  ${OSST_SRC_DIR}/Gui/ZoomWidget.ui
  ${OSST_SRC_DIR}/Resources/Resources.qrc
  ${OSST_SRC_DIR}/Settings.h
  ${OSST_SRC_DIR}/Settings.cpp
  ${OSST_SRC_DIR}/Atlas/Atlas.h
  ${OSST_SRC_DIR}/Atlas/Frame.h
  ${OSST_SRC_DIR}/Atlas/AtlasSerializer.h
  ${OSST_SRC_DIR}/Atlas/DefaultAtlasSerializer.h
  ${OSST_SRC_DIR}/Atlas/DefaultAtlasSerializer.cpp
  ${OSST_SRC_DIR}/Splitters/Splitter.h
  ${OSST_SRC_DIR}/Splitters/GridSplitter.h
  ${OSST_SRC_DIR}/Splitters/GridSplitter.cpp
  ${OSST_SRC_DIR}/Splitters/AtlasSplitter.h
  ${OSST_SRC_DIR}/Splitters/AtlasSplitter.cpp
)

set(OSST open-sprite-sheet-tools)

qt_add_executable(${OSST}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(${OSST} PRIVATE Qt6::Widgets Qt6::Xml)

target_include_directories(${OSST}
  PRIVATE ${SRC_DIR}
)

qt_finalize_executable(${OSST})
