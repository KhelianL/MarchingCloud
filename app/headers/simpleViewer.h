#include <qglviewer.h>

#include <pointCloud.h>

class Viewer : public QGLViewer
{
private:
    PointCloud test;

protected:
    virtual void draw();
    virtual void init();
    virtual QString helpString() const;
};