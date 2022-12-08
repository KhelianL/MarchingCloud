TEMPLATE = app

QT *= core gui widgets opengl xml
CONFIG *= qt opengl c++17 warn_off

TARGET = marchingCloud
DESTDIR = ./

INCLUDEPATH *= \
    ./app/headers \
    ./app/ui

SOURCES = $$files(*.cpp, true)
HEADERS = $$files(*.h, true)
FORMS = $$files(*.ui, true)

OBJECTS_DIR = ./app/build/.obj
MOC_DIR = ./app/build/.moc
RCC_DIR = ./app/build/.rcc
UI_DIR = ./app/build/.ui

#####################################################################
#                   QGLViewer compiler configuration                #
#####################################################################

LIBS *= -lGLU
LIBS *= -L./lib/libQGLViewer-2.8.0/QGLViewer/ -lQGLViewer-qt5
INCLUDEPATH *= ./lib/libQGLViewer-2.8.0/QGLViewer
DEPENDPATH *= ./lib/libQGLViewer-2.8.0/QGLViewer

#####################################################################
#                   CUDA compiler configuration                     #
#####################################################################

CUDA_SOURCES = $$files(*.cu, true)
LIBS *= -L$$CUDA_DIR/lib64 -lcuda -lcudart

# GPU architecture
SYSTEM_TYPE = 64                    # '32' or '64', depending on your system
CUDA_ARCH = sm_30                   # Type of CUDA architecture, for example 'compute_10', 'compute_11', 'sm_10'
NVCCOPTIONS = -use_fast_math -O2

# Mandatory flags for stepping through the code
debug {
    NVCCOPTIONS *= -g -G
}

# Prepare the extra compiler configuration (taken from the nvidia forum - i'm not an expert in this part)
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCCOPTIONS $$CUDA_INC $$CUDA_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME} 2>&1 | sed -r \"s/\\(([0-9]+)\\)/:\\1/g\" 1>&2
cuda.dependency_type = TYPE_C

QMAKE_EXTRA_COMPILERS *= cuda

#####################################################################
#                               HELP                                #
#####################################################################

# " *= "    : adds value to the list only if it is not already present
# QT        : list of Qt modules used in a project
# CONFIG    : General project configuration options
# DESTDIR   : The directory in which the executable or binary file will be placed
# TARGET    : renames the resulting executable
# SOURCES   : list of sources files
# HEADERS   : list of headers files
# FORMS     : list of UI files