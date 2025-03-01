cmake_minimum_required(VERSION 3.26)

project(SimpleGM VERSION 2.11 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#support Visual Studio 2022
if (MSVC)
    #PATH_QT_MSVC  -> C:/Qt/6.8.1/msvc2022_64
    set(CMAKE_PREFIX_PATH ${PATH_QT_MSVC})

endif (MSVC)

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

#Set path for assembly framework .OpenCascade
#linux path

if (UNIX)   
    #PATH_CASCADE_LINUX  ->  /run/media/alexey/LinuxData/Cascade/occ_linux_build790)
    set(THIRD_PARTY_PATH ${PATH_CASCADE_LINUX})
endif (UNIX)
#windows path
if (WIN32)
    #PATH_CASCADE_WINDOWS  -> D:/Cascade/occt_win_build780
    set(THIRD_PARTY_PATH ${PATH_CASCADE_WINDOWS})
endif (WIN32)

#apple mac os path
if (APPLE)
    #PATH_CASCADE_APPLE  -> /Users/admin/Documents/MacData/occt_mac_build780
    set(THIRD_PARTY_PATH ${PATH_CASCADE_APPLE})
endif(APPLE)

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
        if (MSVC)
            #support Visual Studio 2022
            link_directories(${THIRD_PARTY_PATH}/vc2022/libd)
        endif (MSVC)
    endif()
endif (WIN32)


#linux path
if (UNIX)

    link_directories(${THIRD_PARTY_PATH}/lin64/gcc/lib)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Building in Debug mode")
        link_directories(${THIRD_PARTY_PATH}/lin64/gcc/libd)
    endif()
endif (UNIX)

#apple path
if (APPLE)
    link_directories(${THIRD_PARTY_PATH}/mac64/clang/libd)
endif(APPLE)


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




