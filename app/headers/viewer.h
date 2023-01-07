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

class Viewer : public QGLViewer
{
private:
    Scene *const scene;
    QLineEdit *editWidth;
    QLineEdit *editHeight;

protected:
    virtual void init();
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void draw();
    virtual QString helpString() const;

public:
    Viewer(Scene *const s, QLineEdit *w, QLineEdit *h, QWidget *parent);
    Scene *getScene();
    void rayTraceEvent(int width, int height);
};

#endif