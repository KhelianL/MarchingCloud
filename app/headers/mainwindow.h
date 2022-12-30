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

/* SRC */
#include <scene.h>
#include <viewer.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private slots:
    void showCustomMenu();
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();

private:
    Scene *const scene = new Scene();
    Viewer *viewer;

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;
    QActionGroup *alignmentGroup;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *boldAct;
    QAction *italicAct;
    QAction *leftAlignAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *centerAct;
    QAction *setLineSpacingAct;
    QAction *setParagraphSpacingAct;
    QAction *aboutAct;
    QLabel *infoLabel;
    QShortcut *shortcut;
};

#endif