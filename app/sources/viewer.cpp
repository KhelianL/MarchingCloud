#include <viewer.h>

Viewer::Viewer(Scene *const s, InterfaceQT *const i, QWidget *parent) : scene(s), interfaceQt(i), QGLViewer(parent)
{
	this->interfaceQt->enableEdit(false);
	this->init();
}

void Viewer::init()
{
	restoreStateFromFile();
	setMouseTracking(true);
	setAxisIsDrawn();
	glDisable(GL_LIGHTING);
	glPointSize(2.0);
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
		PointCloud &p = this->scene->getPointCloudAtIndex(indexPointCloud);
		this->interfaceQt->targetP = &p;
		this->interfaceQt->indexP = indexPointCloud;

		p.setIsSelected(true);
		this->interfaceQt->updateViewerTarget();
		this->interfaceQt->enableEdit(true);
	}
	else
	{
		this->interfaceQt->targetP = nullptr;
		this->interfaceQt->indexP = 0;
		this->interfaceQt->resetViewerTarget();
		this->interfaceQt->enableEdit(false);
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

std::string myToStringFloat(float a)
{
	std::stringstream ss;
	ss << a;
	return ss.str();
}

void Viewer::sceneParserJSON(const std::string &filename)
{
	std::string fileContent = ""; // std::string for popback "," if needed.
	fileContent += "{\n";
	/** START **/

	/** DATA SCENE CAMERA **/
	qglviewer::Vec cam_p = this->camera()->position();
	qglviewer::Quaternion cam_o = this->camera()->orientation();

	fileContent += "\t\"data_camera\":{\n";
	fileContent += "\t\t\"position\":[" + myToStringFloat(cam_p[0]) + "," + myToStringFloat(cam_p[1]) + "," + myToStringFloat(cam_p[2]) + "],\n";
	fileContent += "\t\t\"orientation\":[" + myToStringFloat(cam_o[0]) + "," + myToStringFloat(cam_o[1]) + "," + myToStringFloat(cam_o[2]) + "," + myToStringFloat(cam_o[3]) + "]\n";
	fileContent += "\t},\n";

	/** DATA SCENE POINT CLOUD **/
	fileContent += "\t\"data_scene\":[\n";
	std::vector<PointCloud> &sceneData = this->getScene()->getListPointCloud();

	// Pour chaque PointCloud
	for (PointCloud &pointCloud : sceneData)
	{
		fileContent += "\t\t{\n";
		/** START POINTCLOUD **/

		// Type and Resolution
		PointCloudType &typePointCloud = pointCloud.getPointCloudType();
		int &resolution = pointCloud.getResolution();
		fileContent += "\t\t\"type_pointcloud\":\"" + getPointCloudTypeToString(typePointCloud) + "\",\n";
		fileContent += "\t\t\"param_resolution\":" + myToStringFloat(resolution) + ",\n";

		// If IMPORT : save each positions/normals
		if (typePointCloud == PointCloudType::IMPORT)
		{
			// For Each positions
			std::string savePos;
			fileContent += "\t\t\t\"positions\":[\n";
			for (const Vec3 &position : pointCloud.getPositions())
			{
				fileContent += "\t\t\t\t[" + myToStringFloat(position[0]) + "," + myToStringFloat(position[1]) + "," + myToStringFloat(position[2]) + "],\n";
			}
			if (pointCloud.getPositions().size() > 1)
			{
				fileContent.pop_back();
				fileContent.pop_back();
				fileContent += "\n";
			}
			fileContent += "\t\t\t],\n";

			// For Each normals
			fileContent += "\t\t\t\"normals\":[\n";
			for (const Vec3 &normal : pointCloud.getNormals())
			{
				fileContent += "\t\t\t\t[" + myToStringFloat(normal[0]) + "," + myToStringFloat(normal[1]) + "," + myToStringFloat(normal[2]) + "],\n";
			}
			if (pointCloud.getNormals().size() > 1)
			{
				fileContent.pop_back();
				fileContent.pop_back();
				fileContent += "\n";
			}
			fileContent += "\t\t\t],\n";
		}

		// Relative Transforms
		const Vec3 &relativePosition = pointCloud.getRelativePosition();
		const Vec3 &relativeRotation = pointCloud.getRelativeRotation();
		const Vec3 &relativeScale = pointCloud.getRelativeScale();
		fileContent += "\t\t\t\"relative_position\":[" + myToStringFloat(relativePosition[0]) + "," + myToStringFloat(relativePosition[1]) + "," + myToStringFloat(relativePosition[2]) + "],\n";
		fileContent += "\t\t\t\"relative_rotation\":[" + myToStringFloat(relativeRotation[0]) + "," + myToStringFloat(relativeRotation[1]) + "," + myToStringFloat(relativeRotation[2]) + "],\n";
		fileContent += "\t\t\t\"relative_scale\":[" + myToStringFloat(relativeScale[0]) + "," + myToStringFloat(relativeScale[1]) + "," + myToStringFloat(relativeScale[2]) + "],\n";

		// Material
		Material &mat = pointCloud.getMaterial();
		MaterialType &typeMaterial = mat.getType();

		if (typeMaterial == MaterialType::Custom)
		{
			const Vec3 &matAmb = mat.getAmbiant();
			const Vec3 &matDif = mat.getDiffuse();
			const Vec3 &matSpe = mat.getSpecular();
			const int &matSpecExp = mat.getSpecExp();
			const float &matTransparency = mat.getTransparency();
			const float &matRefractionIndex = mat.getRefractionIndex();
			fileContent += "\t\t\t\"type_material\":\"" + getMaterialTypeToString(typeMaterial).toStdString() + "\",\n";
			fileContent += "\t\t\t\"material\":{\n";
			fileContent += "\t\t\t\t\"ambient\":[" + myToStringFloat(matAmb[0]) + "," + myToStringFloat(matAmb[1]) + "," + myToStringFloat(matAmb[2]) + "],\n";
			fileContent += "\t\t\t\t\"diffuse\":[" + myToStringFloat(matDif[0]) + "," + myToStringFloat(matDif[1]) + "," + myToStringFloat(matDif[2]) + "],\n";
			fileContent += "\t\t\t\t\"specular\":[" + myToStringFloat(matSpe[0]) + "," + myToStringFloat(matSpe[1]) + "," + myToStringFloat(matSpe[2]) + "],\n";
			fileContent += "\t\t\t\t\"specular_exponent\":" + myToStringFloat(matSpecExp) + ",\n";
			fileContent += "\t\t\t\t\"transparency\":" + myToStringFloat(matTransparency) + ",\n";
			fileContent += "\t\t\t\t\"refraction_index\":" + myToStringFloat(matRefractionIndex) + "\n";
			fileContent += "\t\t\t}\n";
		}
		else
		{
			fileContent += "\t\t\t\"typeMaterial\":\"" + getMaterialTypeToString(typeMaterial).toStdString() + "\"\n";
		}

		/** END POINTCLOUD **/
		fileContent += (sceneData.size() == 1 ? "\t\t}\n" : "\t\t},\n");
	}
	if (sceneData.size() > 1)
	{
		fileContent.pop_back();
		fileContent.pop_back();
		fileContent += "\n";
	}
	fileContent += "\t]\n";

	/** END **/
	fileContent += "}";

	std::ofstream jsonFile(filename);
	jsonFile << fileContent;
}