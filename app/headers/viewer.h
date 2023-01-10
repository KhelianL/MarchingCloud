#ifndef VIEWER_H
#define VIEWER_H

/* QT */
#include <QString>
#include <QKeyEvent>
#include <QWidget>
#include <QMatrix4x4>

/* libQGLViewer */
#include <qglviewer.h>
#include <vec.h>

/* SRC */
#include <scene.h>
#include <tools.h>
#include <vec3.h>
#include <interfaceQT.h>

class Viewer : public QGLViewer
{
private:
    Scene *const scene;
    InterfaceQT *interfaceQt;

protected:
    virtual void init();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void draw();
    virtual QString helpString() const;

public:
    Viewer(Scene *const s, InterfaceQT *i, QWidget *parent);
    ~Viewer();

    Scene *getScene();

    void rayTraceEvent(int width, int height);

    void rayCastClick(const QPoint &point);
    float isAABBHit(const Vec3 &MinAABB, const Vec3 &MaxAABB, const qglviewer::Vec &rayOrigin, const qglviewer::Vec &rayDirection);
};

#endif