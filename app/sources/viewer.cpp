#include <viewer.h>

Viewer::Viewer(Scene *const s, InterfaceQT *const i, QWidget *parent) : scene(s), interfaceQt(i), QGLViewer(parent)
{
	this->interfaceQt->init();
	this->init();
}

void Viewer::init()
{
	restoreStateFromFile();
	setMouseTracking(true);
	setAxisIsDrawn();
	glDisable(GL_LIGHTING);
	glPointSize(1.0);
}

Viewer::~Viewer()
{
	delete this->scene;
	delete this->interfaceQt;
}

void Viewer::draw()
{
	this->scene->draw();
}

float Viewer::isAABBHit(const Vec3 &MinAABB, const Vec3 &MaxAABB, const qglviewer::Vec &rayOrigin, const qglviewer::Vec &rayDirection)
{
	// Calcul des paramètres t0 et t1 de l'intersection du rayon avec l'AABB
	float t0 = std::numeric_limits<float>::min();
	float t1 = std::numeric_limits<float>::max();
	for (int i = 0; i < 3; ++i)
	{
		// Calcul de t0 et t1
		float invRayDirection = 1.0f / rayDirection[i];
		float tNear = (MinAABB[i] - rayOrigin[i]) * invRayDirection;
		float tFar = (MaxAABB[i] - rayOrigin[i]) * invRayDirection;
		if (tNear > tFar)
		{
			std::swap(tNear, tFar);
		}
		t0 = std::max(t0, tNear);
		t1 = std::min(t1, tFar);

		// Si t0 > t1, pas d'intersection
		if (t0 > t1)
		{
			return -1.0f;
		}
	}
	// Si t0 <= t1, le rayon et l'AABB s'intersectent
	return t0;
}

void Viewer::rayCastClick(const QPoint &point)
{
	// Compute origine and direction, used to draw a representation of the intersecting line
	qglviewer::Vec origine, direction;
	camera()->convertClickToLine(point, origine, direction);

	float minDist = std::numeric_limits<float>::max();
	int indexPointCloud = -1;

	for (int i = 0, maxSize = this->scene->getListPointCloud().size(); i < maxSize; i++)
	{
		this->scene->getPointCloudAtIndex(i).setIsSelected(false);
		float distAtm = this->isAABBHit(this->scene->getPointCloudAtIndex(i).getMinAABB(), this->scene->getPointCloudAtIndex(i).getMaxAABB(), origine, direction);
		if (distAtm > 0 && distAtm < minDist)
		{
			minDist = distAtm;
			indexPointCloud = i;
		}
	}
	if (indexPointCloud >= 0)
	{
		this->interfaceQt->enableEdit(true);

		PointCloud &p = this->scene->getPointCloudAtIndex(indexPointCloud);
		p.setIsSelected(true);
		this->interfaceQt->updateViewerTarget(p);
	}
	else
	{
		this->interfaceQt->enableEdit(false);
		this->interfaceQt->resetViewerTarget();
	}
}

void Viewer::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_R:
		rayTraceEvent(this->interfaceQt->editWidth->text().toInt(), this->interfaceQt->editHeight->text().toInt());
		break;
	default:
		QGLViewer::keyPressEvent(event);
	}
}

void Viewer::mousePressEvent(QMouseEvent *e)
{
	if ((e->button() == Qt::LeftButton) && (e->modifiers() == Qt::NoButton))
	{
		QPoint cursorPos = QCursor::pos();
		QPoint windowPos = this->mapFromGlobal(cursorPos);
		rayCastClick(windowPos);
	}
	QGLViewer::mousePressEvent(e);
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
	}

	// Projection Matrix
	float projectionMatrix[16];
	float modelViewMatrix[16];
	this->camera()->getProjectionMatrix(projectionMatrix);
	this->camera()->getModelViewMatrix(modelViewMatrix);
	QMatrix4x4 invprojectionMat4 = QMatrix4x4(projectionMatrix).inverted().transposed();
	QMatrix4x4 invmodelViewMat4 = QMatrix4x4(modelViewMatrix).inverted().transposed();

	// Get Camera Position
	qglviewer::Vec cameraPos = this->camera()->position();

	if (this->scene->getListPointCloud().size() > 0)
	{
		linkToCuda(scenePointCloud, width, height, invmodelViewMat4.data(), invprojectionMat4.data(), {cameraPos.x, cameraPos.y, cameraPos.z});
	}

	// Reset
	this->camera()->setScreenWidthAndHeight(tmpW, tmpH);
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