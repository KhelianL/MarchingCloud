#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* QT */
#include <QMainWindow>
#include <QWidget>
#include <QSplitter>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QCursor>
#include <QAction>
#include <QActionGroup>
#include <QShortcut>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QString>
#include <QComboBox>

/* SRC */
#include <scene.h>
#include <viewer.h>
#include <popupWindow.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void setProgress(int n);

private slots:
    void showCustomMenu();

    void newScene();
    void openScene();
    void saveScene();

    void undo();
    void redo();

    void importPointCloud();
    void createPlane();
    void createCube();
    void createSphere();
    void createTorus();

    void about();

private:
    /* CORE */
    Scene *const scene = new Scene();
    Viewer *viewer;
    QProgressBar *progressBar = new QProgressBar();

    /* EDIT_LINES */
    QLineEdit *editPosX;
    QLineEdit *editPosY;
    QLineEdit *editPosZ;
    QLineEdit *editRotX;
    QLineEdit *editRotY;
    QLineEdit *editRotZ;
    QLineEdit *editSclX;
    QLineEdit *editSclY;
    QLineEdit *editSclZ;
    QLineEdit *editAmbR;
    QLineEdit *editAmbG;
    QLineEdit *editAmbB;
    QLineEdit *editDifR;
    QLineEdit *editDifG;
    QLineEdit *editDifB;
    QLineEdit *editSpeR;
    QLineEdit *editSpeG;
    QLineEdit *editSpeB;
    QLineEdit *editSpeExp;
    QLineEdit *editWidth;
    QLineEdit *editHeight;

    void enableEdit(bool b);

    /* INTERFACE CREATION */
    QWidget *createTransformComponent();
    QWidget *createMaterialComponent();
    QWidget *createRenderComponent();
    void addLine(QVBoxLayout *layoutComponent);
    void createActions();
    void createMenus();

    /* ACTIONS & MENU */
    QShortcut *shortcut;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *pointCloudMenu;
    QMenu *helpMenu;
    QAction *newSceneAct;
    QAction *openSceneAct;
    QAction *saveSceneAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *importPointCloudAct;
    QAction *genPlaneAct;
    QAction *genCubeAct;
    QAction *genSphereAct;
    QAction *genTorusAct;
    QAction *aboutAct;
};

#endif