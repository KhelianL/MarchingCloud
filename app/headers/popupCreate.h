#ifndef POPUP_CREATE_H
#define POPUP_CREATE_H

/* QT */
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDoubleValidator>

/* SRC */
#include <pointCloud.h>

class PopupCreate : public QDialog
{
    Q_OBJECT

public:
    PopupCreate(const PointCloudType &type, QWidget *parent = nullptr);
    double getValue();

private slots:
    void handleButtonClick();

private:
    PointCloudType t;

    QLineEdit *m_lineEdit;
    QPushButton *m_button;

    double value;
};

#endif