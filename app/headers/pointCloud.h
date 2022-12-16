#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <fstream>
#include <string>

// QT
#include <QVector>

// libQGLViewer 
#include <QGLViewer/vec.h>

class PointCloud
{
private:
    QVector<qglviewer::Vec> positions;
    QVector<qglviewer::Vec> normals;

public:
    void draw();
    void print();
    void loadPointCloud(const std::string &filename);
    void savePointCloud(const std::string &filename);
};

#endif