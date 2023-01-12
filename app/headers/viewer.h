#ifndef VIEWER_H
#define VIEWER_H

/* C++ */
#include <sstream>

/* QT */
#include <QString>
#include <QKeyEvent>
#include <QWidget>
#include <QMatrix4x4>

/* libQGLViewer */
#include <qglviewer.h>
#include <vec.h>
#include <quaternion.h>

/* SRC */
#include <vec3.h>
#include <pointCloud.h>
#include <scene.h>
#include <interface.h>
#include <tools.h>

class Viewer : public QGLViewer
{
private:
    Scene *scene;
    InterfaceQT *const interfaceQt;

protected:
    virtual void init();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void draw();
    virtual QString helpString() const;

public:
    Viewer(InterfaceQT *const i, QWidget *parent);
    ~Viewer();

    Scene *getScene();

    void rayTraceEvent(int width, int height);

    void rayCastClick(const QPoint &point);
    float isAABBHit(const Vec3 &MinAABB, const Vec3 &MaxAABB, const qglviewer::Vec &rayOrigin, const qglviewer::Vec &rayDirection);

    void sceneParserJSON(const std::string &filename);
    void sceneReaderJSON(const std::string &filename);
};

std::string myToStringFloat(float a);

#endif