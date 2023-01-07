#include <mainwindow.h>

MainWindow::MainWindow()
{
    // Configuration de la barre d'état et ajout de la barre de progression
    this->progressBar->setRange(0, 100);
    this->progressBar->setValue(0);
    this->statusBar()->addPermanentWidget(this->progressBar);

    // Création des widget main
    QSplitter *splitter = new QSplitter;
    QWidget *rightSide = new QWidget;

    // Ajout des composants
    QVBoxLayout *layoutComponent = new QVBoxLayout;
    layoutComponent->addWidget(createTransformComponent());
    this->addLine(layoutComponent);
    layoutComponent->addWidget(createMaterialComponent());
    this->addLine(layoutComponent);
    layoutComponent->addWidget(createRenderComponent());
    rightSide->setLayout(layoutComponent);

    // Left/Right side
    this->viewer = new Viewer(this->scene, this->camera, splitter);
    splitter->addWidget(rightSide);

    this->setCentralWidget(splitter);
    this->createActions();
    this->createMenus();
    this->statusBar()->showMessage(tr("A context menu is available by right-clicking"));
    this->setWindowTitle(tr("Menus"));
    this->setMinimumSize(1024, 576);
}

MainWindow::~MainWindow()
{
    delete this->scene;
    delete this->camera;
    delete this->progressBar;
}

/*#########################################*/
/*                 Setters                #*/
/*#########################################*/

void MainWindow::setProgress(int n)
{
    this->progressBar->setValue(n);
}

/*#########################################*/
/*            CreateComponents            #*/
/*#########################################*/

QWidget *MainWindow::createTransformComponent()
{
    QWidget *resWidget = new QWidget;
    QWidget *combineWidget = new QWidget;
    QWidget *labelWidget = new QWidget;
    QWidget *editWidget = new QWidget;

    QVBoxLayout *resLayout = new QVBoxLayout;
    QHBoxLayout *combineLayout = new QHBoxLayout;
    QGridLayout *editTransform = new QGridLayout;
    QGridLayout *labelTransform = new QGridLayout;

    QLabel *labelTitle = new QLabel(tr("Transform:"), this);
    QLabel *labelPos = new QLabel(tr("Position:"), this);
    QLabel *labelRot = new QLabel(tr("Rotation:"), this);
    QLabel *labelScl = new QLabel(tr("Scale:"), this);
    QLabel *labelPosX = new QLabel("X :", this);
    QLabel *labelPosY = new QLabel("Y :", this);
    QLabel *labelPosZ = new QLabel("Z :", this);
    QLabel *labelRotX = new QLabel("X :", this);
    QLabel *labelRotY = new QLabel("Y :", this);
    QLabel *labelRotZ = new QLabel("Z :", this);
    QLabel *labelSclX = new QLabel("X :", this);
    QLabel *labelSclY = new QLabel("Y :", this);
    QLabel *labelSclZ = new QLabel("Z :", this);
    QLineEdit *editPosX = new QLineEdit("0.0");
    QLineEdit *editPosY = new QLineEdit("0.0");
    QLineEdit *editPosZ = new QLineEdit("0.0");
    QLineEdit *editRotX = new QLineEdit("0.0");
    QLineEdit *editRotY = new QLineEdit("0.0");
    QLineEdit *editRotZ = new QLineEdit("0.0");
    QLineEdit *editSclX = new QLineEdit("0.0");
    QLineEdit *editSclY = new QLineEdit("0.0");
    QLineEdit *editSclZ = new QLineEdit("0.0");
    editPosX->setAlignment(Qt::AlignCenter);
    editPosY->setAlignment(Qt::AlignCenter);
    editPosZ->setAlignment(Qt::AlignCenter);
    editRotX->setAlignment(Qt::AlignCenter);
    editRotY->setAlignment(Qt::AlignCenter);
    editRotZ->setAlignment(Qt::AlignCenter);
    editSclX->setAlignment(Qt::AlignCenter);
    editSclY->setAlignment(Qt::AlignCenter);
    editSclZ->setAlignment(Qt::AlignCenter);

    labelTransform->addWidget(labelPos, 0, 0);
    labelTransform->addWidget(labelRot, 1, 0);
    labelTransform->addWidget(labelScl, 2, 0);

    editTransform->addWidget(labelPosX, 0, 2, 1, 1);
    editTransform->addWidget(editPosX, 0, 3, 1, 1);
    editTransform->addWidget(labelPosY, 0, 4, 1, 1);
    editTransform->addWidget(editPosY, 0, 5, 1, 1);
    editTransform->addWidget(labelPosZ, 0, 6, 1, 1);
    editTransform->addWidget(editPosZ, 0, 7, 1, 1);

    editTransform->addWidget(labelRotX, 1, 2, 1, 1);
    editTransform->addWidget(editRotX, 1, 3, 1, 1);
    editTransform->addWidget(labelRotY, 1, 4, 1, 1);
    editTransform->addWidget(editRotY, 1, 5, 1, 1);
    editTransform->addWidget(labelRotZ, 1, 6, 1, 1);
    editTransform->addWidget(editRotZ, 1, 7, 1, 1);

    editTransform->addWidget(labelSclX, 2, 2, 1, 1);
    editTransform->addWidget(editSclX, 2, 3, 1, 1);
    editTransform->addWidget(labelSclY, 2, 4, 1, 1);
    editTransform->addWidget(editSclY, 2, 5, 1, 1);
    editTransform->addWidget(labelSclZ, 2, 6, 1, 1);
    editTransform->addWidget(editSclZ, 2, 7, 1, 1);

    labelWidget->setLayout(labelTransform);
    editWidget->setLayout(editTransform);

    combineLayout->addWidget(labelWidget);
    combineLayout->addWidget(editWidget);

    combineWidget->setLayout(combineLayout);

    QFont boldFont = labelTitle->font();
    boldFont.setBold(true);
    labelTitle->setFont(boldFont);
    labelTitle->setFixedHeight(25);

    resLayout->addWidget(labelTitle);
    resLayout->addWidget(combineWidget);

    resWidget->setLayout(resLayout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(8);
    shadow->setColor(Qt::gray);
    shadow->setOffset(2, 2);
    resWidget->setGraphicsEffect(shadow);

    editWidget->setMaximumHeight(100);
    labelWidget->setMaximumHeight(100);
    combineWidget->setMaximumHeight(100);
    resWidget->setMaximumHeight(150);

    return resWidget;
}
QWidget *MainWindow::createMaterialComponent()
{
    QWidget *resWidget = new QWidget;
    QWidget *combineWidget = new QWidget;
    QWidget *labelWidget = new QWidget;
    QWidget *editWidget = new QWidget;

    QVBoxLayout *resLayout = new QVBoxLayout;
    QHBoxLayout *combineLayout = new QHBoxLayout;
    QGridLayout *editTransform = new QGridLayout;
    QGridLayout *labelTransform = new QGridLayout;

    QLabel *labelTitle = new QLabel(tr("Material:"), this);
    QLabel *labelPos = new QLabel(tr("Position:"), this);
    QLabel *labelRot = new QLabel(tr("Rotation:"), this);
    QLabel *labelScl = new QLabel(tr("Scale:"), this);
    QLabel *labelPosX = new QLabel("X :", this);
    QLabel *labelPosY = new QLabel("Y :", this);
    QLabel *labelPosZ = new QLabel("Z :", this);
    QLabel *labelRotX = new QLabel("X :", this);
    QLabel *labelRotY = new QLabel("Y :", this);
    QLabel *labelRotZ = new QLabel("Z :", this);
    QLabel *labelSclX = new QLabel("X :", this);
    QLabel *labelSclY = new QLabel("Y :", this);
    QLabel *labelSclZ = new QLabel("Z :", this);
    QLineEdit *editPosX = new QLineEdit("0.0");
    QLineEdit *editPosY = new QLineEdit("0.0");
    QLineEdit *editPosZ = new QLineEdit("0.0");
    QLineEdit *editRotX = new QLineEdit("0.0");
    QLineEdit *editRotY = new QLineEdit("0.0");
    QLineEdit *editRotZ = new QLineEdit("0.0");
    QLineEdit *editSclX = new QLineEdit("0.0");
    QLineEdit *editSclY = new QLineEdit("0.0");
    QLineEdit *editSclZ = new QLineEdit("0.0");
    editPosX->setAlignment(Qt::AlignCenter);
    editPosY->setAlignment(Qt::AlignCenter);
    editPosZ->setAlignment(Qt::AlignCenter);
    editRotX->setAlignment(Qt::AlignCenter);
    editRotY->setAlignment(Qt::AlignCenter);
    editRotZ->setAlignment(Qt::AlignCenter);
    editSclX->setAlignment(Qt::AlignCenter);
    editSclY->setAlignment(Qt::AlignCenter);
    editSclZ->setAlignment(Qt::AlignCenter);

    labelTransform->addWidget(labelPos, 0, 0);
    labelTransform->addWidget(labelRot, 1, 0);
    labelTransform->addWidget(labelScl, 2, 0);

    editTransform->addWidget(labelPosX, 0, 2, 1, 1);
    editTransform->addWidget(editPosX, 0, 3, 1, 1);
    editTransform->addWidget(labelPosY, 0, 4, 1, 1);
    editTransform->addWidget(editPosY, 0, 5, 1, 1);
    editTransform->addWidget(labelPosZ, 0, 6, 1, 1);
    editTransform->addWidget(editPosZ, 0, 7, 1, 1);

    editTransform->addWidget(labelRotX, 1, 2, 1, 1);
    editTransform->addWidget(editRotX, 1, 3, 1, 1);
    editTransform->addWidget(labelRotY, 1, 4, 1, 1);
    editTransform->addWidget(editRotY, 1, 5, 1, 1);
    editTransform->addWidget(labelRotZ, 1, 6, 1, 1);
    editTransform->addWidget(editRotZ, 1, 7, 1, 1);

    editTransform->addWidget(labelSclX, 2, 2, 1, 1);
    editTransform->addWidget(editSclX, 2, 3, 1, 1);
    editTransform->addWidget(labelSclY, 2, 4, 1, 1);
    editTransform->addWidget(editSclY, 2, 5, 1, 1);
    editTransform->addWidget(labelSclZ, 2, 6, 1, 1);
    editTransform->addWidget(editSclZ, 2, 7, 1, 1);

    labelWidget->setLayout(labelTransform);
    editWidget->setLayout(editTransform);

    combineLayout->addWidget(labelWidget);
    combineLayout->addWidget(editWidget);

    combineWidget->setLayout(combineLayout);

    QFont boldFont = labelTitle->font();
    boldFont.setBold(true);
    labelTitle->setFont(boldFont);
    labelTitle->setFixedHeight(25);

    resLayout->addWidget(labelTitle);
    resLayout->addWidget(combineWidget);

    resWidget->setLayout(resLayout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(8);
    shadow->setColor(Qt::gray);
    shadow->setOffset(2, 2);
    resWidget->setGraphicsEffect(shadow);

    editWidget->setMaximumHeight(100);
    labelWidget->setMaximumHeight(100);
    combineWidget->setMaximumHeight(100);
    resWidget->setMaximumHeight(150);

    return resWidget;
}
QWidget *MainWindow::createRenderComponent()
{
    QWidget *resWidget = new QWidget;
    QWidget *combineWidget = new QWidget;
    QWidget *labelWidget = new QWidget;
    QWidget *editWidget = new QWidget;

    QVBoxLayout *resLayout = new QVBoxLayout;
    QHBoxLayout *combineLayout = new QHBoxLayout;
    QGridLayout *editTransform = new QGridLayout;
    QGridLayout *labelTransform = new QGridLayout;

    QLabel *labelTitle = new QLabel(tr("Render:"), this);
    QLabel *labelPos = new QLabel(tr("Position:"), this);
    QLabel *labelRot = new QLabel(tr("Rotation:"), this);
    QLabel *labelScl = new QLabel(tr("Scale:"), this);
    QLabel *labelPosX = new QLabel("X :", this);
    QLabel *labelPosY = new QLabel("Y :", this);
    QLabel *labelPosZ = new QLabel("Z :", this);
    QLabel *labelRotX = new QLabel("X :", this);
    QLabel *labelRotY = new QLabel("Y :", this);
    QLabel *labelRotZ = new QLabel("Z :", this);
    QLabel *labelSclX = new QLabel("X :", this);
    QLabel *labelSclY = new QLabel("Y :", this);
    QLabel *labelSclZ = new QLabel("Z :", this);
    QLineEdit *editPosX = new QLineEdit("0.0");
    QLineEdit *editPosY = new QLineEdit("0.0");
    QLineEdit *editPosZ = new QLineEdit("0.0");
    QLineEdit *editRotX = new QLineEdit("0.0");
    QLineEdit *editRotY = new QLineEdit("0.0");
    QLineEdit *editRotZ = new QLineEdit("0.0");
    QLineEdit *editSclX = new QLineEdit("0.0");
    QLineEdit *editSclY = new QLineEdit("0.0");
    QLineEdit *editSclZ = new QLineEdit("0.0");
    editPosX->setAlignment(Qt::AlignCenter);
    editPosY->setAlignment(Qt::AlignCenter);
    editPosZ->setAlignment(Qt::AlignCenter);
    editRotX->setAlignment(Qt::AlignCenter);
    editRotY->setAlignment(Qt::AlignCenter);
    editRotZ->setAlignment(Qt::AlignCenter);
    editSclX->setAlignment(Qt::AlignCenter);
    editSclY->setAlignment(Qt::AlignCenter);
    editSclZ->setAlignment(Qt::AlignCenter);

    labelTransform->addWidget(labelPos, 0, 0);
    labelTransform->addWidget(labelRot, 1, 0);
    labelTransform->addWidget(labelScl, 2, 0);

    editTransform->addWidget(labelPosX, 0, 2, 1, 1);
    editTransform->addWidget(editPosX, 0, 3, 1, 1);
    editTransform->addWidget(labelPosY, 0, 4, 1, 1);
    editTransform->addWidget(editPosY, 0, 5, 1, 1);
    editTransform->addWidget(labelPosZ, 0, 6, 1, 1);
    editTransform->addWidget(editPosZ, 0, 7, 1, 1);

    editTransform->addWidget(labelRotX, 1, 2, 1, 1);
    editTransform->addWidget(editRotX, 1, 3, 1, 1);
    editTransform->addWidget(labelRotY, 1, 4, 1, 1);
    editTransform->addWidget(editRotY, 1, 5, 1, 1);
    editTransform->addWidget(labelRotZ, 1, 6, 1, 1);
    editTransform->addWidget(editRotZ, 1, 7, 1, 1);

    editTransform->addWidget(labelSclX, 2, 2, 1, 1);
    editTransform->addWidget(editSclX, 2, 3, 1, 1);
    editTransform->addWidget(labelSclY, 2, 4, 1, 1);
    editTransform->addWidget(editSclY, 2, 5, 1, 1);
    editTransform->addWidget(labelSclZ, 2, 6, 1, 1);
    editTransform->addWidget(editSclZ, 2, 7, 1, 1);

    labelWidget->setLayout(labelTransform);
    editWidget->setLayout(editTransform);

    combineLayout->addWidget(labelWidget);
    combineLayout->addWidget(editWidget);

    combineWidget->setLayout(combineLayout);

    QFont boldFont = labelTitle->font();
    boldFont.setBold(true);
    labelTitle->setFont(boldFont);
    labelTitle->setFixedHeight(25);

    resLayout->addWidget(labelTitle);
    resLayout->addWidget(combineWidget);

    resWidget->setLayout(resLayout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(8);
    shadow->setColor(Qt::gray);
    shadow->setOffset(2, 2);
    resWidget->setGraphicsEffect(shadow);

    editWidget->setMaximumHeight(100);
    labelWidget->setMaximumHeight(100);
    combineWidget->setMaximumHeight(100);
    resWidget->setMaximumHeight(150);

    return resWidget;
}
void MainWindow::addLine(QVBoxLayout *layoutComponent)
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutComponent->addWidget(line);
}

/*#########################################*/
/*                 Actions                #*/
/*#########################################*/

void MainWindow::showCustomMenu()
{
    QMenu menu(this);
    menu.addAction(genPlaneAct);
    menu.addAction(genCubeAct);
    menu.addAction(genSphereAct);
    menu.addAction(genTorusAct);
    menu.exec(QCursor::pos());
    this->statusBar()->showMessage(tr("Invoked <SHORTCUT CTRL+A>"));
}

void MainWindow::newScene()
{
    this->statusBar()->showMessage(tr("Invoked <NEW SCENE>"));
}
void MainWindow::openScene()
{
    this->statusBar()->showMessage(tr("Invoked <OPEN SCENE>"));
}
void MainWindow::saveScene()
{
    this->statusBar()->showMessage(tr("Invoked <SAVE SCENE>"));
}

void MainWindow::undo()
{
    this->statusBar()->showMessage(tr("Invoked <UNDO>"));
}
void MainWindow::redo()
{
    this->statusBar()->showMessage(tr("Invoked <REDO>"));
}

void MainWindow::importPointCloud()
{
    this->statusBar()->showMessage(tr("Invoked <IMPORT POINT CLOUD>"));
    QString fileName = QFileDialog::getOpenFileName();

    PopupWindow popup(PopupType::IMPORT);
    popup.exec();

    this->scene->generateImport(fileName.toStdString());
}

void MainWindow::createPlane()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE PLANE>"));
}
void MainWindow::createCube()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE CUBE>"));
}
void MainWindow::createSphere()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE SPHERE>"));
}
void MainWindow::createTorus()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE TORUS>"));
}

void MainWindow::about()
{
    this->statusBar()->showMessage(tr("Invoked <b>Help|About</b>"));
    this->viewer->help();
}

/*#########################################*/
/*                Assemble                #*/
/*#########################################*/

void MainWindow::createActions()
{
    /* Ctrl + a pour menu contextuel */
    shortcut = new QShortcut(QKeySequence::SelectAll, this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(showCustomMenu()));

    /* File Scene Options */
    newSceneAct = new QAction(tr("&New Scene"), this);
    newSceneAct->setShortcuts(QKeySequence::New);
    newSceneAct->setStatusTip(tr("Create a new scene"));
    this->connect(newSceneAct, &QAction::triggered, this, &MainWindow::newScene);
    openSceneAct = new QAction(tr("&Open Scene"), this);
    openSceneAct->setShortcuts(QKeySequence::Open);
    openSceneAct->setStatusTip(tr("Open an existing scene"));
    this->connect(openSceneAct, &QAction::triggered, this, &MainWindow::openScene);
    saveSceneAct = new QAction(tr("&Save Scene"), this);
    saveSceneAct->setShortcuts(QKeySequence::Save);
    saveSceneAct->setStatusTip(tr("Save the scene to disk"));
    this->connect(saveSceneAct, &QAction::triggered, this, &MainWindow::saveScene);

    /* Exit */
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    this->connect(exitAct, &QAction::triggered, this, &QWidget::close);

    /* Edition */
    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    this->connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    this->connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    /* PointCloud */
    importPointCloudAct = new QAction(tr("&Import PointCloud"), this);
    importPointCloudAct->setShortcuts(QKeySequence::DeleteEndOfLine);
    importPointCloudAct->setStatusTip(tr("Import a point cloud from disk"));
    this->connect(importPointCloudAct, &QAction::triggered, this, &MainWindow::importPointCloud);
    // ---
    genPlaneAct = new QAction(tr("&Create Plane"), this);
    genPlaneAct->setStatusTip(tr("Create a plane"));
    this->connect(genPlaneAct, &QAction::triggered, this, &MainWindow::createPlane);
    genCubeAct = new QAction(tr("&Create Cube"), this);
    genCubeAct->setStatusTip(tr("Create a cube"));
    this->connect(genCubeAct, &QAction::triggered, this, &MainWindow::createCube);
    genSphereAct = new QAction(tr("&Create Sphere"), this);
    genSphereAct->setStatusTip(tr("Create a sphere"));
    this->connect(genSphereAct, &QAction::triggered, this, &MainWindow::createSphere);
    genTorusAct = new QAction(tr("&Create Torus"), this);
    genTorusAct->setStatusTip(tr("Create a torus"));
    this->connect(genTorusAct, &QAction::triggered, this, &MainWindow::createTorus);

    /* About */
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    this->connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newSceneAct);
    fileMenu->addAction(openSceneAct);
    fileMenu->addAction(saveSceneAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    pointCloudMenu = menuBar()->addMenu(tr("&PointCloud"));
    pointCloudMenu->addAction(importPointCloudAct);
    pointCloudMenu->addSeparator();
    pointCloudMenu->addAction(genPlaneAct);
    pointCloudMenu->addAction(genCubeAct);
    pointCloudMenu->addAction(genSphereAct);
    pointCloudMenu->addAction(genTorusAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}