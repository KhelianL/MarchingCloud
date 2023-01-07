#include <popupWindow.h>

#include <iostream>

PopupWindow::PopupWindow(PopupType type, QWidget *parent) : QDialog(parent)
{
    // Type
    this->t = type;

    // Création du layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Création d'un validateur
    QIntValidator *validatorInt = new QIntValidator(0, 100, this);
    QDoubleValidator *validatorDouble = new QDoubleValidator(0.0, 1.0, 2, this);
    validatorDouble->setNotation(QDoubleValidator::StandardNotation);

    // Création des champs de saisie selon le type
    if (type == PopupType::IMPORT)
    {
        // Param = decimation
        layout->addWidget(new QLabel("Entrez une valeur de décimation [0.0 ; 1.0] :", this));
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setValidator(validatorDouble);
        layout->addWidget(m_lineEdit);
    }
    else // PopupType::PLANE + PopupType::CUBE + PopupType::SHPERE + PopupType::TORUS
    {
        // Param = resolution
        layout->addWidget(new QLabel("Entrez une valeur de résolution :", this));
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setValidator(validatorInt);
        layout->addWidget(m_lineEdit);
    }

    // Ajout d'un bouton d'envoi
    m_button = new QPushButton("OK", this);
    layout->addWidget(m_button);

    // Connecte le signal "clicked" du bouton d'envoi au slot handleButtonClick()
    connect(m_button, &QPushButton::clicked, this, &PopupWindow::handleButtonClick);
}

void PopupWindow::handleButtonClick()
{
    double v = this->m_lineEdit->text().toDouble();
    this->value = (this->t == PopupType::IMPORT ? (v > 1.0 ? 1.0 : v) : v);
    this->accept();
}

double PopupWindow::getValue()
{
    return this->value;
}
