#ifndef INTERFACE_QT_H
#define INTERFACE_QT_H

/* QT */
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>

/* SRC */
#include <pointCloud.h>

struct InterfaceQT
{
    QLineEdit *editPosX, *editPosY, *editPosZ;
    QLineEdit *editRotX, *editRotY, *editRotZ;
    QLineEdit *editSclX, *editSclY, *editSclZ;
    QLineEdit *editAmbR, *editAmbG, *editAmbB;
    QLineEdit *editDifR, *editDifG, *editDifB;
    QLineEdit *editSpeR, *editSpeG, *editSpeB;
    QLineEdit *editSpeExp;

    QLineEdit *editWidth;
    QLineEdit *editHeight;

    QComboBox *editMat;
    QProgressBar *progressBar;

    void init();

    void enableEdit(const bool &b);
    void updateViewerTarget(PointCloud &p);
    void resetViewerTarget();

    /* SIGNALS */
    void updateEditMat(const QString &selected);
};

#endif