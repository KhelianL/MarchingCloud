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

/* SRC */
#include <scene.h>
#include <viewer.h>

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
    Scene *const scene = new Scene();
    Viewer *viewer;
    QProgressBar *progressBar = new QProgressBar();

    QWidget *createTransformComponent();
    QWidget *createMaterialComponent();
    QWidget *createRenderComponent();
    void addLine(QVBoxLayout *layoutComponent);

    void createActions();
    void createMenus();

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