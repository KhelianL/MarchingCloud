#include <QApplication>
#include <cameraViewer.h>
#include <QWidget>


#include <QFile>

extern "C" void test();

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    CameraViewer viewer;
    viewer.setWindowTitle("MarchingCloud");

    viewer.show();

    return app.exec();
}