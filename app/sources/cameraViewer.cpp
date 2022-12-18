/* SRC */
#include <iostream>

#include <cameraViewer.h>

#include <QMatrix4x4>

/* libQGLViewer */
#include <vec.h>

#include <Vec3.h> 

#include <chrono>

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

        Material bronze;
        bronze.AMBIANT_COLOR = Vec3(0.2125, 0.1275, 0.054);
        bronze.DIFFUSE_COLOR = Vec3(0.714, 0.4284, 0.18144);
        bronze.SPECULAR_COLOR = Vec3(0.393548, 0.271906, 0.166721);
        bronze.SPECULAR_EXPONENT = 25.6;
        bronze.transparency = 0.0;
        bronze.refractionIndex = 0.0;

        Material copper;
        copper.AMBIANT_COLOR = Vec3(0.19125, 0.0735, 0.0225);
        copper.DIFFUSE_COLOR = Vec3(0.7038, 0.27048, 0.0828);
        copper.SPECULAR_COLOR = Vec3(0.256777, 0.137622, 0.086014);
        copper.SPECULAR_EXPONENT = 12.8;
        copper.transparency = 0.0;
        copper.refractionIndex = 0.0;

        // Scene
        PointCloud igea;
        igea.loadPointCloud("data/pointsets/igea2_subsampled_extreme.pn");
        igea.setMaterial(gold);

        PointCloud dino;
        dino.loadPointCloud("data/pointsets/dino.pn");
        dino.setMaterial(silver);
        dino.move({0.5,0,0});

        PointCloud african_statue;
        african_statue.loadPointCloud("data/pointsets/african_statue.pn");
        african_statue.setMaterial(bronze);
        african_statue.move({-0.5,0,0});

        PointCloud face;
        face.loadPointCloud("data/pointsets/face.pn");
        face.setMaterial(copper);
        face.move({0,0.5,0});
        

        this->listPointCloud.push_back(igea);
        this->listPointCloud.push_back(dino);
        this->listPointCloud.push_back(african_statue);
        this->listPointCloud.push_back(face);

        // Help window
        // help();

        //
}

constexpr double kPricePerKWh = 0.15; // Le prix d'un kilowattheure en euros
constexpr double kPowerConsumption = 100.0; // La consommation en watts

void displayElectricityPrice(int duration)
{
  // Convertir la durée en heures
  double durationInHours = static_cast<double>(duration) / 3600.0;
  // Calculer la consommation en kilowattheures
  double consumptionInKWh = kPowerConsumption * durationInHours / 1000.0;
  // Calculer le prix en euros
  double price = consumptionInKWh * kPricePerKWh;
  // Convertir le prix en centimes d'euros
  float priceInCents = price * 100.0;

  std::cout << "Le rendu a durré " << duration << " secondes et a couté " << priceInCents << " centimes d'euros." << std::endl;
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

        auto l_clock = std::chrono::high_resolution_clock::now();

        switch (event->key())
        {
        case Qt::Key_R:

                camPos = this->camera()->position();

                for (int i = 0, sizeMax = this->listPointCloud.size(); i < sizeMax; i++)
                {
                        std::vector<qglviewer::Vec> p = this->listPointCloud[i].getPositions();
                        std::vector<qglviewer::Vec> n = this->listPointCloud[i].getNormals();

                        materialList.push_back(this->listPointCloud[i].getMaterial());
                        
                        for(int j = 0 ; j < p.size() ; j ++){
                                positions.push_back(Vec3(p[j].x,p[j].y,p[j].z));
                                normals.push_back(Vec3(n[j].x,n[j].y,n[j].z));
                                materialIndex.push_back(i);
                        }

                }
                
                pcd = getGPUpcd(positions, normals, materialIndex, materialList);
                
                
                cuda_ray_trace_from_camera(width, height, invmodelViewMat4.data(), invprojectionMat4.data(), {camPos.x,camPos.y,camPos.z} , pcd);
                displayElectricityPrice(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - l_clock).count()/1000);

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