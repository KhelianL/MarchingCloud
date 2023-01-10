#include <interfaceQT.h>

void InterfaceQT::init()
{
    // Align
    this->editPosX->setAlignment(Qt::AlignCenter);
    this->editPosY->setAlignment(Qt::AlignCenter);
    this->editPosZ->setAlignment(Qt::AlignCenter);
    this->editRotX->setAlignment(Qt::AlignCenter);
    this->editRotY->setAlignment(Qt::AlignCenter);
    this->editRotZ->setAlignment(Qt::AlignCenter);
    this->editSclX->setAlignment(Qt::AlignCenter);
    this->editSclY->setAlignment(Qt::AlignCenter);
    this->editSclZ->setAlignment(Qt::AlignCenter);
    this->editAmbR->setAlignment(Qt::AlignCenter);
    this->editAmbG->setAlignment(Qt::AlignCenter);
    this->editAmbB->setAlignment(Qt::AlignCenter);
    this->editDifR->setAlignment(Qt::AlignCenter);
    this->editDifG->setAlignment(Qt::AlignCenter);
    this->editDifB->setAlignment(Qt::AlignCenter);
    this->editSpeR->setAlignment(Qt::AlignCenter);
    this->editSpeG->setAlignment(Qt::AlignCenter);
    this->editSpeB->setAlignment(Qt::AlignCenter);
    this->editSpeExp->setAlignment(Qt::AlignCenter);
    this->enableEdit(false);
}

void InterfaceQT::enableEdit(const bool &b)
{
    this->editPosX->setEnabled(b);
    this->editPosY->setEnabled(b);
    this->editPosZ->setEnabled(b);
    this->editRotX->setEnabled(b);
    this->editRotY->setEnabled(b);
    this->editRotZ->setEnabled(b);
    this->editSclX->setEnabled(b);
    this->editSclY->setEnabled(b);
    this->editSclZ->setEnabled(b);
    this->editAmbR->setEnabled(b);
    this->editAmbG->setEnabled(b);
    this->editAmbB->setEnabled(b);
    this->editDifR->setEnabled(b);
    this->editDifG->setEnabled(b);
    this->editDifB->setEnabled(b);
    this->editSpeR->setEnabled(b);
    this->editSpeG->setEnabled(b);
    this->editSpeB->setEnabled(b);
    this->editMat->setEnabled(b);
    this->editSpeExp->setEnabled(b);
}
void InterfaceQT::updateViewerTarget(PointCloud &p)
{
    // TODO : UPDATE LES POSITIONS ?
    // TODO : SAVE LE POINTCLOUD TARGET

    Material &m = p.getMaterial();
    Vec3 &vecAmbiant = m.getAmbiant();
    Vec3 &vecDiffuse = m.getDiffuse();
    Vec3 &vecSpecular = m.getSpecular();

    this->editAmbR->setText(QString::number(vecAmbiant.getX()));
    this->editAmbG->setText(QString::number(vecAmbiant.getY()));
    this->editAmbB->setText(QString::number(vecAmbiant.getZ()));
    this->editDifR->setText(QString::number(vecDiffuse.getX()));
    this->editDifG->setText(QString::number(vecDiffuse.getY()));
    this->editDifB->setText(QString::number(vecDiffuse.getZ()));
    this->editSpeR->setText(QString::number(vecSpecular.getX()));
    this->editSpeG->setText(QString::number(vecSpecular.getY()));
    this->editSpeB->setText(QString::number(vecSpecular.getZ()));
    this->editSpeExp->setText(QString::number(m.getSpecExp()));
}
void InterfaceQT::resetViewerTarget()
{
    this->editPosX->setText("");
    this->editPosY->setText("");
    this->editPosZ->setText("");
    this->editRotX->setText("");
    this->editRotY->setText("");
    this->editRotZ->setText("");
    this->editSclX->setText("");
    this->editSclY->setText("");
    this->editSclZ->setText("");
    this->editAmbR->setText("");
    this->editAmbG->setText("");
    this->editAmbB->setText("");
    this->editDifR->setText("");
    this->editDifG->setText("");
    this->editDifB->setText("");
    this->editSpeR->setText("");
    this->editSpeG->setText("");
    this->editSpeB->setText("");
    this->editSpeExp->setText("");
}

#include <QDebug>
/*#########################################*/
/*                 Signals                #*/
/*#########################################*/

void InterfaceQT::updateEditPosX(const QString &text) { qDebug() << "Modification : updateEditPosX"; }
void InterfaceQT::updateEditPosY(const QString &text) { qDebug() << "Modification : updateEditPosY"; }
void InterfaceQT::updateEditPosZ(const QString &text) { qDebug() << "Modification : updateEditPosZ"; }
void InterfaceQT::updateEditRotX(const QString &text) { qDebug() << "Modification : updateEditRotX"; }
void InterfaceQT::updateEditRotY(const QString &text) { qDebug() << "Modification : updateEditRotY"; }
void InterfaceQT::updateEditRotZ(const QString &text) { qDebug() << "Modification : updateEditRotZ"; }
void InterfaceQT::updateEditSclX(const QString &text) { qDebug() << "Modification : updateEditSclX"; }
void InterfaceQT::updateEditSclY(const QString &text) { qDebug() << "Modification : updateEditSclY"; }
void InterfaceQT::updateEditSclZ(const QString &text) { qDebug() << "Modification : updateEditSclZ"; }

// TODO : NE PAS OUBLIER DE METTRE EDITMAT A CUSTOM SI CHANGEMENT!
void InterfaceQT::updateEditAmbR() { qDebug() << "Modification : updateEditAmbR"; }
void InterfaceQT::updateEditAmbG() { qDebug() << "Modification : updateEditAmbG"; }
void InterfaceQT::updateEditAmbB() { qDebug() << "Modification : updateEditAmbB"; }
void InterfaceQT::updateEditDifR() { qDebug() << "Modification : updateEditDifR"; }
void InterfaceQT::updateEditDifG() { qDebug() << "Modification : updateEditDifG"; }
void InterfaceQT::updateEditDifB() { qDebug() << "Modification : updateEditDifB"; }
void InterfaceQT::updateEditSpeR() { qDebug() << "Modification : updateEditSpeR"; }
void InterfaceQT::updateEditSpeG() { qDebug() << "Modification : updateEditSpeG"; }
void InterfaceQT::updateEditSpeB() { qDebug() << "Modification : updateEditSpeB"; }
void InterfaceQT::updateEditSpeExp() { qDebug() << "Modification : updateEditSpeExp"; }

void InterfaceQT::updateEditMat(const QString &selected)
{
    qDebug() << selected;
    // TODO : SWITCH CASE SUR SELECTED ET UPDATE LES MATERIAL.
}