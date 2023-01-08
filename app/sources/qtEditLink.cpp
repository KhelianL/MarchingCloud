#include <qtEditLink.h>

InterfaceQT::InterfaceQT(QLineEdit *editPosX, QLineEdit *editPosY, QLineEdit *editPosZ, QLineEdit *editRotX, QLineEdit *editRotY, QLineEdit *editRotZ, QLineEdit *editSclX, QLineEdit *editSclY, QLineEdit *editSclZ, QLineEdit *editAmbR, QLineEdit *editAmbG, QLineEdit *editAmbB, QLineEdit *editDifR, QLineEdit *editDifG, QLineEdit *editDifB, QLineEdit *editSpeR, QLineEdit *editSpeG, QLineEdit *editSpeB, QLineEdit *editSpeExp, QProgressBar *progressBar)
{
    this->editPosX = editPosX;
    this->editPosY = editPosY;
    this->editPosZ = editPosZ;
    this->editRotX = editRotX;
    this->editRotY = editRotY;
    this->editRotZ = editRotZ;
    this->editSclX = editSclX;
    this->editSclY = editSclY;
    this->editSclZ = editSclZ;
    this->editAmbR = editAmbR;
    this->editAmbG = editAmbG;
    this->editAmbB = editAmbB;
    this->editDifR = editDifR;
    this->editDifG = editDifG;
    this->editDifB = editDifB;
    this->editSpeR = editSpeR;
    this->editSpeG = editSpeG;
    this->editSpeB = editSpeB;
    this->editSpeExp = editSpeExp;
    this->progressBar = progressBar;
}

InterfaceQT::~InterfaceQT()
{
    delete this->editPosX;
    delete this->editPosY;
    delete this->editPosZ;
    delete this->editRotX;
    delete this->editRotY;
    delete this->editRotZ;
    delete this->editSclX;
    delete this->editSclY;
    delete this->editSclZ;
    delete this->editAmbR;
    delete this->editAmbG;
    delete this->editAmbB;
    delete this->editDifR;
    delete this->editDifG;
    delete this->editDifB;
    delete this->editSpeR;
    delete this->editSpeG;
    delete this->editSpeB;
    delete this->editSpeExp;
    delete this->progressBar;
}

void InterfaceQT::setAlignCenter()
{
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
}

void InterfaceQT::enableEdit(bool b)
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
    this->editSpeExp->setEnabled(b);
}

void InterfaceQT::setProgress(int n)
{
    this->progressBar->setValue(n);
}

void InterfaceQT::updateViewerTarget(PointCloud *pc)
{
    if (pc != nullptr)
    {
        
    }
}