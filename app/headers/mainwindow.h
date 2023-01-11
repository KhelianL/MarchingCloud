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
#include <QRegExpValidator>

/* SRC */
#include <scene.h>
#include <viewer.h>
#include <popupWindow.h>
#include <interface.h>

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
    void initInterfaceQT();
    void initSignals();
    void updateViewer();

    /* ACTIONS & MENU */
    QShortcut *shortcut;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *pointCloudMenu;
    QMenu *helpMenu;
    QAction *delTargetAct;
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
    void handleEditPosX(const QString &text);
    void handleEditPosY(const QString &text);
    void handleEditPosZ(const QString &text);
    void handleEditRotX(const QString &text);
    void handleEditRotY(const QString &text);
    void handleEditRotZ(const QString &text);
    void handleEditSclX(const QString &text);
    void handleEditSclY(const QString &text);
    void handleEditSclZ(const QString &text);
    void handleEditAmbR(const QString &text);
    void handleEditAmbG(const QString &text);
    void handleEditAmbB(const QString &text);
    void handleEditDifR(const QString &text);
    void handleEditDifG(const QString &text);
    void handleEditDifB(const QString &text);
    void handleEditSpeR(const QString &text);
    void handleEditSpeG(const QString &text);
    void handleEditSpeB(const QString &text);
    void handleEditSpeExp(const QString &text);
    void handleEditMat();

    /* ACTIONS & MENU */
    void delTarget();
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