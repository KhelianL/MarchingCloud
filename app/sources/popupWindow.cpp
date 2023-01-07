#include <popupWindow.h>

#include <iostream>

PopupWindow::PopupWindow(PopupType type, QWidget *parent) : QDialog(parent)
{
    // Création du layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Création d'un validateur
    QDoubleValidator *validator = new QDoubleValidator(0.0, 1.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);

    // Création des champs de saisie selon le type
    switch (type)
    {
    case PopupType::IMPORT:
        layout->addWidget(new QLabel("Entrez une valeur de décimation [0.0 ; 1.0] :", this));
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setValidator(validator);
        layout->addWidget(m_lineEdit);
        break;
    case PopupType::PLANE:
        break;
    case PopupType::CUBE:
        break;
    case PopupType::SHPERE:
        break;
    case PopupType::TORUS:
        break;
    default:
        break;
    }

    // Ajout d'un bouton d'envoi
    m_button = new QPushButton("OK", this);
    layout->addWidget(m_button);

    // Connecte le signal "clicked" du bouton d'envoi au slot handleButtonClick()
    connect(m_button, &QPushButton::clicked, this, &PopupWindow::handleButtonClick);
}

void PopupWindow::handleButtonClick()
{
    // Récupère la valeur du champ de saisie et affiche un message
    QString value = m_lineEdit->text();
    std::cout << (value.toDouble() > 1.0 ? 1.0 : value.toDouble()) << std::endl;
}
