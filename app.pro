TEMPLATE = app

QT *= core gui widgets opengl xml
CONFIG *= qt opengl c++17 warn_off

TARGET = marchingCloud
DESTDIR = ./

INCLUDEPATH *= ./app/headers

CUDA_SOURCES = $$files(*.cu, true)
SOURCES = $$files(*.cpp, true)
HEADERS = $$files(*.h, true) $$files(*.cuh, true)
FORMS = $$files(*.ui, true)

OBJECTS_DIR = ./app/build/.obj
MOC_DIR = ./app/build/.moc
RCC_DIR = ./app/build/.rcc
UI_DIR = ./app/build/.ui

#####################################################################
#                    CUDA compiler configuration                    #
#####################################################################

INCLUDEPATH *= $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib/
CUDA_LIBS = -lcuda -lcudart
CUDA_INC = $$join(INCLUDEPATH,'" -I"','-I"','"')
LIBS += $$CUDA_LIBS

NVCCOPTIONS = -use_fast_math -O2   
NVCCOPTIONS *= -g -G               

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCCOPTIONS $$CUDA_INC -c ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
cuda.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda

#####################################################################
#                  QGLViewer compiler configuration                 #
#####################################################################

LIBS *= -lGLU
LIBS *= -L./lib/libQGLViewer-2.8.0/QGLViewer/ -lQGLViewer-qt5
INCLUDEPATH *= ./lib/libQGLViewer-2.8.0/QGLViewer
DEPENDPATH *= ./lib/libQGLViewer-2.8.0/QGLViewer

#####################################################################
#                             RSJParser                             #
#####################################################################

INCLUDEPATH *= ./lib/RSJP