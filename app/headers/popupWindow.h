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
    SHPERE,
    TORUS
};

class PopupWindow : public QDialog
{
    Q_OBJECT

public:
    PopupWindow(PopupType type, QWidget *parent = nullptr);

private slots:
    void handleButtonClick();

private:
    QLineEdit *m_lineEdit;
    QPushButton *m_button;


};

#endif