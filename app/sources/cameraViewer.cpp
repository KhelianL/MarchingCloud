/* SRC */
#include <iostream>

#include <cameraViewer.h>

#include <QMatrix4x4>

/* libQGLViewer */
#include <vec.h>

#include <Vec3.h> 

#include <chrono>

#include <random>
#include <ctime>

#include <alsa/asoundlib.h>


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

const int BUFFER_SIZE = 1024;

void playHappySound(){
        int err;
        snd_pcm_t *playback_handle;
        snd_pcm_hw_params_t *hw_params;

        // Ouvre le périphérique audio
        if ((err = snd_pcm_open(&playback_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
        {
        std::cout<<"Erreur d'ouverture du périphérique audio"<<std::endl;
        return;
        }

        // Alloue de la mémoire pour les paramètres du périphérique
        snd_pcm_hw_params_alloca(&hw_params);

        // Initialise les paramètres du périphérique
        snd_pcm_hw_params_any(playback_handle, hw_params);

        // Configure le format du son (16 bits, signé)
        snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE);

        // Configure la fréquence d'échantillonnage (44100 Hz)
        unsigned int freq = 44100;

        snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &freq, 0);

        // Configure le nombre de canaux (mono)
        snd_pcm_hw_params_set_channels(playback_handle, hw_params, 1);

        // Applique les paramètres au périphérique
        snd_pcm_hw_params(playback_handle, hw_params);

        // Charge le son à partir du fichier
        // Remplacez "nom_du_fichier.wav" par le nom du fichier que vous souhaitez jouer
        FILE *sound_file = fopen("data/ahhhhhh.wav", "rb");

        // Vérifie que le fichier a été ouvert correctement
        if (!sound_file)
        {
        std::cout<<"Erreur d'ouverture du fichier"<<std::endl;
        return;
        }

         std::vector<short> audio_buffer(BUFFER_SIZE);

        // Boucle jusqu'à ce que le fichier soit entièrement lu
        while (!feof(sound_file))
        {
        // Lit des données audio depuis le fichier
        size_t samples_read = fread(audio_buffer.data(), sizeof(short), audio_buffer.size(), sound_file);

        // Vérifie que la lecture a réussi
        if (samples_read < audio_buffer.size())
        {
            // Si la fin du fichier a été atteinte, ajuste la taille du tampon
            audio_buffer.resize(samples_read);
        }

        // Écrit les données audio dans le périphérique audio
        snd_pcm_writei(playback_handle, audio_buffer.data(), audio_buffer.size());
    }

    // Ferme le fichier et le périphérique audio
        // Ferme le fichier et le périphérique audio
        fclose(sound_file);
        snd_pcm_close(playback_handle);
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

        Material wood;
        wood.AMBIANT_COLOR = Vec3(0.3, 0.1, 0.1);
        wood.DIFFUSE_COLOR = Vec3(0.6, 0.3, 0.3);
        wood.SPECULAR_COLOR = Vec3(0.1, 0.1, 0.1);
        wood.SPECULAR_EXPONENT = 10.0;
        wood.transparency = 0.0;
        wood.refractionIndex = 0.0;

        Material redPlastic;
        redPlastic.AMBIANT_COLOR = Vec3(0.3, 0.0, 0.0);
        redPlastic.DIFFUSE_COLOR = Vec3(0.6, 0.0, 0.0);
        redPlastic.SPECULAR_COLOR = Vec3(0.8, 0.8, 0.8);
        redPlastic.SPECULAR_EXPONENT = 10.0;
        redPlastic.transparency = 0.0;
        redPlastic.refractionIndex = 0.0;

        Material greenPlastic;
        greenPlastic.AMBIANT_COLOR = Vec3(0.0, 0.3, 0.0);
        greenPlastic.DIFFUSE_COLOR = Vec3(0.0, 0.6, 0.0);
        greenPlastic.SPECULAR_COLOR = Vec3(0.8, 0.8, 0.8);
        greenPlastic.SPECULAR_EXPONENT = 10.0;
        greenPlastic.transparency = 0.0;
        greenPlastic.refractionIndex = 0.0;

        Material bluePlastic;
        bluePlastic.AMBIANT_COLOR = Vec3(0.0, 0.0, 0.3);
        bluePlastic.DIFFUSE_COLOR = Vec3(0.0, 0.0, 0.6);
        bluePlastic.SPECULAR_COLOR = Vec3(0.8, 0.8, 0.8);
        bluePlastic.SPECULAR_EXPONENT = 10.0;
        bluePlastic.transparency = 0.0;
        bluePlastic.refractionIndex = 0.0;

        Material ruby;
        ruby.AMBIANT_COLOR = Vec3(0.1745, 0.01175, 0.01175);
        ruby.DIFFUSE_COLOR = Vec3(0.61424, 0.04136, 0.04136);
        ruby.SPECULAR_COLOR = Vec3(0.727811, 0.626959, 0.626959);
        ruby.SPECULAR_EXPONENT = 76.8;
        ruby.transparency = 0.0;
        ruby.refractionIndex = 0.0;

        Material crystal;
        crystal.AMBIANT_COLOR = Vec3(0.1, 0.1, 0.1);
        crystal.DIFFUSE_COLOR = Vec3(0.4, 0.4, 0.4);
        crystal.SPECULAR_COLOR = Vec3(0.9, 0.9, 0.9);
        crystal.SPECULAR_EXPONENT = 100.0;
        crystal.transparency = 0.9;
        crystal.refractionIndex = 1.5;

        Material water;
        water.AMBIANT_COLOR = Vec3(0.0, 0.0, 0.2);
        water.DIFFUSE_COLOR = Vec3(0.0, 0.0, 0.6);
        water.SPECULAR_COLOR = Vec3(0.9, 0.9, 0.9);
        water.SPECULAR_EXPONENT = 100.0;
        water.transparency = 0.9;
        water.refractionIndex = 1.33;

        Material glass;
        glass.AMBIANT_COLOR = Vec3(0.0, 0.0, 0.0);
        glass.DIFFUSE_COLOR = Vec3(0.5, 0.5, 0.5);
        glass.SPECULAR_COLOR = Vec3(0.9, 0.9, 0.9);
        glass.SPECULAR_EXPONENT = 100.0;
        glass.transparency = 0.9;
        glass.refractionIndex = 1.5;

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
        african_statue.setMaterial(gold);
        african_statue.move({-0.5,0,0});

        PointCloud face;
        face.loadPointCloud("data/pointsets/face.pn");
        face.setMaterial(copper);
        face.move({0,0.5,0});

        
        PointCloud boule1;
        PointCloud boule2;
        PointCloud boite;

        boite.generateCornellBox(100);
        boule1.addSphere(2,-2,0,1,100);
        boule2.addSphere(2,0,0,1,100);

        boite.setMaterial(silver);
        boule1.setMaterial(ruby);
        boule2.setMaterial(redPlastic);

        //this->listPointCloud.push_back(boite);
        this->listPointCloud.push_back(boule1);
        this->listPointCloud.push_back(boule2);

        // this->listPointCloud.push_back(igea);
        // this->listPointCloud.push_back(dino);
        //this->listPointCloud.push_back(african_statue);
        // this->listPointCloud.push_back(face);

        // Help window
        // help();

        //
}


void displayElectricityPrice(int duration)
{
        constexpr double kPricePerKWh = 0.15; // Le prix d'un kilowattheure en euros
        constexpr double kPowerConsumption = 100.0; // La consommation en watts
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

void decimate(std::vector<Vec3>& positions, std::vector<Vec3>& normals, std::vector<char>& materialIndex, float keepingPart)
{
    // On commence par vérifier que la valeur de keepingPart est correcte
    if (keepingPart <= 0 || keepingPart > 1)
    {
        std::cerr << "Error: keepingPart must be a value between 0 and 1" << std::endl;
        return;
    }

    // On utilise un générateur de nombres aléatoires pour sélectionner les points à conserver
    std::mt19937 randomGenerator(time(nullptr));
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    // On parcours chaque point et on décide s'il doit être conservé ou non
    std::vector<Vec3> newPositions;
    std::vector<Vec3> newNormals;
    std::vector<char> newMaterialIndex;
    for (int i = 0; i < positions.size(); i++)
    {
        float randomNumber = distribution(randomGenerator);
        if (randomNumber <= keepingPart)
        {
            // On conserve le point et les informations associées
            newPositions.push_back(positions[i]);
            newNormals.push_back(normals[i]);
            newMaterialIndex.push_back(materialIndex[i]);
        }
    }

    positions.resize(newPositions.size());
    normals.resize(newNormals.size());
    materialIndex.resize(newMaterialIndex.size());

    for(int i = 0 ; i < newPositions.size() ; i ++){
        positions[i] = newPositions[i];
        normals[i] = newNormals[i];
        materialIndex[i] = newMaterialIndex[i];
    }
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


                //decimate(positions,normals, materialIndex, 0.1);
                
                pcd = getGPUpcd(positions, normals, materialIndex, materialList);
                
                
                cuda_ray_trace_from_camera(width, height, invmodelViewMat4.data(), invprojectionMat4.data(), {camPos.x,camPos.y,camPos.z} , pcd);

                std::cout<<"Rendu de "<<positions.size()<<" points"<<std::endl;
                playHappySound();
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