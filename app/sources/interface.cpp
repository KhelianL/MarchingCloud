#include <interface.h>

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
void InterfaceQT::updateViewerTarget()
{
    Vec3 &vecPosition = this->targetP->getRelativePosition();
    Vec3 &vecRotation = this->targetP->getRelativeRotation();
    Vec3 &vecScale = this->targetP->getRelativeScale();
    this->editPosX->setText(QString::number(vecPosition.getX()));
    this->editPosY->setText(QString::number(vecPosition.getY()));
    this->editPosZ->setText(QString::number(vecPosition.getZ()));
    this->editRotX->setText(QString::number(vecRotation.getX()));
    this->editRotY->setText(QString::number(vecRotation.getY()));
    this->editRotZ->setText(QString::number(vecRotation.getZ()));
    this->editSclX->setText(QString::number(vecScale.getX()));
    this->editSclY->setText(QString::number(vecScale.getY()));
    this->editSclZ->setText(QString::number(vecScale.getZ()));

    Material &m = this->targetP->getMaterial();
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

    QString value = QString::fromStdString(getMaterialTypeToString(m.getType()));
    int index = -1;
    bool find = false;
    for (int i = 0, maxSize = this->editMat->count(); i < maxSize && !find; ++i)
    {
        if (this->editMat->itemText(i) == value)
        {
            index = i;
            find = true;
        }
    }
    if (find)
    {
        this->editMat->setCurrentIndex(index);
    }
    else
    {
        this->editMat->setCurrentIndex(0);
    }
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

/*#########################################*/
/*                 Signals                #*/
/*#########################################*/

void InterfaceQT::updateEditPosX(const QString &text) { this->targetP->relativeMoveX(text.toDouble()); }
void InterfaceQT::updateEditPosY(const QString &text) { this->targetP->relativeMoveY(text.toDouble()); }
void InterfaceQT::updateEditPosZ(const QString &text) { this->targetP->relativeMoveZ(text.toDouble()); }
void InterfaceQT::updateEditRotX(const QString &text) { this->targetP->relativeRotateX(text.toDouble()); }
void InterfaceQT::updateEditRotY(const QString &text) { this->targetP->relativeRotateY(text.toDouble()); }
void InterfaceQT::updateEditRotZ(const QString &text) { this->targetP->relativeRotateZ(text.toDouble()); }
void InterfaceQT::updateEditSclX(const QString &text) { this->targetP->relativeScaleX(text.toDouble()); }
void InterfaceQT::updateEditSclY(const QString &text) { this->targetP->relativeScaleY(text.toDouble()); }
void InterfaceQT::updateEditSclZ(const QString &text) { this->targetP->relativeScaleZ(text.toDouble()); }

void InterfaceQT::updateEditAmbR(const QString &text)
{
    this->targetP->getMaterial().setAmbiantR(this->editAmbR->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditAmbG(const QString &text)
{
    this->targetP->getMaterial().setAmbiantG(this->editAmbG->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditAmbB(const QString &text)
{
    this->targetP->getMaterial().setAmbiantB(this->editAmbB->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditDifR(const QString &text)
{
    this->targetP->getMaterial().setDiffuseR(this->editDifR->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditDifG(const QString &text)
{
    this->targetP->getMaterial().setDiffuseG(this->editDifG->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditDifB(const QString &text)
{
    this->targetP->getMaterial().setDiffuseB(this->editDifB->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditSpeR(const QString &text)
{
    this->targetP->getMaterial().setSpecularR(this->editSpeR->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditSpeG(const QString &text)
{
    this->targetP->getMaterial().setSpecularG(this->editSpeG->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditSpeB(const QString &text)
{
    this->targetP->getMaterial().setSpecularB(this->editSpeB->text().toDouble());
    this->editMat->setCurrentIndex(0);
}
void InterfaceQT::updateEditSpeExp(const QString &text)
{
    this->targetP->getMaterial().setSpecExp(this->editSpeExp->text().toDouble());
    this->editMat->setCurrentIndex(0);
}

void InterfaceQT::updateEditMat(const QString &selected)
{
    int idx = 0;
    bool find = false;
    for (int i = 0, maxSize = sizeof(MaterialTable) / sizeof(MaterialTable[0]); i < maxSize && !find; i++)
    {
        if (selected == QString(MaterialTable[i]))
        {
            find = true;
            idx = i;
        }
    }
    this->targetP->setMaterial(Material(static_cast<MaterialType>(idx)));
    Material &m = this->targetP->getMaterial();
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