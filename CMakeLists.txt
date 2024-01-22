cmake_minimum_required(VERSION 3.14)

project(SudokuCube VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
set(Boost_USE_MULTITHREADED ON)
ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
ADD_DEFINITIONS("-DBOOST_PROGRAM_OPTIONS_DYN_LINK=1")
find_package( Boost 1.66 REQUIRED system filesystem program_options date_time serialization unit_test_framework)

include_directories(${Boost_INCLUDE_DIRS})


set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        CubeModel.h CubeModel.cpp
        CubeFaceModel.h CubeFaceModel.cpp
        ColorModel.h ColorModel.cpp
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SudokuCube
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
qt_add_qml_module(SudokuCube
    URI sudoku.cube.ex
    VERSION 1.0
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SudokuCube APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SudokuCube SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SudokuCube
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SudokuCube
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set_target_properties(SudokuCube PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SudokuCube
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(SudokuCube)
    qt_finalize_executable(SudokuCube)
endif()
