#include <popupCreate.h>

PopupCreate::PopupCreate(const PointCloudType &type, QWidget *parent) : QDialog(parent)
{
    // Type
    this->t = type;

    // Création du layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Création validateurs
    QRegExp rvp("^1|^0[.][0-9]+$");
    QRegExp rvi("[0-9]{3}");
    QRegExpValidator *vPercent = new QRegExpValidator(rvp, this);
    QRegExpValidator *vInt = new QRegExpValidator(rvi, this);

    // Création des champs de saisie selon le type
    if (type == PointCloudType::IMPORT)
    {
        // Param = decimation
        layout->addWidget(new QLabel("Entrez une valeur de décimation [0.0 ; 1.0] :", this));
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setText("0.5");
        m_lineEdit->setValidator(vPercent);
        layout->addWidget(m_lineEdit);
    }
    else // PointCloudType::PLANE + PointCloudType::CUBE + PointCloudType::SHPERE + PointCloudType::TORUS
    {
        // Param = resolution
        layout->addWidget(new QLabel("Entrez une valeur de résolution :", this));
        m_lineEdit = new QLineEdit(this);
        m_lineEdit->setText("50");
        m_lineEdit->setValidator(vInt);
        layout->addWidget(m_lineEdit);
    }

    // Ajout d'un bouton d'envoi
    m_button = new QPushButton("OK", this);
    layout->addWidget(m_button);

    // Connecte le signal "clicked" du bouton d'envoi au slot handleButtonClick()
    connect(m_button, &QPushButton::clicked, this, &PopupCreate::handleButtonClick);
}

void PopupCreate::handleButtonClick()
{
    double v = this->m_lineEdit->text().toDouble();
    this->value = (this->t == PointCloudType::IMPORT ? (v > 1.0 ? 1.0 : v) : v);
    this->accept();
}

double PopupCreate::getValue()
{
    return this->value;
}
