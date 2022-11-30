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

##################
# Link QGLViewer #
##################

# set(QGLVIEWER_FILES ${CMAKE_BINARY_DIR}/extern/libQGLViewer-2.8.0/QGLViewer/qglviewer.h)
# get_target_property(QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
# 
# add_custom_command(OUTPUT ${QGLVIEWER_FILES}
#   COMMAND  tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/extern/libQGLViewer-2.8.0.tar.gz" --strip 1
#   COMMAND ${QT_QMAKE_EXECUTABLE} -o QMakefile 
#   COMMAND make -f QMakefile 
#   WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/extern/libQGLViewer-2.8.0"
#   DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/extern/libQGLViewer-2.8.0.tar.gz"
#   COMMENT "Unpacking libQGLViewer-2.8.0.tar.gz"
#   VERBATIM
# )
# 
# add_custom_target(qglviewer_untar DEPENDS ${QGLVIEWER_FILES})
# 
# add_library(qglviewer SHARED IMPORTED)
# add_dependencies(qglviewer qglviewer_untar)
# 
# set_target_properties(qglviewer PROPERTIES
#                       IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/extern/libQGLViewer-2.8.0/QGLViewer/libQGLViewer-qt5.so"
#                       INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/extern/libQGLViewer-2.8.0")

##################
# ############## #
##################

find_package(Qt5Widgets)

# Tell CMake to create the marchingCloud executable
add_executable(marchingCloud 
    src/main.cpp
    src/sampleapp.cpp
    src/mainwindow.cpp
)

target_link_libraries(marchingCloud
    Qt5::Widgets
)

# target_include_directories(marchingCloud PUBLIC
#   "${CMAKE_SOURCE_DIR}/header"
# )

set_target_properties(marchingCloud PROPERTIES
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)