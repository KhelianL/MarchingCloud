/* QT */
#include <QApplication>

/* CUDA */
#include <hello.cuh>

/* HEADERS */
#include <simpleViewer.h>

int main(int argc, char **argv)
{
    kernel();

    QApplication app(argc, argv);

    // Instantiate the viewer.
    Viewer viewer;
    viewer.setWindowTitle("simpleViewer");
    viewer.show();

    return app.exec();
}