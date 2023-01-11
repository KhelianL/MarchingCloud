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

    PointCloud *targetP;
    int indexP;

    void enableEdit(const bool &b);
    void updateViewerTarget();
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

    void updateEditAmbR(const QString &text);
    void updateEditAmbG(const QString &text);
    void updateEditAmbB(const QString &text);
    void updateEditDifR(const QString &text);
    void updateEditDifG(const QString &text);
    void updateEditDifB(const QString &text);
    void updateEditSpeR(const QString &text);
    void updateEditSpeG(const QString &text);
    void updateEditSpeB(const QString &text);
    void updateEditSpeExp(const QString &text);

    void updateEditMat(const QString &selected);
};

#endif