#include <QApplication>

#include <mainwindow.h>

#include <hello.cuh>

int main(int argc, char *argv[])
{
    kernel();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
