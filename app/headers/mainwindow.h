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
#include <interfaceQT.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /* CORE */
    Scene *const scene = new Scene();
    Viewer *viewer;
    InterfaceQT *interfaceQT;

    /* INTERFACE CREATION */
    QWidget *createTransformComponent();
    QWidget *createMaterialComponent();
    QWidget *createRenderComponent();
    void addLine(QVBoxLayout *layoutComponent);
    void createActions();
    void createMenus();

    /* SIGNALS */
    void marchingCloud();
    void initSignals();

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

private slots:
    /* SIGNALS */
    void handleEditMat();

    /* ACTIONS & MENU */
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

public:
    MainWindow();
    ~MainWindow();
};

#endif