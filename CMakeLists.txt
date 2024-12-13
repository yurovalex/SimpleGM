cmake_minimum_required(VERSION 3.26)

project(SimpleGM VERSION 2.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




#support Visual Studio 2022
#set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/msvc2022_64") 

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        occQt.h
        occQt.cpp
        occView.h
        occView.cpp
        occQt.ui

        surfaces.h
        surfaces.cpp
)


#!Задан путь до сборки
#linux path
if (UNIX)
set(THIRD_PARTY_PATH /run/media/alexey/LinuxData/Cascade/occt_linux_build780)
endif (UNIX)
#windows path
if (WIN32)
set(THIRD_PARTY_PATH D:/Cascade/occt_win_build780)
endif (WIN32)

message(${CMAKE_SOURCE_DIR})
include_directories(${THIRD_PARTY_PATH}/inc)

# Set the CMake build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


#windows path
if (WIN32)
    link_directories(${THIRD_PARTY_PATH}/mingw/gcc/lib)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Building in Debug mode")
        link_directories(${THIRD_PARTY_PATH}/mingw/gcc/libd)
        #support Visual Studio 2022
	#link_directories(${THIRD_PARTY_PATH}/vc2022/libd)
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
    PRIVATE
    Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Core
    ${OpenCASCADE_Component}
)




