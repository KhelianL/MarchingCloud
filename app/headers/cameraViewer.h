#ifndef CAMERA_VIEWER_H
#define CAMERA_VIEWER_H

/* libQGLViewer */
#include <qglviewer.h>

/* SRC */
#include <pointCloud.h>

class CameraViewer : public QGLViewer
{
private:
    QVector<PointCloud> listPointCloud;

protected:
    virtual void init();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void draw();
    virtual QString helpString() const;
};

#endif