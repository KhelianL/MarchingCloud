#ifndef STANDARD_CAMERA_H
#define STANDARD_CAMERA_H

/* libQGLViewer */
#include <camera.h>

class StandardCamera : public qglviewer::Camera
{
public:
    StandardCamera();

    virtual qreal zNear() const;
    virtual qreal zFar() const;
};

#endif