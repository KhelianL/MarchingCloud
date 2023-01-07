#include <viewer.h>

Viewer::Viewer(Scene *const s, QWidget *parent) : scene(s), QGLViewer(parent)
{
        this->init();
}

void Viewer::draw()
{
        this->scene->draw();
}

void Viewer::init()
{
        restoreStateFromFile();
        setMouseTracking(true);
        setAxisIsDrawn();
        glDisable(GL_LIGHTING);
        glPointSize(1.0);
}

void Viewer::keyPressEvent(QKeyEvent *event)
{
        switch (event->key())
        {
        case Qt::Key_R:
                rayTraceEvent(0, 0);
                break;
        default:
                QGLViewer::keyPressEvent(event);
        }
}

void Viewer::rayTraceEvent(int width, int height)
{
        // Get Scene informations
        std::vector<PointCloud> scenePointCloud = this->scene->getListPointCloud();

        int tmpW = this->camera()->screenWidth();
        int tmpH = this->camera()->screenHeight(); 

        // Get Size
        if (width == 0 || height == 0)
        {
                QSize windowSize = size();
                width = windowSize.width();
                height = windowSize.height();
        }
        else
        {
                this->camera()->setScreenWidthAndHeight(width, height);
                this->camera()->setAspectRatio(width / height);
        }

        // Projection Matrix
        float projectionMatrix[16];
        float modelViewMatrix[16];
        this->camera()->getProjectionMatrix(projectionMatrix);
        this->camera()->getModelViewMatrix(modelViewMatrix);
        QMatrix4x4 invprojectionMat4 = QMatrix4x4(projectionMatrix).inverted().transposed();
        QMatrix4x4 invmodelViewMat4 = QMatrix4x4(modelViewMatrix).inverted().transposed();
        
        // Reset
        this->camera()->setScreenWidthAndHeight(tmpW, tmpH);

        // Get Camera Position
        qglviewer::Vec cameraPos = this->camera()->position();

        if (this->scene->getListPointCloud().size() > 0)
        {
                linkToCuda(scenePointCloud, width, height, invmodelViewMat4.data(), invprojectionMat4.data(), {cameraPos.x, cameraPos.y, cameraPos.z});
        }
}

Scene *Viewer::getScene()
{
        return this->scene;
}

QString Viewer::helpString() const
{
        QString text("<h2>S i m p l e V i e w e r</h2>");
        text += "Use the mouse to move the camera around the object. ";
        text += "You can respectively revolve around, zoom and translate with the "
                "three mouse buttons. ";
        text += "Left and middle buttons pressed together rotate around the camera "
                "view direction axis<br><br>";
        text += "Pressing <b>Alt</b> and one of the function keys "
                "(<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
        text += "Simply press the function key again to restore it. Several "
                "keyFrames define a ";
        text += "camera path. Paths are saved when you quit the application and "
                "restored at next start.<br><br>";
        text +=
            "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
        text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save "
                "a snapshot. ";
        text += "See the <b>Keyboard</b> tab in this window for a complete shortcut "
                "list.<br><br>";
        text += "Double clicks automates single click actions: A left button double "
                "click aligns the closer axis with the camera (if close enough). ";
        text += "A middle button double click fits the zoom of the camera and the "
                "right button re-centers the scene.<br><br>";
        text += "A left button double click while holding right button pressed "
                "defines the camera <i>Revolve Around Point</i>. ";
        text += "See the <b>Mouse</b> tab and the documentation web pages for "
                "details.<br><br>";
        text += "Press <b>Escape</b> to exit the viewer.";
        return text;
}