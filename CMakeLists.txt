cmake_minimum_required(VERSION 3.2)

# Project
project(marchingCloud VERSION 1.0.0 LANGUAGES CXX)

# Requirement cpp
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make executable in current dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(Qt5 COMPONENTS Core Xml OpenGL Gui Widgets QUIET)

##################
# Link QGLViewer #
##################

# if(NOT Qt5_FOUND)
#   message("Qt5 not found. Install it and set Qt5_DIR accordingly")
#   if (WIN32)
#     message("In Windows, Qt5_DIR should be something like C:/Qt/5.4/msvc2013_64_opengl/lib/cmake/Qt5")
#   endif()
#   return()
# endif()
# 
# find_path(QGLVIEWER_INCLUDE_DIR qglviewer.h
#     /usr/include/QGLViewer
#     /opt/local/include/QGLViewer
#     /usr/local/include/QGLViewer
#     /sw/include/QGLViewer
#     ENV QGLVIEWERROOT
#   )
# 
# find_library(QGLVIEWER_LIBRARY_RELEASE
#   NAMES qglviewer QGLViewer qglviewer-qt5 QGLViewer-qt5
#   PATHS /usr/lib
#         /usr/local/lib
#         /opt/local/lib
#         /sw/lib
#         ENV QGLVIEWERROOT
#         ENV LD_LIBRARY_PATH
#         ENV LIBRARY_PATH
#   PATH_SUFFIXES QGLViewer QGLViewer/release
# )
# find_library(QGLVIEWER_LIBRARY_DEBUG
#   NAMES dqglviewer dQGLViewer dqglviewer-qt5 dQGLViewer-qt5 QGLViewerd2
#   PATHS /usr/lib
#         /usr/local/lib
#         /opt/local/lib
#         /sw/lib
#         ENV QGLVIEWERROOT
#         ENV LD_LIBRARY_PATH
#         ENV LIBRARY_PATH
#   PATH_SUFFIXES QGLViewer QGLViewer/debug
# )
# 
# if(QGLVIEWER_LIBRARY_RELEASE)
#   if(QGLVIEWER_LIBRARY_DEBUG)
#     set(QGLVIEWER_LIBRARY optimized ${QGLVIEWER_LIBRARY_RELEASE} debug ${QGLVIEWER_LIBRARY_DEBUG})
#   else()
#     set(QGLVIEWER_LIBRARY ${QGLVIEWER_LIBRARY_RELEASE})
#   endif()
# endif()

##################
# ############## #
##################

## Set folders vars
# set(MY_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/header)
# set(MY_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# set(MY_UI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ui)

## include headers
# include_directories(${MY_HEADER_DIR})

# Tell CMake to create the marchingCloud executable
add_executable(marchingCloud 
    src/main.cpp
    src/sampleapp.cpp
    src/mainwindow.cpp
    header/mainwindow.h
    header/sampleapp.h
)

target_include_directories(marchingCloud PUBLIC
  "${CMAKE_SOURCE_DIR}/header"
)

target_link_libraries(marchingCloud
    Qt5::Widgets
)

set_target_properties(marchingCloud PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)