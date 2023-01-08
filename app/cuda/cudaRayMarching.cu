/* C++ */
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>      // Sqrt
#include <algorithm>  // Sort
#include <functional> // Bind
#include <float.h>    // FLT_MAX
#include <fstream>    // save render
#include <string>     // name render

/* SRC */
#include <vec3.h>

/*#########################################*/
/*                 CudaVec3               #*/
/*#########################################*/

extern "C" struct CudaVec3
{
    float mVals[3];

    __device__ CudaVec3()
    {
        mVals[0] = 0.0;
        mVals[1] = 0.0;
        mVals[2] = 0.0;
    }
    __device__ CudaVec3(float x, float y, float z)
    {
        mVals[0] = x;
        mVals[1] = y;
        mVals[2] = z;
    }
    __device__ float squareLength() const
    {
        return mVals[0] * mVals[0] + mVals[1] * mVals[1] + mVals[2] * mVals[2];
    }
    __device__ float length() const
    {
        return sqrt(squareLength());
    }
    __device__ void normalize()
    {
        float L = length();
        mVals[0] /= L;
        mVals[1] /= L;
        mVals[2] /= L;
    }
    __device__ float &operator[](unsigned int c)
    {
        return mVals[c];
    }
    __device__ float operator[](unsigned int c) const
    {
        return mVals[c];
    }
    __device__ void operator=(CudaVec3 const &other)
    {
        mVals[0] = other[0];
        mVals[1] = other[1];
        mVals[2] = other[2];
    }
    __device__ void operator+=(CudaVec3 const &other)
    {
        mVals[0] += other[0];
        mVals[1] += other[1];
        mVals[2] += other[2];
    }
    __device__ void operator-=(CudaVec3 const &other)
    {
        mVals[0] -= other[0];
        mVals[1] -= other[1];
        mVals[2] -= other[2];
    }
    __device__ void operator*=(float s)
    {
        mVals[0] *= s;
        mVals[1] *= s;
        mVals[2] *= s;
    }
    __device__ void operator/=(float s)
    {
        mVals[0] /= s;
        mVals[1] /= s;
        mVals[2] /= s;
    }
};

__device__ CudaVec3 operator+(CudaVec3 const &a, CudaVec3 const &b)
{
    return CudaVec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}
__device__ CudaVec3 operator-(CudaVec3 const &a, CudaVec3 const &b)
{
    return CudaVec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}
__device__ CudaVec3 operator*(float a, CudaVec3 const &b)
{
    return CudaVec3(a * b[0], a * b[1], a * b[2]);
}
__device__ CudaVec3 operator*(CudaVec3 const &a, float b)
{
    return CudaVec3(b * a[0], b * a[1], b * a[2]);
}
__device__ CudaVec3 operator*(CudaVec3 const &a, CudaVec3 const &b)
{
    return CudaVec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}
__device__ CudaVec3 operator/(CudaVec3 const &a, float b)
{
    return CudaVec3(a[0] / b, a[1] / b, a[2] / b);
}
__device__ float dot(CudaVec3 const &a, CudaVec3 const &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
__device__ CudaVec3 cross(CudaVec3 const &a, CudaVec3 const &b)
{
    return CudaVec3(a[1] * b[2] - a[2] * b[1],
                    a[2] * b[0] - a[0] * b[2],
                    a[0] * b[1] - a[1] * b[0]);
}
__device__ CudaVec3 project(CudaVec3 point, CudaVec3 normalePlan, CudaVec3 pointPlan)
{
    return (point - dot(point - pointPlan, normalePlan) * normalePlan);
}

/*#########################################*/
/*#              CudaMaterial             #*/
/*#########################################*/

struct CudaMaterial
{
    CudaVec3 AMBIANT_COLOR;
    CudaVec3 DIFFUSE_COLOR;
    CudaVec3 SPECULAR_COLOR;

    int SPECULAR_EXPONENT = 32;
    float transparency = 0.0;
    float refractionIndex = 1.0;
};

/*#########################################*/
/*#                Outils                 #*/
/*#########################################*/

void mult(const float m[16], float x, float y, float z, float w, float &resX, float &resY, float &resZ, float &resW)
{
    resX = m[0] * x + m[4] * y + m[8] * z + m[12] * w;
    resY = m[1] * x + m[5] * y + m[9] * z + m[13] * w;
    resZ = m[2] * x + m[6] * y + m[10] * z + m[14] * w;
    resW = m[3] * x + m[7] * y + m[11] * z + m[15] * w;
}
Vec3 screen_space_to_worldSpace(float u, float v, float invModelViewMatrix[16], float invProjectionMatrix[16])
{
    // u et v sont entre 0 et 1 (0,0 est en haut à gauche de l'écran)
    float resInt[4];
    mult(invProjectionMatrix, (float)2.f * u - 1.f, -((float)2.f * v - 1.f), 0, (float)1.0, resInt[0], resInt[1], resInt[2], resInt[3]);
    float res[4];
    mult(invModelViewMatrix, resInt[0], resInt[1], resInt[2], resInt[3], res[0], res[1], res[2], res[3]);
    return Vec3(res[0] / res[3], res[1] / res[3], res[2] / res[3]);
}
__device__ int getGlobalIdx_1D_2D()
{
    return blockIdx.x * blockDim.x * blockDim.y + threadIdx.y * blockDim.x + threadIdx.x;
}

/*#########################################*/
/*                 KdTree                 #*/
/*#########################################*/

struct KdTreeNode
{
    int ind;
    float x, y, z;
    int axis;
    int left, right;

    KdTreeNode(int _ind, float _x, float _y, float _z, int _axis, int _left, int _right) : ind(_ind), x(_x), y(_y), z(_z), axis(_axis), left(_left), right(_right) {}
};

bool compareSortIndVec3(int axis, std::pair<int, Vec3> i, std::pair<int, Vec3> j)
{
    return (i.second[axis] < j.second[axis]);
}
std::vector<KdTreeNode> make_kd_tree(std::vector<Vec3> dots)
{
    std::vector<KdTreeNode> res;

    // les points à mettre dans le kd tree, on tri la partie qu'on veut au moment qu'on veut
    std::vector<std::pair<int, Vec3>> indVec = std::vector<std::pair<int, Vec3>>(dots.size()); // les points à mettre dans le kd tree, on tri la partie qu'on veut au moment qu'on veut

    for (int i = 0; i < dots.size(); i++)
    {
        indVec[i] = std::make_pair(i, dots[i]);
    }

    // Axe et Indice de début et de fin du tableau indVec
    std::queue<std::pair<int, std::pair<int, int>>> fileTraitement = std::queue<std::pair<int, std::pair<int, int>>>(); // Axe et Indice de début et de fin du tableau indVec

    fileTraitement.push(std::make_pair(0, std::make_pair(0, indVec.size())));
    int maxSize = 0;

    while (!fileTraitement.empty())
    {
        std::pair<int, int> plage = fileTraitement.front().second;
        int axis = fileTraitement.front().first;

        fileTraitement.pop();

        std::sort(indVec.begin() + plage.first, indVec.begin() + plage.second, std::bind(compareSortIndVec3, axis, std::placeholders::_1, std::placeholders::_2));

        int med = (plage.first + plage.second) / 2;

        int left;
        int right;

        if (plage.second - plage.first > 1)
        {
            left = ++maxSize;
            right = ++maxSize;
        }
        else if (plage.second - plage.first == 1)
        {
            left = -1;
            right = ++maxSize;
        }
        else
        {
            left = -1;
            right = -1;
        }

        res.push_back(KdTreeNode(
            indVec[med].first,
            indVec[med].second[0],
            indVec[med].second[1],
            indVec[med].second[2],
            axis,
            left,
            right));

        if (left != -1 && right != -1)
        {
            fileTraitement.push(std::make_pair((axis + 1) % 3, std::make_pair(plage.first, med)));
            fileTraitement.push(std::make_pair((axis + 1) % 3, std::make_pair(med, plage.second)));
        }
        else if (right != -1 && left == -1)
        {
            fileTraitement.push(std::make_pair((axis + 1) % 3, std::make_pair(med, med)));
        }
    }
    return res;
}
KdTreeNode *send_kd_tree(std::vector<KdTreeNode> kd_tree)
{
    KdTreeNode *res = NULL;

    cudaMalloc(&res, kd_tree.size() * sizeof(KdTreeNode));
    cudaMemcpy(res, (void *)kd_tree.data(), kd_tree.size() * sizeof(KdTreeNode), cudaMemcpyHostToDevice);

    return res;
}

/*#########################################*/
/*               PointQueue               #*/
/*#########################################*/

const int MAX_STACK_SIZE = 1000;

struct PointQueue
{
    int size;
    int nbInQueue;

    int *ind;
    float *dist;
};

__device__ inline float square(float f)
{
    return f * f;
}
__device__ void initPointQueue(PointQueue *ptc, int nb)
{
    ptc->size = nb;
    ptc->nbInQueue = 0;

    ptc->ind = (int *)malloc(nb * sizeof(int));
    ptc->dist = (float *)malloc(nb * sizeof(float));

    for (int i = 0; i < nb; i++)
    {
        ptc->dist[i] = -1.0;
        ptc->ind[i] = 0;
    }
}
__device__ void freePointQueue(PointQueue *ptc)
{
    free(ptc->ind);
    free(ptc->dist);
}
__device__ float getThresholdDist(PointQueue *queue)
{
    if (queue->nbInQueue == queue->size)
    {
        return queue->dist[queue->size - 1];
    }
    return -1;
}
__device__ void addToPointQueue(PointQueue *queue, int index, float distance)
{
    // c'est bien moi qui ai écrit cette fonction, elle a seulement été commentée par chatGPT

    // Ajoute un élément (un indice et une distance) à une file d'attente structurée en utilisant un algorithme de tri par insertion.
    //
    // queue: pointeur vers la file d'attente à laquelle ajouter l'élément
    // index: indice de l'élément à ajouter à la file d'attente
    // distance: distance de l'élément à ajouter à la file d'attente

    // variables temporaires pour stocker l'indice et la distance passés en paramètre
    int currentIndex = index;
    float currentDistance = distance;

    // itère à travers tous les éléments de la file d'attente
    for (int i = 0; i < queue->nbInQueue; i++)
    {
        // si la distance de l'élément de la file d'attente est négative ou si la distance passée en paramètre est inférieure à celle de l'élément de la file d'attente
        if (queue->dist[i] < 0 || currentDistance < queue->dist[i])
        {
            // échange l'élément de la file d'attente avec l'indice et la distance temporaires
            int tempIndex = queue->ind[i];
            float tempDistance = queue->dist[i];

            queue->ind[i] = currentIndex;
            queue->dist[i] = currentDistance;

            currentIndex = tempIndex;
            currentDistance = tempDistance;
        }
    }

    // si la file d'attente n'est pas pleine, ajoute l'indice et la distance temporaires à la fin de la file d'attente et incrémente nbInQueue
    if (queue->nbInQueue < queue->size)
    {
        queue->ind[queue->nbInQueue] = currentIndex;
        queue->dist[queue->nbInQueue] = currentDistance;

        queue->nbInQueue++;
    }
}
__device__ void fillQueue(KdTreeNode *kd_tree, PointQueue *queue, int currentInd, int currentAxis, float pointX, float pointY, float pointZ)
{
    int stack[MAX_STACK_SIZE];
    int stackPointer = 0;
    stack[stackPointer++] = 0;
    stack[stackPointer++] = 0;

    while (stackPointer > 0)
    {
        int currentAxis = stack[--stackPointer];
        int currentInd = stack[--stackPointer];

        float currentSqDist = square(kd_tree[currentInd].x - pointX) + square(kd_tree[currentInd].y - pointY) + square(kd_tree[currentInd].z - pointZ);
        float threshold = getThresholdDist(queue);

        int pointIndex = kd_tree[currentInd].ind;
        if (threshold < 0 || currentSqDist < threshold)
        {
            addToPointQueue(queue, pointIndex, currentSqDist);
        }

        int bestSide = 0;
        int otherSide = 0;

        if (kd_tree[currentInd].left == -1 || (currentAxis == 0 && kd_tree[currentInd].x < pointX) ||
            (currentAxis == 1 && kd_tree[currentInd].y < pointY) || (currentAxis == 2 && kd_tree[currentInd].z < pointZ))
        {
            bestSide = kd_tree[currentInd].left;
            otherSide = kd_tree[currentInd].right;
        }
        else
        {
            bestSide = kd_tree[currentInd].right;
            otherSide = kd_tree[currentInd].left;
        }

        if (bestSide != -1)
        {
            stack[stackPointer++] = bestSide;
            stack[stackPointer++] = (currentAxis + 1) % 3;
        }

        threshold = getThresholdDist(queue);

        if (otherSide != -1 &&
            ((currentAxis == 0 && (threshold < 0 || square(pointX - kd_tree[otherSide].x) < threshold)) ||
             (currentAxis == 1 && (threshold < 0 || square(pointY - kd_tree[otherSide].y) < threshold)) ||
             (currentAxis == 2 && (threshold < 0 || square(pointZ - kd_tree[otherSide].z) < threshold))))
        {
            stack[stackPointer++] = otherSide;
            stack[stackPointer++] = (currentAxis + 1) % 3;
        }
    }
}

/*#########################################*/
/*               PointCloud               #*/
/*#########################################*/

struct PointCloudData
{
    KdTreeNode *kdTree;
    char *materialIndex;
    CudaMaterial *materialList;
    CudaVec3 *positions;
    CudaVec3 *normals;
};
struct cIntersection
{
    bool intersected;
    CudaVec3 position;
    float convTime;
};

__device__ PointQueue *knearest(KdTreeNode *kd_tree, float pointX, float pointY, float pointZ, int nbNeighbors)
{
    PointQueue *queue = (PointQueue *)malloc(sizeof(PointQueue));
    initPointQueue(queue, nbNeighbors);

    int currentInd = 0; // indice du noeud du kd_tree
    int currentAxis = 0;

    fillQueue(kd_tree, queue, currentInd, currentAxis, pointX, pointY, pointZ);

    return queue;
}
__device__ void computeKnn(int *indTab, float *sqDistTab, KdTreeNode *kd_tree, int nb, float x, float y, float z)
{
    PointQueue *resQueue = knearest(kd_tree, x, y, z, nb);

    for (int i = 0; i < nb; i++)
    {
        indTab[i] = resQueue->ind[i];
        sqDistTab[i] = resQueue->dist[i];
    }

    freePointQueue(resQueue);
    free(resQueue);
}
__device__ int findNearest(KdTreeNode *tree, CudaVec3 point)
{
    int currNode = 0;
    int bestNode = 0;
    float bestDistance = FLT_MAX;

    while (currNode >= 0)
    {
        KdTreeNode node = tree[currNode];
        CudaVec3 nodePoint = CudaVec3(node.x, node.y, node.z);

        float distance = (nodePoint - point).length();

        if (distance < bestDistance)
        {
            bestDistance = distance;
            bestNode = node.ind;
        }

        int nextNode;
        if (point[node.axis] < nodePoint[node.axis])
        {
            nextNode = node.left;
        }
        else
        {
            nextNode = node.right;
        }

        if (nextNode >= 0)
        {
            KdTreeNode next = tree[nextNode];
            CudaVec3 nextNodePoint = CudaVec3(next.x, next.y, next.z);

            float axisDistance = nextNodePoint[node.axis] - point[node.axis];
            float axisDistanceSq = axisDistance * axisDistance;
            if (axisDistanceSq < bestDistance)
            {
                currNode = nextNode;
            }
            else
            {
                currNode = -1;
            }
        }
        else
        {
            currNode = -1;
        }
    }

    return bestNode;
}
__device__ float HPSSDist(CudaVec3 inputPoint, PointCloudData pcd)
{
    int kerneltype = 0;
    float h = 100;
    unsigned int nbIterations = 4;
    const unsigned int knn = 10;

    int *id_nearest_neighbors = (int *)malloc(knn * sizeof(int));
    float *square_distances_to_neighbors = (float *)malloc(knn * sizeof(float));

    CudaVec3 precPoint = inputPoint;
    CudaVec3 nextPoint;
    CudaVec3 nextNormal;

    for (int itt = 0; itt < nbIterations; itt++)
    {
        computeKnn(id_nearest_neighbors, (float *)square_distances_to_neighbors, pcd.kdTree, knn, precPoint[0], precPoint[1], precPoint[2]);

        nextPoint = CudaVec3();
        nextNormal = CudaVec3();

        float totWeight = 0.0;

        for (int i = 0; i < knn; i++)
        {
            CudaVec3 proj = project(precPoint, pcd.normals[id_nearest_neighbors[i]], pcd.positions[id_nearest_neighbors[i]]);
            float weight = 0.0;
            float r = sqrt(square_distances_to_neighbors[i]) / h;
            switch (kerneltype)
            {
            case 0:

                weight = exp((-(r * r)) / (h * h));
                break;
            case 1:
                weight = 0;
                break;
            case 2:
                weight = 0;
                break;
            }
            totWeight += weight;
            nextPoint += weight * proj;
            nextNormal += weight * pcd.normals[id_nearest_neighbors[i]];
        }
        nextPoint = nextPoint / totWeight;
        nextNormal.normalize();
        precPoint = nextPoint;
    }

    free(id_nearest_neighbors);
    free(square_distances_to_neighbors);

    return (dot(inputPoint - nextPoint, nextNormal));
}
__device__ cIntersection intersect(CudaVec3 pos, CudaVec3 dir, PointCloudData pcd)
{
    float seuilMin = 0.01;
    float seuilMax = 10;

    int maxItt = 50;

    bool conv = false;

    int i = 0;
    for (int i = 0; i < maxItt; i++)
    {
        float dist = abs(HPSSDist(pos, pcd));

        if (dist > seuilMax)
        {
            break;
        }
        else if (dist < seuilMin)
        {
            conv = true;
            break;
        }
        else
        {
            pos += dist * dir;
        }
    }
    return {conv, pos, (float)i / (float)maxItt};
}
__device__ CudaVec3 normale(CudaVec3 pos, PointCloudData pcd)
{
    CudaVec3 eps1 = CudaVec3(0.01, 0., 0.);
    CudaVec3 eps2 = CudaVec3(0., 0.01, 0.);
    CudaVec3 eps3 = CudaVec3(0., 0., 0.01);

    CudaVec3 res = CudaVec3(
        HPSSDist(pos + eps1, pcd) - HPSSDist(pos - eps1, pcd),
        HPSSDist(pos + eps2, pcd) - HPSSDist(pos - eps2, pcd),
        HPSSDist(pos + eps3, pcd) - HPSSDist(pos - eps3, pcd));

    res.normalize();

    return res;
}

extern "C" PointCloudData getGPUpcd(std::vector<Vec3> positions, std::vector<Vec3> normals, std::vector<char> materialIndex, std::vector<CudaMaterial> materialList)
{
    PointCloudData res;

    // Allouer de la mémoire sur le GPU pour les champs positions, normals, materialIndex et materialList de la structure PointCloudData
    cudaMalloc(&(res.positions), positions.size() * sizeof(Vec3));
    cudaMalloc(&(res.normals), normals.size() * sizeof(Vec3));
    cudaMalloc(&(res.materialIndex), materialIndex.size() * sizeof(char));
    cudaMalloc(&(res.materialList), materialList.size() * sizeof(CudaMaterial));

    // Copier les données depuis le CPU vers le GPU
    cudaMemcpy(res.positions, (void *)positions.data(), positions.size() * sizeof(Vec3), cudaMemcpyHostToDevice);
    cudaMemcpy(res.normals, (void *)normals.data(), normals.size() * sizeof(Vec3), cudaMemcpyHostToDevice);
    cudaMemcpy(res.materialIndex, (void *)materialIndex.data(), materialIndex.size() * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(res.materialList, (void *)materialList.data(), materialList.size() * sizeof(CudaMaterial), cudaMemcpyHostToDevice);

    std::cout << "Start kd-tree building" << std::endl;
    // Construire l'arbre kd à partir des positions sur le CPU et l'envoyer sur le GPU
    std::vector<KdTreeNode> my_kd_tree = make_kd_tree(positions);
    res.kdTree = send_kd_tree(my_kd_tree);
    std::cout << "End kd-tree building" << std::endl;

    return res;
}

/*#########################################*/
/*               RayMarching              #*/
/*#########################################*/

__device__ CudaVec3 computeColor(CudaVec3 positionCamera, CudaVec3 positionPoint, CudaVec3 normalePoint, CudaVec3 positionLumiere, CudaMaterial &material)
{
    // Calcul de la direction de la lumière
    CudaVec3 directionLumiere = positionLumiere - positionPoint;
    directionLumiere.normalize();

    // Calcul de la direction de la caméra
    CudaVec3 directionCamera = positionCamera - positionPoint;
    directionCamera.normalize();

    // Calcul de la normale moyenne
    CudaVec3 normaleMoyenne = directionLumiere + directionCamera;
    normaleMoyenne.normalize();

    // Calcul de l'intensité de la lumière en utilisant l'éclairage de Blinn-Phong
    float intensiteLumiere = fmax(dot(normalePoint, directionLumiere), 0.0f);
    float specular = pow(fmax(dot(normalePoint, normaleMoyenne), 0.0f), material.SPECULAR_EXPONENT);

    // Calcul de la couleur finale en utilisant les composantes ambiante, diffuse et spéculaire
    CudaVec3 couleurFinale = material.AMBIANT_COLOR + intensiteLumiere * material.DIFFUSE_COLOR + specular * material.SPECULAR_COLOR;

    return couleurFinale;
}

__device__ CudaVec3 computeReflection(const CudaVec3 &ray, const CudaVec3 &normal)
{
    // Calculer la composante parallèle et perpendiculaire du rayon par rapport à la normale
    float dotProduct = dot(ray, normal);
    CudaVec3 parallel = normal * dotProduct;
    CudaVec3 perpendicular = ray - parallel;

    // Calculer le vecteur de réflexion
    CudaVec3 reflection = perpendicular - parallel;
    reflection.normalize();
    return reflection;
}
__device__ CudaVec3 computeTransmission(const CudaVec3 &ray, const CudaVec3 &normal, const CudaVec3 &intersection, float refractionIndex)
{
    // Calculer la composante parallèle et perpendiculaire du rayon par rapport à la normale
    float dotProduct = dot(ray, normal);
    CudaVec3 parallel = normal * dotProduct;
    CudaVec3 perpendicular = ray - parallel;

    // Calculer l'indice de réfraction du milieu d'où vient le rayon (ici, l'air avec un indice de réfraction de 1)
    float n1 = 1.0;
    // Calculer l'indice de réfraction du matériau au point d'intersection
    float n2 = refractionIndex;

    // Calculer le coefficient de réflexion et de transmission
    float reflectionCoefficient = (n1 - n2) / (n1 + n2);
    reflectionCoefficient *= reflectionCoefficient;
    // float transmissionCoefficient = 1.0 - reflectionCoefficient;

    // Calculer le vecteur de transmission
    CudaVec3 transmission = (perpendicular * n1 - normal * sqrt(1.0 - reflectionCoefficient)) * n2 + parallel;
    transmission.normalize();
    return transmission;
}
__device__ CudaVec3 mix(CudaVec3 color1, CudaVec3 color2, float mixFactor)
{
    return color1 * (1.0 - mixFactor) + color2 * mixFactor;
}

__global__ void cuda_ray_trace(int startIndex, float *rayPos, float *rayDir, float *image, int imgSize, PointCloudData pcd, int maxTransparencyIterations = 0)
{
    int index = getGlobalIdx_1D_2D()+startIndex;

    if (index < imgSize)
    {
        CudaVec3 pos = CudaVec3(rayPos[0], rayPos[1], rayPos[2]);
        CudaVec3 dir = CudaVec3(rayDir[index * 3 + 0], rayDir[index * 3 + 1], rayDir[index * 3 + 2]);

        cIntersection it = intersect(pos, dir, pcd);

        if (it.intersected)
        {
            int nearestPoint = findNearest(pcd.kdTree, it.position);

            CudaVec3 norm = normale(it.position, pcd);

            CudaVec3 color = computeColor(pos, it.position, norm, CudaVec3(0, 4, 0), pcd.materialList[pcd.materialIndex[nearestPoint]]);

            // Transparence
            float transparency = pcd.materialList[pcd.materialIndex[nearestPoint]].transparency;

            // Nombre d'itérations de transparence
            int transparencyIterations = 0;

            while (transparency > 0.0 && transparencyIterations < maxTransparencyIterations)
            {
                // Calculer le vecteur de transmission
                dir = computeTransmission(dir, norm, it.position, pcd.materialList[pcd.materialIndex[nearestPoint]].refractionIndex);
                // Lancer un nouveau rayon de transmission
                cIntersection it2 = intersect(it.position + dir * 0.01, dir, pcd);
                if (it2.intersected)
                {
                    // Si le nouveau rayon de transmission intersecte un autre objet, combiner les couleurs
                    int nearestPoint2 = findNearest(pcd.kdTree, it2.position);
                    norm = normale(it2.position, pcd);
                    CudaVec3 color2 = computeColor(it.position, it2.position, norm, CudaVec3(1, 1, 1), pcd.materialList[pcd.materialIndex[nearestPoint2]]);
                    color = mix(color, color2, transparency);
                    // Mettre à jour la transparence et le nombre d'itérations
                    transparency = pcd.materialList[pcd.materialIndex[nearestPoint2]].transparency;
                    transparencyIterations++;
                }
                else
                {
                    // Sinon, utiliser la couleur du fond
                    color = mix(color, CudaVec3(0.1, 0.1, 0.1), transparency);
                    // Mettre à jour la transparence et le nombre d'itérations
                    transparency = 0.0;
                    transparencyIterations++;
                }
            }

            image[index * 3 + 0] = color[0] > 1.0 ? 1.0 : color[0] < 0.0 ? 0.0
                                                                         : color[0];
            image[index * 3 + 1] = color[1] > 1.0 ? 1.0 : color[1] < 0.0 ? 0.0
                                                                         : color[1];
            image[index * 3 + 2] = color[2] > 1.0 ? 1.0 : color[2] < 0.0 ? 0.0
                                                                         : color[2];
        }
        else
        {
            image[index * 3 + 0] = 0.1;
            image[index * 3 + 1] = 0.1;
            image[index * 3 + 2] = 0.1;
        }
    }
}

extern "C" void cuda_ray_trace_from_camera(int w, int h, float ModelViewMatrix[16], float projectionMatrix[16], Vec3 cameraPos, PointCloudData pcd)
{

    std::vector<float> image(3 * w * h, 0.5f);
    std::vector<float> rayDir(3 * w * h);

    std::cout << "Ray tracing a " << w << " x " << h << " image" << std::endl;

    // Init
    Vec3 pos = cameraPos;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float u = ((float)(x) + (float)(rand()) / (float)(RAND_MAX)) / w;
            float v = ((float)(y) + (float)(rand()) / (float)(RAND_MAX)) / h;

            Vec3 dir = screen_space_to_worldSpace(u, v, ModelViewMatrix, projectionMatrix) - pos;
            dir.normalize();

            rayDir[3 * (y * w + x) + 0] = dir[0];
            rayDir[3 * (y * w + x) + 1] = dir[1];
            rayDir[3 * (y * w + x) + 2] = dir[2];
        }
    }

    float *cudaDirTab;
    cudaMalloc(&cudaDirTab, 3 * rayDir.size() * sizeof(float));

    float *cudaImage;
    cudaMalloc(&cudaImage, 3 * image.size() * sizeof(float));

    float *cudaPos;
    cudaMalloc(&cudaPos, 3 * sizeof(float));

    cudaMemcpy(cudaDirTab, (void *)rayDir.data(), rayDir.size() * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(cudaImage, (void *)image.data(), image.size() * sizeof(float), cudaMemcpyHostToDevice);

    cudaMemcpy(cudaPos, &pos, 3 * sizeof(float), cudaMemcpyHostToDevice);

    std::cout << "w : " << w << " h : " << h << " w*h : " << w * h << std::endl;

    int nbth = 5;

    // cuda_ray_trace<<<h,w>>>(cudaPos, cudaDirTab, cudaImage, w);

    int nbBlock = std::ceil((w * h) / (nbth * nbth));
    // nbBlock = 5;

    std::cout << "Nb block : " << nbBlock << std::endl;

    dim3 threadsPerBlock(nbth, nbth);

    
    // dim3 numBlocks(nbBlock, 1);
    // cuda_ray_trace<<<numBlocks, threadsPerBlock>>>(cudaPos, cudaDirTab, cudaImage, h * w, pcd);
    // cudaMemcpy((void *)image.data(), (void *)cudaImage, image.size() * sizeof(float), cudaMemcpyDeviceToHost);
    

    int nbsteps = 10;   
    int blockPerSteps = nbBlock/nbsteps;
    dim3 numBlocks(blockPerSteps, 1);

    int nextInd = 0;
    int i = 0;
    while(nextInd < nbBlock * (nbth * nbth)){
        cuda_ray_trace<<<numBlocks, threadsPerBlock>>>(nextInd, cudaPos, cudaDirTab, cudaImage, h * w, pcd);
        cudaDeviceSynchronize();
        i += 100/nbsteps;
        std::cout<<i<<"%"<<std::endl;
        nextInd += blockPerSteps * (nbth * nbth);
    }

    cudaMemcpy((void *)image.data(), (void *)cudaImage, image.size() * sizeof(float), cudaMemcpyDeviceToHost);


    std::string filename = "./rendu.ppm";

    std::ofstream f(filename.c_str(), std::ios::binary);

    if (f.fail())
    {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }
    f << "P3" << std::endl
      << w << " " << h << std::endl
      << 255 << std::endl;
    for (int i = 0; i < w * h; i++)
        f << (int)(255.f * std::min<float>(1.f, image[i * 3 + 0])) << " " << (int)(255.f * std::min<float>(1.f, image[i * 3 + 1])) << " " << (int)(255.f * std::min<float>(1.f, image[i * 3 + 2])) << " ";
    f << std::endl;
    f.close();

    // Reset img
    image.clear();
    image.resize(w * h * 3);
    fill(image.begin(), image.end(), 0.0f);
}



/*
            // Transparence
            float transparency = pcd.materialList[pcd.materialIndex[nearestPoint]].transparency;

            // Nombre d'itérations de transparence
            int transparencyIterations = 0;

            while (transparency > 0.0 && transparencyIterations < maxTransparencyIterations)
            {
                // Calculer le vecteur de transmission
                dir = computeTransmission(dir, norm, it.position, pcd.materialList[pcd.materialIndex[nearestPoint]].refractionIndex);
                // Lancer un nouveau rayon de transmission
                cIntersection it2 = intersect(it.position + dir * 0.01, dir, pcd);
                if (it2.intersected)
                {
                    // Si le nouveau rayon de transmission intersecte un autre objet, combiner les couleurs
                    int nearestPoint2 = findNearest(pcd.kdTree, it2.position);
                    norm = normale(it2.position, pcd);
                    CudaVec3 color2 = computeColor(it.position, it2.position, norm, CudaVec3(1, 1, 1), pcd.materialList[pcd.materialIndex[nearestPoint2]]);
                    color = mix(color, color2, transparency);
                    // Mettre à jour la transparence et le nombre d'itérations
                    transparency = pcd.materialList[pcd.materialIndex[nearestPoint2]].transparency;
                    transparencyIterations++;
                }
                else
                {
                    // Sinon, utiliser la couleur du fond
                    color = mix(color, CudaVec3(0.1, 0.1, 0.1), transparency);
                    // Mettre à jour la transparence et le nombre d'itérations
                    transparency = 0.0;
                    transparencyIterations++;
                }
            }
            */