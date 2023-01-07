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
    enableEdit(false);

    // Left/Right side
    this->viewer = new Viewer(this->scene, splitter);
    splitter->addWidget(rightSide);

    this->setCentralWidget(splitter);
    this->createActions();
    this->createMenus();
    this->statusBar()->showMessage(tr("A context menu is available by right-clicking"));
    this->setWindowTitle(tr("Menu"));
    this->setMinimumSize(1024, 576);
}

MainWindow::~MainWindow()
{
    delete this->scene;
    delete this->progressBar;
    delete this->editPosX;
    delete this->editPosY;
    delete this->editPosZ;
    delete this->editRotX;
    delete this->editRotY;
    delete this->editRotZ;
    delete this->editSclX;
    delete this->editSclY;
    delete this->editSclZ;
    delete this->editAmbR;
    delete this->editAmbG;
    delete this->editAmbB;
    delete this->editDifR;
    delete this->editDifG;
    delete this->editDifB;
    delete this->editSpeR;
    delete this->editSpeG;
    delete this->editSpeB;
    delete this->editSpeExp;
}

/*#########################################*/
/*                 Setters                #*/
/*#########################################*/

void MainWindow::setProgress(int n)
{
    this->progressBar->setValue(n);
}

void MainWindow::enableEdit(bool b)
{
    this->editPosX->setEnabled(b);
    this->editPosY->setEnabled(b);
    this->editPosZ->setEnabled(b);
    this->editRotX->setEnabled(b);
    this->editRotY->setEnabled(b);
    this->editRotZ->setEnabled(b);
    this->editSclX->setEnabled(b);
    this->editSclY->setEnabled(b);
    this->editSclZ->setEnabled(b);
    this->editAmbR->setEnabled(b);
    this->editAmbG->setEnabled(b);
    this->editAmbB->setEnabled(b);
    this->editDifR->setEnabled(b);
    this->editDifG->setEnabled(b);
    this->editDifB->setEnabled(b);
    this->editSpeR->setEnabled(b);
    this->editSpeG->setEnabled(b);
    this->editSpeB->setEnabled(b);
    this->editSpeExp->setEnabled(b);
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
    this->editPosX = new QLineEdit();
    this->editPosY = new QLineEdit();
    this->editPosZ = new QLineEdit();
    this->editRotX = new QLineEdit();
    this->editRotY = new QLineEdit();
    this->editRotZ = new QLineEdit();
    this->editSclX = new QLineEdit();
    this->editSclY = new QLineEdit();
    this->editSclZ = new QLineEdit();
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
    this->editAmbR = new QLineEdit();
    this->editAmbG = new QLineEdit();
    this->editAmbB = new QLineEdit();
    this->editDifR = new QLineEdit();
    this->editDifG = new QLineEdit();
    this->editDifB = new QLineEdit();
    this->editSpeR = new QLineEdit();
    this->editSpeG = new QLineEdit();
    this->editSpeB = new QLineEdit();
    this->editSpeExp = new QLineEdit();
    editAmbR->setAlignment(Qt::AlignCenter);
    editAmbG->setAlignment(Qt::AlignCenter);
    editAmbB->setAlignment(Qt::AlignCenter);
    editDifR->setAlignment(Qt::AlignCenter);
    editDifG->setAlignment(Qt::AlignCenter);
    editDifB->setAlignment(Qt::AlignCenter);
    editSpeR->setAlignment(Qt::AlignCenter);
    editSpeG->setAlignment(Qt::AlignCenter);
    editSpeB->setAlignment(Qt::AlignCenter);
    editSpeExp->setAlignment(Qt::AlignCenter);

    labelMaterial->addWidget(labelAmb, 0, 0);
    labelMaterial->addWidget(labelDif, 1, 0);
    labelMaterial->addWidget(labelSpe, 2, 0);
    labelMaterial->addWidget(labelSpeExp, 3, 0);
    labelMaterial->addWidget(labelMat, 4, 0);

    editMaterial->addWidget(labelAmbR, 0, 2, 1, 1);
    editMaterial->addWidget(editAmbR, 0, 3, 1, 1);
    editMaterial->addWidget(labelAmbG, 0, 4, 1, 1);
    editMaterial->addWidget(editAmbG, 0, 5, 1, 1);
    editMaterial->addWidget(labelAmbB, 0, 6, 1, 1);
    editMaterial->addWidget(editAmbB, 0, 7, 1, 1);

    editMaterial->addWidget(labelDifR, 1, 2, 1, 1);
    editMaterial->addWidget(editDifR, 1, 3, 1, 1);
    editMaterial->addWidget(labelDifG, 1, 4, 1, 1);
    editMaterial->addWidget(editDifG, 1, 5, 1, 1);
    editMaterial->addWidget(labelDifB, 1, 6, 1, 1);
    editMaterial->addWidget(editDifB, 1, 7, 1, 1);

    editMaterial->addWidget(labelSpeR, 2, 2, 1, 1);
    editMaterial->addWidget(editSpeR, 2, 3, 1, 1);
    editMaterial->addWidget(labelSpeG, 2, 4, 1, 1);
    editMaterial->addWidget(editSpeG, 2, 5, 1, 1);
    editMaterial->addWidget(labelSpeB, 2, 6, 1, 1);
    editMaterial->addWidget(editSpeB, 2, 7, 1, 1);

    editMaterial->addWidget(editSpeExp, 3, 4, 1, 3);

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
    this->editWidth = new QLineEdit("200");
    this->editHeight = new QLineEdit("300");
    editWidth->setAlignment(Qt::AlignCenter);
    editHeight->setAlignment(Qt::AlignCenter);
    QPushButton *renderButton = new QPushButton(tr("MarchingCloud!"), this);
    connect(renderButton, &QPushButton::released, this, &MainWindow::marchingCloud);

    renderParamLayout->addWidget(labelWidth, 0, 0);
    renderParamLayout->addWidget(labelHeight, 1, 0);
    renderParamLayout->addWidget(editWidth, 0, 1);
    renderParamLayout->addWidget(editHeight, 1, 1);
    renderParamLayout->addWidget(renderButton, 2, 0, 2, 2);

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

    // resWidget->setStyleSheet("border : 1px solid red");

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
    this->viewer->rayTraceEvent(this->editWidth->text().toInt(), this->editHeight->text().toInt());
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