#include <mainwindow.h>

MainWindow::MainWindow()
{
    // Configuration de la barre d'état et ajout de la barre de progression
    this->everyButton->progressBar = new QProgressBar();
    this->everyButton->progressBar->setRange(0, 100);
    this->everyButton->progressBar->setValue(0);
    this->statusBar()->addPermanentWidget(this->everyButton->progressBar);

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
    this->addLine(layoutComponent);
    QPushButton *renderButton = new QPushButton(tr("MarchingCloud!"), this);
    connect(renderButton, &QPushButton::released, this, &MainWindow::marchingCloud);
    layoutComponent->addWidget(renderButton);
    rightSide->setLayout(layoutComponent);

    this->everyButton->enableEdit(false);

    // Left/Right side
    this->viewer = new Viewer(this->scene, this->everyButton, splitter);
    splitter->addWidget(rightSide);

    this->setCentralWidget(splitter);
    this->createActions();
    this->createMenus();
    this->statusBar()->showMessage(tr("A context menu is available with <CTRL+A>"));
    this->setWindowTitle(tr("MarchingCloud"));
    this->setMinimumSize(1024, 576);
}

MainWindow::~MainWindow()
{
    delete this->scene;
    delete this->everyButton;
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
    this->everyButton->editPosX = new QLineEdit();
    this->everyButton->editPosY = new QLineEdit();
    this->everyButton->editPosZ = new QLineEdit();
    this->everyButton->editRotX = new QLineEdit();
    this->everyButton->editRotY = new QLineEdit();
    this->everyButton->editRotZ = new QLineEdit();
    this->everyButton->editSclX = new QLineEdit();
    this->everyButton->editSclY = new QLineEdit();
    this->everyButton->editSclZ = new QLineEdit();

    labelTransform->addWidget(labelPos, 0, 0);
    labelTransform->addWidget(labelRot, 1, 0);
    labelTransform->addWidget(labelScl, 2, 0);

    editTransform->addWidget(labelPosX, 0, 2, 1, 1);
    editTransform->addWidget(this->everyButton->editPosX, 0, 3, 1, 1);
    editTransform->addWidget(labelPosY, 0, 4, 1, 1);
    editTransform->addWidget(this->everyButton->editPosY, 0, 5, 1, 1);
    editTransform->addWidget(labelPosZ, 0, 6, 1, 1);
    editTransform->addWidget(this->everyButton->editPosZ, 0, 7, 1, 1);

    editTransform->addWidget(labelRotX, 1, 2, 1, 1);
    editTransform->addWidget(this->everyButton->editRotX, 1, 3, 1, 1);
    editTransform->addWidget(labelRotY, 1, 4, 1, 1);
    editTransform->addWidget(this->everyButton->editRotY, 1, 5, 1, 1);
    editTransform->addWidget(labelRotZ, 1, 6, 1, 1);
    editTransform->addWidget(this->everyButton->editRotZ, 1, 7, 1, 1);

    editTransform->addWidget(labelSclX, 2, 2, 1, 1);
    editTransform->addWidget(this->everyButton->editSclX, 2, 3, 1, 1);
    editTransform->addWidget(labelSclY, 2, 4, 1, 1);
    editTransform->addWidget(this->everyButton->editSclY, 2, 5, 1, 1);
    editTransform->addWidget(labelSclZ, 2, 6, 1, 1);
    editTransform->addWidget(this->everyButton->editSclZ, 2, 7, 1, 1);

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
    QGridLayout *editMaterial = new QGridLayout;
    QGridLayout *labelMaterial = new QGridLayout;

    QLabel *labelTitle = new QLabel(tr("Material:"), this);
    QLabel *labelAmb = new QLabel(tr("Diffuse:"), this);
    QLabel *labelDif = new QLabel(tr("Ambiant:"), this);
    QLabel *labelSpe = new QLabel(tr("Specular:"), this);
    QLabel *labelSpeExp = new QLabel(tr("Specular Exponent:"), this);
    QLabel *labelMat = new QLabel(tr("Material:"), this);
    QLabel *labelAmbR = new QLabel("R :", this);
    QLabel *labelAmbG = new QLabel("G :", this);
    QLabel *labelAmbB = new QLabel("B :", this);
    QLabel *labelDifR = new QLabel("R :", this);
    QLabel *labelDifG = new QLabel("G :", this);
    QLabel *labelDifB = new QLabel("B :", this);
    QLabel *labelSpeR = new QLabel("R :", this);
    QLabel *labelSpeG = new QLabel("G :", this);
    QLabel *labelSpeB = new QLabel("B :", this);
    this->everyButton->editAmbR = new QLineEdit();
    this->everyButton->editAmbG = new QLineEdit();
    this->everyButton->editAmbB = new QLineEdit();
    this->everyButton->editDifR = new QLineEdit();
    this->everyButton->editDifG = new QLineEdit();
    this->everyButton->editDifB = new QLineEdit();
    this->everyButton->editSpeR = new QLineEdit();
    this->everyButton->editSpeG = new QLineEdit();
    this->everyButton->editSpeB = new QLineEdit();
    this->everyButton->editSpeExp = new QLineEdit();

    labelMaterial->addWidget(labelAmb, 0, 0);
    labelMaterial->addWidget(labelDif, 1, 0);
    labelMaterial->addWidget(labelSpe, 2, 0);
    labelMaterial->addWidget(labelSpeExp, 3, 0);
    labelMaterial->addWidget(labelMat, 4, 0);

    editMaterial->addWidget(labelAmbR, 0, 2, 1, 1);
    editMaterial->addWidget(this->everyButton->editAmbR, 0, 3, 1, 1);
    editMaterial->addWidget(labelAmbG, 0, 4, 1, 1);
    editMaterial->addWidget(this->everyButton->editAmbG, 0, 5, 1, 1);
    editMaterial->addWidget(labelAmbB, 0, 6, 1, 1);
    editMaterial->addWidget(this->everyButton->editAmbB, 0, 7, 1, 1);

    editMaterial->addWidget(labelDifR, 1, 2, 1, 1);
    editMaterial->addWidget(this->everyButton->editDifR, 1, 3, 1, 1);
    editMaterial->addWidget(labelDifG, 1, 4, 1, 1);
    editMaterial->addWidget(this->everyButton->editDifG, 1, 5, 1, 1);
    editMaterial->addWidget(labelDifB, 1, 6, 1, 1);
    editMaterial->addWidget(this->everyButton->editDifB, 1, 7, 1, 1);

    editMaterial->addWidget(labelSpeR, 2, 2, 1, 1);
    editMaterial->addWidget(this->everyButton->editSpeR, 2, 3, 1, 1);
    editMaterial->addWidget(labelSpeG, 2, 4, 1, 1);
    editMaterial->addWidget(this->everyButton->editSpeG, 2, 5, 1, 1);
    editMaterial->addWidget(labelSpeB, 2, 6, 1, 1);
    editMaterial->addWidget(this->everyButton->editSpeB, 2, 7, 1, 1);

    editMaterial->addWidget(this->everyButton->editSpeExp, 3, 4, 1, 3);

    QComboBox *editMat = new QComboBox();
    editMat->addItem(matToString(MaterialType::Gold));
    editMat->addItem(matToString(MaterialType::Silver));
    editMat->addItem(matToString(MaterialType::Bronze));
    editMat->addItem(matToString(MaterialType::Copper));
    editMat->addItem(matToString(MaterialType::Wood));
    editMat->addItem(matToString(MaterialType::RedPlastic));
    editMat->addItem(matToString(MaterialType::GreenPlastic));
    editMat->addItem(matToString(MaterialType::BluePlastic));
    editMat->addItem(matToString(MaterialType::Ruby));
    editMat->addItem(matToString(MaterialType::Crystal));
    editMat->addItem(matToString(MaterialType::Water));
    editMat->addItem(matToString(MaterialType::Glass));
    editMat->addItem(matToString(MaterialType::Mirror));
    editMat->setEnabled(false);
    editMaterial->addWidget(editMat, 4, 4, 1, 3);

    labelWidget->setLayout(labelMaterial);
    editWidget->setLayout(editMaterial);

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

    editWidget->setMaximumHeight(150);
    labelWidget->setMaximumHeight(150);
    combineWidget->setMaximumHeight(150);
    resWidget->setMaximumHeight(200);

    return resWidget;
}
QWidget *MainWindow::createRenderComponent()
{
    QWidget *resWidget = new QWidget;
    QWidget *combineWidget = new QWidget;

    QVBoxLayout *resLayout = new QVBoxLayout;
    QGridLayout *renderParamLayout = new QGridLayout;

    QLabel *labelTitle = new QLabel(tr("Render:"), this);
    QLabel *labelWidth = new QLabel(tr("Width:"), this);
    QLabel *labelHeight = new QLabel(tr("Height:"), this);
    this->everyButton->editWidth = new QLineEdit("200");
    this->everyButton->editHeight = new QLineEdit("300");

    renderParamLayout->addWidget(labelWidth, 0, 0);
    renderParamLayout->addWidget(labelHeight, 1, 0);
    renderParamLayout->addWidget(this->everyButton->editWidth, 0, 1);
    renderParamLayout->addWidget(this->everyButton->editHeight, 1, 1);
    combineWidget->setLayout(renderParamLayout);

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
/*                 Signals                #*/
/*#########################################*/

void MainWindow::marchingCloud()
{
    this->viewer->rayTraceEvent(this->everyButton->editWidth->text().toInt(), this->everyButton->editHeight->text().toInt());
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

    this->scene->generateImport(fileName.toStdString(), (double)popup.getValue());
}

void MainWindow::createPlane()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE PLANE>"));

    PopupWindow popup(PopupType::PLANE);
    popup.exec();

    scene->generatePrimitive(PopupType::PLANE, (int)popup.getValue());
}
void MainWindow::createCube()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE CUBE>"));

    PopupWindow popup(PopupType::CUBE);
    popup.exec();

    scene->generatePrimitive(PopupType::CUBE, (int)popup.getValue());
}
void MainWindow::createSphere()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE SPHERE>"));

    PopupWindow popup(PopupType::SPHERE);
    popup.exec();

    scene->generatePrimitive(PopupType::SPHERE, (int)popup.getValue());
}
void MainWindow::createTorus()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE TORUS>"));

    PopupWindow popup(PopupType::TORUS);
    popup.exec();

    scene->generatePrimitive(PopupType::TORUS, (int)popup.getValue());
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