/* SRC */
#include <iostream>

#include <cameraViewer.h>

#include <QMatrix4x4>

/* libQGLViewer */
#include <vec.h>

#include <Vec3.h> 

extern "C" void test();

struct cVec3 {
   float mVals[3];
   

   cVec3( float x , float y , float z ) {
      mVals[0] = x; mVals[1] = y; mVals[2] = z;
   }

   cVec3() {
      mVals[0] = 0.0;
      mVals[1] = 0.0;
      mVals[2] = 0.0;
   }

   float operator [] (unsigned int c) { return mVals[c]; }
   float operator [] (unsigned int c) const { return mVals[c]; }


   float squareLength() const {
      return mVals[0]*mVals[0] + mVals[1]*mVals[1] + mVals[2]*mVals[2];
   }

   float length() const { return sqrt( squareLength() ); }

   void operator += (cVec3 const & other) {
      mVals[0] += other[0];
      mVals[1] += other[1];
      mVals[2] += other[2];
   }

   void normalize() { float L = length(); mVals[0] /= L; mVals[1] /= L; mVals[2] /= L; }

   friend std::ostream & operator<<(std::ostream &out, const cVec3 &vec)
    {
        out << "(";
        for (int i = 0; i < 3; i++) {
        out << vec.mVals[i];
        if (i < 2) {
        out << ", ";
        }
        }
        out << ")";
        return out;
    }

   

};

extern "C" struct Material{
    Vec3 AMBIANT_COLOR = Vec3(0,0,0);
    Vec3 DIFFUSE_COLOR= Vec3(0.5,0.5,0.5);
    Vec3 SPECULAR_COLOR= Vec3(0.5,0.5,0.5);

    int SPECULAR_EXPONENT = 32;
    float transparency = 0.0;
    float refractionIndex = 1.0;
};
extern "C" struct kd_tree_node{
    int ind;

    float x;
    float y;
    float z;

    int axis;

    int left;
    int right;
};

extern "C" struct PointCloudData{
    kd_tree_node* kdTree;
    char* materialIndex;
    Material* materialList;
    Vec3 * positions;
    Vec3 * normals;
};

extern "C" void cuda_ray_trace_from_camera(int w, int h, float ModelViewMatrix[16], float projectionMatrix[16], Vec3 cameraPos, PointCloudData pcd);

extern "C" PointCloudData getGPUpcd(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<char> materialIndex, std::vector<Material> materialList);


void CameraViewer::draw()
{
        int size = this->listPointCloud.size();
        for (int i = 0; i < size; i++)
                this->listPointCloud[i].draw();
}

void CameraViewer::init()
{
        // Init
        restoreStateFromFile();
        setMouseTracking(true);
        setAxisIsDrawn();
        glDisable(GL_LIGHTING);
        glPointSize(1.0);

        // Scene
        PointCloud igea;
        igea.loadPointCloud("data/pointsets/igea2_subsampled_extreme.pn");

        PointCloud dino;
        dino.loadPointCloud("data/pointsets/dino.pn");

        this->listPointCloud.push_back(igea);
        this->listPointCloud.push_back(dino);

        // Help window
        // help();
}

void CameraViewer::keyPressEvent(QKeyEvent *event)
{
        // float m[16];
        // QMatrix4x4 matrix;
        qglviewer::Vec camPos;

        float projectionMatrix[16];
        float modelViewMatrix[16];
        
        this->camera()->getProjectionMatrix(projectionMatrix);
        this->camera()->getModelViewMatrix(modelViewMatrix);

        QMatrix4x4 invprojectionMat4 = QMatrix4x4(projectionMatrix).inverted().transposed();
        QMatrix4x4 invmodelViewMat4 = QMatrix4x4(modelViewMatrix).inverted().transposed();

        PointCloudData pcd;

        QSize windowSize = size();
        int width = windowSize.width();
        int height = windowSize.height();

        // int znear = this->camera()->zNear();
        // std::cout<<"znear : "<<znear<<std::endl;

        std::vector<Vec3> positions;
        std::vector<Vec3> normals;
        std::vector<char> materialIndex;
        std::vector<Material> materialList;

        Material gold;
        gold.AMBIANT_COLOR = Vec3(0.24725, 0.1995, 0.0745);
        gold.DIFFUSE_COLOR = Vec3(0.75164, 0.60648, 0.22648);
        gold.SPECULAR_COLOR = Vec3(0.628281, 0.555802, 0.366065);
        gold.SPECULAR_EXPONENT = 51.2;
        gold.transparency = 0.0;
        gold.refractionIndex = 0.0;

        Material silver;
        silver.AMBIANT_COLOR = Vec3(0.19225, 0.19225, 0.19225);
        silver.DIFFUSE_COLOR = Vec3(0.50754, 0.50754, 0.50754);
        silver.SPECULAR_COLOR = Vec3(0.508273, 0.508273, 0.508273);
        silver.SPECULAR_EXPONENT = 51.2;
        silver.transparency = 0.0;
        silver.refractionIndex = 0.0;

        switch (event->key())
        {
        case Qt::Key_R:

                camPos = this->camera()->position();

                // this->camera()->getModelViewProjectionMatrix(m);
                // matrix = QMatrix4x4(m);
                // matrix = matrix.inverted();
                
                materialList.push_back(gold);
                materialList.push_back(silver);


                for (int i = 0, sizeMax = this->listPointCloud.size(); i < sizeMax; i++)
                {
                        std::vector<qglviewer::Vec> p = this->listPointCloud[i].getPositions();
                        std::vector<qglviewer::Vec> n = this->listPointCloud[i].getNormals();
                        
                        for(int j = 0 ; j < p.size() ; j ++){
                                positions.push_back(Vec3(p[j].x,p[j].y,p[j].z));
                                normals.push_back(Vec3(n[j].x,n[j].y,n[j].z));
                                materialIndex.push_back(i);
                        }

                }
                
                pcd = getGPUpcd(positions, normals, materialIndex, materialList);
                
                cuda_ray_trace_from_camera(width, height, invmodelViewMat4.data(), invprojectionMat4.data(), {camPos.x,camPos.y,camPos.z} , pcd);

                break;
        /*
        case Qt::Key_A:
                std::cout << this->camera()->keyFrameInterpolator(0) << std::endl;
                break;
        */
        default:
                QGLViewer::keyPressEvent(event);
        }
}

QString CameraViewer::helpString() const
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