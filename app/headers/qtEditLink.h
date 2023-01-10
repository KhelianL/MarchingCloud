#ifndef QT_EDIT_LINK
#define QT_EDIT_LINK

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

    ~InterfaceQT();

    void setAlignCenter();

    void enableEdit(const bool &b);
    void updateViewerTarget(PointCloud &p);
    void resetViewerTarget();
};

#endif