#ifndef VIEWER_H
#define VIEWER_H

/* QT */
#include <QString>
#include <QKeyEvent>
#include <QWidget>
#include <QMatrix4x4>

/* libQGLViewer */
#include <qglviewer.h>
#include <camera.h>
#include <vec.h>

/* SRC */
#include <scene.h>
#include <tools.h>
#include <vec3.h>

class Viewer : public QGLViewer
{
private:
    Scene *const scene;
    qglviewer::Camera *camera;

protected:
    virtual void init();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void draw();
    virtual QString helpString() const;

public:
    Viewer(Scene *const s, qglviewer::Camera *c, QWidget *parent);
    Scene *getScene();
    void rayTraceEvent();
};

#endif