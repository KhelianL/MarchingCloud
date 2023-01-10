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

    // PointCloud targetP;

    void enableEdit(const bool &b);
    void updateViewerTarget(PointCloud &p);
    void resetViewerTarget();

    /* SIGNALS */
    void updateEditPosX(const QString &text);
    void updateEditPosY(const QString &text);
    void updateEditPosZ(const QString &text);
    void updateEditRotX(const QString &text);
    void updateEditRotY(const QString &text);
    void updateEditRotZ(const QString &text);
    void updateEditSclX(const QString &text);
    void updateEditSclY(const QString &text);
    void updateEditSclZ(const QString &text);

    void updateEditAmbR();
    void updateEditAmbG();
    void updateEditAmbB();
    void updateEditDifR();
    void updateEditDifG();
    void updateEditDifB();
    void updateEditSpeR();
    void updateEditSpeG();
    void updateEditSpeB();
    void updateEditSpeExp();

    void updateEditMat(const QString &selected);
};

#endif