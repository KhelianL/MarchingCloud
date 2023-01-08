#ifndef QT_EDIT_LINK
#define QT_EDIT_LINK

/* QT */
#include <QLineEdit>
#include <QProgressBar>

/* SRC */
#include <pointCloud.h>

struct InterfaceQT
{
    QLineEdit *editPosX, *editPosY, *editPosZ, *editRotX, *editRotY, *editRotZ, *editSclX, *editSclY, *editSclZ, *editAmbR, *editAmbG, *editAmbB, *editDifR, *editDifG, *editDifB, *editSpeR, *editSpeG, *editSpeB, *editSpeExp, *editWidth, *editHeight;
    QProgressBar *progressBar;

    InterfaceQT(QLineEdit *editPosX, QLineEdit *editPosY, QLineEdit *editPosZ, QLineEdit *editRotX, QLineEdit *editRotY, QLineEdit *editRotZ, QLineEdit *editSclX, QLineEdit *editSclY, QLineEdit *editSclZ, QLineEdit *editAmbR, QLineEdit *editAmbG, QLineEdit *editAmbB, QLineEdit *editDifR, QLineEdit *editDifG, QLineEdit *editDifB, QLineEdit *editSpeR, QLineEdit *editSpeG, QLineEdit *editSpeB, QLineEdit *editSpeExp, QProgressBar *progressBar);
    ~InterfaceQT();

    void setAlignCenter();
    void enableEdit(bool b);
    void setProgress(int n);

    void updateViewerTarget(PointCloud *pc);
};

#endif