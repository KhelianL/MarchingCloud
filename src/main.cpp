#include <sampleapp.h>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
    SampleApp app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}

