#include <tools.h>

std::string displayElectricityPrice(int duration)
{
    // Le prix d'un kilowattheure en euros
    constexpr double kPricePerKWh = 0.15;
    // La consommation en watts
    constexpr double kPowerConsumption = 100.0;
    // Convertir la durée en heures
    double durationInHours = static_cast<double>(duration) / 3600.0;
    // Calculer la consommation en kilowattheures
    double consumptionInKWh = kPowerConsumption * durationInHours / 1000.0;
    // Calculer le prix en euros
    double price = consumptionInKWh * kPricePerKWh;
    // Convertir le prix en centimes d'euros
    float priceInCents = price * 100.0;

    return "Le rendu a duré " + std::to_string(duration) + " secondes et a couté " + std::to_string(priceInCents) + " centimes d'euros.";
}

/* ********** EXTERN_CUDA ********** */

struct CudaVec3
{
    float mVals[3];

    CudaVec3()
    {
        mVals[0] = 0.0;
        mVals[1] = 0.0;
        mVals[2] = 0.0;
    }
    CudaVec3(float x, float y, float z)
    {
        mVals[0] = x;
        mVals[1] = y;
        mVals[2] = z;
    }
    CudaVec3(Vec3 &v)
    {
        mVals[0] = v.getX();
        mVals[1] = v.getY();
        mVals[2] = v.getZ();
    }
    float squareLength() const
    {
        return mVals[0] * mVals[0] + mVals[1] * mVals[1] + mVals[2] * mVals[2];
    }
    float length() const
    {
        return sqrt(squareLength());
    }
    void normalize()
    {
        float L = length();
        mVals[0] /= L;
        mVals[1] /= L;
        mVals[2] /= L;
    }
    static float dot(CudaVec3 const &a, CudaVec3 const &b)
    {
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
    }
    static CudaVec3 cross(CudaVec3 const &a, CudaVec3 const &b)
    {
        return CudaVec3(a[1] * b[2] - a[2] * b[1],
                        a[2] * b[0] - a[0] * b[2],
                        a[0] * b[1] - a[1] * b[0]);
    }
    static CudaVec3 project(CudaVec3 point, CudaVec3 normalePlan, CudaVec3 pointPlan)
    {
        return (point - dot(point - pointPlan, normalePlan) * normalePlan);
    }
    float &operator[](unsigned int c)
    {
        return mVals[c];
    }
    float operator[](unsigned int c) const
    {
        return mVals[c];
    }
    void operator=(CudaVec3 const &other)
    {
        mVals[0] = other[0];
        mVals[1] = other[1];
        mVals[2] = other[2];
    }
    void operator+=(CudaVec3 const &other)
    {
        mVals[0] += other[0];
        mVals[1] += other[1];
        mVals[2] += other[2];
    }
    void operator-=(CudaVec3 const &other)
    {
        mVals[0] -= other[0];
        mVals[1] -= other[1];
        mVals[2] -= other[2];
    }
    void operator*=(float s)
    {
        mVals[0] *= s;
        mVals[1] *= s;
        mVals[2] *= s;
    }
    void operator/=(float s)
    {
        mVals[0] /= s;
        mVals[1] /= s;
        mVals[2] /= s;
    }
    friend CudaVec3 operator+(CudaVec3 const &a, CudaVec3 const &b)
    {
        return CudaVec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
    }
    friend CudaVec3 operator-(CudaVec3 const &a, CudaVec3 const &b)
    {
        return CudaVec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
    }
    friend CudaVec3 operator*(float a, CudaVec3 const &b)
    {
        return CudaVec3(a * b[0], a * b[1], a * b[2]);
    }
    friend CudaVec3 operator*(CudaVec3 const &a, float b)
    {
        return CudaVec3(b * a[0], b * a[1], b * a[2]);
    }
    friend CudaVec3 operator*(CudaVec3 const &a, CudaVec3 const &b)
    {
        return CudaVec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
    }
    friend CudaVec3 operator/(CudaVec3 const &a, float b)
    {
        return CudaVec3(a[0] / b, a[1] / b, a[2] / b);
    }
};
extern "C" struct CudaMaterial
{
    CudaVec3 AMBIANT_COLOR;
    CudaVec3 DIFFUSE_COLOR;
    CudaVec3 SPECULAR_COLOR;

    int SPECULAR_EXPONENT = 32;
    float transparency = 0.0;
    float refractionIndex = 1.0;

    CudaMaterial(Material &m) : AMBIANT_COLOR(CudaVec3(m.getAmbiant())),
                                DIFFUSE_COLOR(CudaVec3(m.getDiffuse())),
                                SPECULAR_COLOR(CudaVec3(m.getSpecular())),
                                SPECULAR_EXPONENT(m.getSpecExp()),
                                transparency(m.getTransparency()),
                                refractionIndex(m.getRefractionIndex())
    {
    }
};
extern "C" struct KdTreeNode
{
    int ind;
    float x, y, z;
    int axis;
    int left, right;

    KdTreeNode(int _ind, float _x, float _y, float _z, int _axis, int _left, int _right) : ind(_ind), x(_x), y(_y), z(_z), axis(_axis), left(_left), right(_right) {}
};
extern "C" struct PointCloudData
{
    KdTreeNode *kdTree;
    char *materialIndex;
    CudaMaterial *materialList;
    CudaVec3 *positions;
    CudaVec3 *normals;
};
extern "C" void cuda_ray_trace_from_camera(int w, int h, float ModelViewMatrix[16], float projectionMatrix[16], Vec3 cameraPos, PointCloudData pcd);
extern "C" PointCloudData getGPUpcd(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<char> materialIndex, std::vector<CudaMaterial> materialList);

/* ********** EXTERN_CUDA ********** */

void linkToCuda(std::vector<PointCloud> scenePointCloud, int width, int height, float ModelViewMatrix[16], float projectionMatrix[16], Vec3 cameraPos)
{
    // Concatenate every informations into a PointCloud
    std::vector<Vec3> concat_positions;
    std::vector<Vec3> concat_normals;
    std::vector<char> concat_materialIndex;
    std::vector<CudaMaterial> concat_materialList;

    for (int i = 0, sizeMax = scenePointCloud.size(); i < sizeMax; i++)
    {
        QMatrix4x4 mat = scenePointCloud[i].getModelMatrix();
        std::vector<Vec3> p = scenePointCloud[i].getPositions();
        std::vector<Vec3> n = scenePointCloud[i].getNormals();

        for (int j = 0, sizeMax = scenePointCloud[i].getPositions().size(); j < sizeMax; j++)
        {
            p[j] = Vec3::multMat4(mat.data(), p[j]);
            n[j] = Vec3::multMat4N(mat.data(), n[j]);
            n[j].normalize();
        }

        concat_positions.insert(concat_positions.end(), p.begin(), p.end());
        concat_normals.insert(concat_normals.end(), n.begin(), n.end());
        concat_materialIndex.insert(concat_materialIndex.end(), p.size(), i);
        concat_materialList.push_back(CudaMaterial(scenePointCloud[i].getMaterial()));
    }

    PointCloudData pcd;
    pcd = getGPUpcd(concat_positions, concat_normals, concat_materialIndex, concat_materialList);

    std::chrono::time_point<std::chrono::high_resolution_clock> l_clock = std::chrono::high_resolution_clock::now();
    cuda_ray_trace_from_camera(width, height, ModelViewMatrix, projectionMatrix, cameraPos, pcd);
    std::cout << "Rendu de " << concat_positions.size() << " points" << std::endl;

    std::string t = displayElectricityPrice(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - l_clock).count() / 1000);
    std::cout << t << std::endl;
}