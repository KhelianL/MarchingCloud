#include <standardCamera.h>

StandardCamera::StandardCamera() {}

qreal StandardCamera::zNear() const
{
    return 0.0001;
}
qreal StandardCamera::zFar() const
{
    return 10000.0;
}