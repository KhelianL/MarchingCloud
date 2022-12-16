#include <QApplication>

#include <hello.cuh>

#include <simpleViewer.h>

int main(int argc, char **argv)
{
    // kernel();

    QApplication application(argc, argv);

    Viewer viewer;
    viewer.setWindowTitle("simpleViewer");
    viewer.show();


    return application.exec();
}