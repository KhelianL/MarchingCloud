#include <interfaceQT.h>

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
    Vec3 &vecPosition = p.getRelativePosition();
    this->editPosX->setText(QString::number(vecPosition.getX()));
    this->editPosY->setText(QString::number(vecPosition.getY()));
    this->editPosZ->setText(QString::number(vecPosition.getZ()));

    Vec3 &vecRotation = p.getRelativeRotation();
    this->editRotX->setText(QString::number(vecRotation.getX()));
    this->editRotY->setText(QString::number(vecRotation.getY()));
    this->editRotZ->setText(QString::number(vecRotation.getZ()));

    Vec3 &vecScale = p.getRelativeScale();
    this->editSclX->setText(QString::number(vecScale.getX()));
    this->editSclY->setText(QString::number(vecScale.getY()));
    this->editSclZ->setText(QString::number(vecScale.getZ()));

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

void InterfaceQT::updateEditPosX(const QString &text)
{
    // this->targetP.move(Vec3(text.toDouble(), 0.0f, 0.0f));
}
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