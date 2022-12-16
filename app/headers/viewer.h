#include <qglviewer.h>

#include <pointCloud.h>

class Viewer : public QGLViewer
{
private:
    QVector<PointCloud> listPointCloud;

protected:
    virtual void draw();
    virtual void init();
    virtual QString helpString() const;
};