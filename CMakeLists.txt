cmake_minimum_required(VERSION 3.26)

project(SimpleGM VERSION 2.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp
        occQt.h
        occQt.cpp
        occView.h
        occView.cpp
        occQt.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()


#!Задан путь до сборки
set(THIRD_PARTY_PATH /run/media/alexey/LinuxData/Cascade/occt_linux_build780)
message(${CMAKE_SOURCE_DIR})

include_directories(${THIRD_PARTY_PATH}/inc)

# Set the CMake build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


#windows path
if (WIN32)
    link_directories(${THIRD_PARTY_PATH}/win64/gcc/lib)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Building in Debug mode")
        link_directories(${THIRD_PARTY_PATH}/win64/gcc/libd)
    endif()
endif (WIN32)

if (UNIX)
#linux path
    link_directories(${THIRD_PARTY_PATH}/lin64/gcc/lib)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Building in Debug mode")
        link_directories(${THIRD_PARTY_PATH}/lin64/gcc/libd)
    endif()
endif (UNIX)
set(OpenCASCADE_Component
  TKernel TKService TKV3d TKOpenGl
  TKBRep TKGeomBase TKGeomAlgo TKG3d TKG2d TKTopAlgo
  TKPrim TKMath TKBin TKBO TKFillet
  TKOffset TKTObj TKFeat TKMesh
  TKDEVRML TKDESTL TKBRep TKDEIGES
  TKShHealing TKDESTEP TKXSBase TKBool TKCAF TKLCAF TKXCAF
  TKCDF TKHLR
)

add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            occqt.qrc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    ${OpenCASCADE_Component}
)


# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.occQt)
# endif()
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
#
# include(GNUInstallDirs)
# install(TARGETS ${PROJECT_NAME}
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
#
# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(${PROJECT_NAME})
# endif()
