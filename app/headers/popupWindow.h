#ifndef POPUP_WINDOW_H
#define POPUP_WINDOW_H

/* QT */
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDoubleValidator>

enum class PopupType
{
    IMPORT,
    PLANE,
    CUBE,
    SPHERE,
    TORUS
};

class PopupWindow : public QDialog
{
    Q_OBJECT

public:
    PopupWindow(const PopupType &type, QWidget *parent = nullptr);
    double getValue();

private slots:
    void handleButtonClick();

private:
    PopupType t;

    QLineEdit *m_lineEdit;
    QPushButton *m_button;

    double value;
};

#endif