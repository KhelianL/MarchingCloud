#include <mainwindow.h>

/*#########################################*/
/*           Construct/Destruct           #*/
/*#########################################*/

MainWindow::MainWindow()
{
    // Configuration de la barre d'état et ajout de la barre de progression
    this->interfaceQT->progressBar = new QProgressBar();
    this->interfaceQT->progressBar->setRange(0, 100);
    this->interfaceQT->progressBar->setValue(0);
    this->statusBar()->addPermanentWidget(this->interfaceQT->progressBar);

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

    this->initSignals();
    this->initInterfaceQT();

    // Left/Right side
    this->viewer = new Viewer(this->interfaceQT, splitter);
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
    delete this->interfaceQT->editPosX;
    delete this->interfaceQT->editPosY;
    delete this->interfaceQT->editPosZ;
    delete this->interfaceQT->editRotX;
    delete this->interfaceQT->editRotY;
    delete this->interfaceQT->editRotZ;
    delete this->interfaceQT->editSclX;
    delete this->interfaceQT->editSclY;
    delete this->interfaceQT->editSclZ;
    delete this->interfaceQT->editAmbR;
    delete this->interfaceQT->editAmbG;
    delete this->interfaceQT->editAmbB;
    delete this->interfaceQT->editDifR;
    delete this->interfaceQT->editDifG;
    delete this->interfaceQT->editDifB;
    delete this->interfaceQT->editSpeR;
    delete this->interfaceQT->editSpeG;
    delete this->interfaceQT->editSpeB;
    delete this->interfaceQT->editSpeExp;
    delete this->interfaceQT->editWidth;
    delete this->interfaceQT->editHeight;
    delete this->interfaceQT->editMat;
    delete this->interfaceQT->progressBar;
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
    this->interfaceQT->editPosX = new QLineEdit();
    this->interfaceQT->editPosY = new QLineEdit();
    this->interfaceQT->editPosZ = new QLineEdit();
    this->interfaceQT->editRotX = new QLineEdit();
    this->interfaceQT->editRotY = new QLineEdit();
    this->interfaceQT->editRotZ = new QLineEdit();
    this->interfaceQT->editSclX = new QLineEdit();
    this->interfaceQT->editSclY = new QLineEdit();
    this->interfaceQT->editSclZ = new QLineEdit();

    labelTransform->addWidget(labelPos, 0, 0);
    labelTransform->addWidget(labelRot, 1, 0);
    labelTransform->addWidget(labelScl, 2, 0);

    editTransform->addWidget(labelPosX, 0, 2, 1, 1);
    editTransform->addWidget(this->interfaceQT->editPosX, 0, 3, 1, 1);
    editTransform->addWidget(labelPosY, 0, 4, 1, 1);
    editTransform->addWidget(this->interfaceQT->editPosY, 0, 5, 1, 1);
    editTransform->addWidget(labelPosZ, 0, 6, 1, 1);
    editTransform->addWidget(this->interfaceQT->editPosZ, 0, 7, 1, 1);

    editTransform->addWidget(labelRotX, 1, 2, 1, 1);
    editTransform->addWidget(this->interfaceQT->editRotX, 1, 3, 1, 1);
    editTransform->addWidget(labelRotY, 1, 4, 1, 1);
    editTransform->addWidget(this->interfaceQT->editRotY, 1, 5, 1, 1);
    editTransform->addWidget(labelRotZ, 1, 6, 1, 1);
    editTransform->addWidget(this->interfaceQT->editRotZ, 1, 7, 1, 1);

    editTransform->addWidget(labelSclX, 2, 2, 1, 1);
    editTransform->addWidget(this->interfaceQT->editSclX, 2, 3, 1, 1);
    editTransform->addWidget(labelSclY, 2, 4, 1, 1);
    editTransform->addWidget(this->interfaceQT->editSclY, 2, 5, 1, 1);
    editTransform->addWidget(labelSclZ, 2, 6, 1, 1);
    editTransform->addWidget(this->interfaceQT->editSclZ, 2, 7, 1, 1);

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
    this->interfaceQT->editAmbR = new QLineEdit();
    this->interfaceQT->editAmbG = new QLineEdit();
    this->interfaceQT->editAmbB = new QLineEdit();
    this->interfaceQT->editDifR = new QLineEdit();
    this->interfaceQT->editDifG = new QLineEdit();
    this->interfaceQT->editDifB = new QLineEdit();
    this->interfaceQT->editSpeR = new QLineEdit();
    this->interfaceQT->editSpeG = new QLineEdit();
    this->interfaceQT->editSpeB = new QLineEdit();
    this->interfaceQT->editSpeExp = new QLineEdit();

    labelMaterial->addWidget(labelAmb, 0, 0);
    labelMaterial->addWidget(labelDif, 1, 0);
    labelMaterial->addWidget(labelSpe, 2, 0);
    labelMaterial->addWidget(labelSpeExp, 3, 0);
    labelMaterial->addWidget(labelMat, 4, 0);

    editMaterial->addWidget(labelAmbR, 0, 2, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editAmbR, 0, 3, 1, 1);
    editMaterial->addWidget(labelAmbG, 0, 4, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editAmbG, 0, 5, 1, 1);
    editMaterial->addWidget(labelAmbB, 0, 6, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editAmbB, 0, 7, 1, 1);

    editMaterial->addWidget(labelDifR, 1, 2, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editDifR, 1, 3, 1, 1);
    editMaterial->addWidget(labelDifG, 1, 4, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editDifG, 1, 5, 1, 1);
    editMaterial->addWidget(labelDifB, 1, 6, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editDifB, 1, 7, 1, 1);

    editMaterial->addWidget(labelSpeR, 2, 2, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editSpeR, 2, 3, 1, 1);
    editMaterial->addWidget(labelSpeG, 2, 4, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editSpeG, 2, 5, 1, 1);
    editMaterial->addWidget(labelSpeB, 2, 6, 1, 1);
    editMaterial->addWidget(this->interfaceQT->editSpeB, 2, 7, 1, 1);

    editMaterial->addWidget(this->interfaceQT->editSpeExp, 3, 4, 1, 3);

    this->interfaceQT->editMat = new QComboBox();
    for (int i = 0, maxSize = sizeof(MaterialTable) / sizeof(MaterialTable[0]); i < maxSize; i++)
    {
        this->interfaceQT->editMat->addItem(MaterialTable[i]);
    }
    editMaterial->addWidget(this->interfaceQT->editMat, 4, 4, 1, 3);

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
    this->interfaceQT->editWidth = new QLineEdit("200");
    this->interfaceQT->editHeight = new QLineEdit("300");

    renderParamLayout->addWidget(labelWidth, 0, 0);
    renderParamLayout->addWidget(labelHeight, 1, 0);
    renderParamLayout->addWidget(this->interfaceQT->editWidth, 0, 1);
    renderParamLayout->addWidget(this->interfaceQT->editHeight, 1, 1);
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
    this->viewer->rayTraceEvent(this->interfaceQT->editWidth->text().toInt(), this->interfaceQT->editHeight->text().toInt());
}
void MainWindow::initInterfaceQT()
{
    // Align
    this->interfaceQT->editPosX->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editPosY->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editPosZ->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editRotX->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editRotY->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editRotZ->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSclX->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSclY->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSclZ->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editAmbR->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editAmbG->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editAmbB->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editDifR->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editDifG->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editDifB->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSpeR->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSpeG->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSpeB->setAlignment(Qt::AlignCenter);
    this->interfaceQT->editSpeExp->setAlignment(Qt::AlignCenter);

    // Validation
    QRegExp rvd("[-]?[0-9]+.[0-9]+");
    QRegExp rvi("[0-9]+");
    QRegExpValidator *vDouble = new QRegExpValidator(rvd, this);
    QRegExpValidator *vInt = new QRegExpValidator(rvi, this);

    this->interfaceQT->editPosX->setValidator(vDouble);
    this->interfaceQT->editPosY->setValidator(vDouble);
    this->interfaceQT->editPosZ->setValidator(vDouble);
    this->interfaceQT->editRotX->setValidator(vDouble);
    this->interfaceQT->editRotY->setValidator(vDouble);
    this->interfaceQT->editRotZ->setValidator(vDouble);
    this->interfaceQT->editSclX->setValidator(vDouble);
    this->interfaceQT->editSclY->setValidator(vDouble);
    this->interfaceQT->editSclZ->setValidator(vDouble);
    this->interfaceQT->editAmbR->setValidator(vDouble);
    this->interfaceQT->editAmbG->setValidator(vDouble);
    this->interfaceQT->editAmbB->setValidator(vDouble);
    this->interfaceQT->editDifR->setValidator(vDouble);
    this->interfaceQT->editDifG->setValidator(vDouble);
    this->interfaceQT->editDifB->setValidator(vDouble);
    this->interfaceQT->editSpeR->setValidator(vDouble);
    this->interfaceQT->editSpeG->setValidator(vDouble);
    this->interfaceQT->editSpeB->setValidator(vDouble);
    this->interfaceQT->editSpeExp->setValidator(vInt);
}
void MainWindow::initSignals()
{
    /* TRANSFORM COMPONENT */
    connect(this->interfaceQT->editPosX, SIGNAL(textEdited(QString)), this, SLOT(handleEditPosX(QString)));
    connect(this->interfaceQT->editPosY, SIGNAL(textEdited(QString)), this, SLOT(handleEditPosY(QString)));
    connect(this->interfaceQT->editPosZ, SIGNAL(textEdited(QString)), this, SLOT(handleEditPosZ(QString)));
    connect(this->interfaceQT->editRotX, SIGNAL(textEdited(QString)), this, SLOT(handleEditRotX(QString)));
    connect(this->interfaceQT->editRotY, SIGNAL(textEdited(QString)), this, SLOT(handleEditRotY(QString)));
    connect(this->interfaceQT->editRotZ, SIGNAL(textEdited(QString)), this, SLOT(handleEditRotZ(QString)));
    connect(this->interfaceQT->editSclX, SIGNAL(textEdited(QString)), this, SLOT(handleEditSclX(QString)));
    connect(this->interfaceQT->editSclY, SIGNAL(textEdited(QString)), this, SLOT(handleEditSclY(QString)));
    connect(this->interfaceQT->editSclZ, SIGNAL(textEdited(QString)), this, SLOT(handleEditSclZ(QString)));

    /* MATERIAL COMPONENT */
    connect(this->interfaceQT->editAmbR, SIGNAL(textEdited(QString)), this, SLOT(handleEditAmbR(QString)));
    connect(this->interfaceQT->editAmbG, SIGNAL(textEdited(QString)), this, SLOT(handleEditAmbG(QString)));
    connect(this->interfaceQT->editAmbB, SIGNAL(textEdited(QString)), this, SLOT(handleEditAmbB(QString)));
    connect(this->interfaceQT->editDifR, SIGNAL(textEdited(QString)), this, SLOT(handleEditDifR(QString)));
    connect(this->interfaceQT->editDifG, SIGNAL(textEdited(QString)), this, SLOT(handleEditDifG(QString)));
    connect(this->interfaceQT->editDifB, SIGNAL(textEdited(QString)), this, SLOT(handleEditDifB(QString)));
    connect(this->interfaceQT->editSpeR, SIGNAL(textEdited(QString)), this, SLOT(handleEditSpeR(QString)));
    connect(this->interfaceQT->editSpeG, SIGNAL(textEdited(QString)), this, SLOT(handleEditSpeG(QString)));
    connect(this->interfaceQT->editSpeB, SIGNAL(textEdited(QString)), this, SLOT(handleEditSpeB(QString)));
    connect(this->interfaceQT->editSpeExp, SIGNAL(textEdited(QString)), this, SLOT(handleEditSpeExp(QString)));

    connect(this->interfaceQT->editMat, SIGNAL(currentIndexChanged(int)), this, SLOT(handleEditMat()));
}
void MainWindow::updateViewer()
{
    this->viewer->update();
}

/* TRANSFORM COMPONENT */
void MainWindow::handleEditPosX(const QString &text)
{
    this->interfaceQT->updateEditPosX(text);
    this->updateViewer();
}
void MainWindow::handleEditPosY(const QString &text)
{
    this->interfaceQT->updateEditPosY(text);
    this->updateViewer();
}
void MainWindow::handleEditPosZ(const QString &text)
{
    this->interfaceQT->updateEditPosZ(text);
    this->updateViewer();
}
void MainWindow::handleEditRotX(const QString &text)
{
    this->interfaceQT->updateEditRotX(text);
    this->updateViewer();
}
void MainWindow::handleEditRotY(const QString &text)
{
    this->interfaceQT->updateEditRotY(text);
    this->updateViewer();
}
void MainWindow::handleEditRotZ(const QString &text)
{
    this->interfaceQT->updateEditRotZ(text);
    this->updateViewer();
}
void MainWindow::handleEditSclX(const QString &text)
{
    this->interfaceQT->updateEditSclX(text);
    this->updateViewer();
}
void MainWindow::handleEditSclY(const QString &text)
{
    this->interfaceQT->updateEditSclY(text);
    this->updateViewer();
}
void MainWindow::handleEditSclZ(const QString &text)
{
    this->interfaceQT->updateEditSclZ(text);
    this->updateViewer();
}

/* MATERIAL COMPONENT */
void MainWindow::handleEditAmbR(const QString &text)
{
    this->interfaceQT->updateEditAmbR(text);
}
void MainWindow::handleEditAmbG(const QString &text)
{
    this->interfaceQT->updateEditAmbG(text);
}
void MainWindow::handleEditAmbB(const QString &text)
{
    this->interfaceQT->updateEditAmbB(text);
}
void MainWindow::handleEditDifR(const QString &text)
{
    this->interfaceQT->updateEditDifR(text);
}
void MainWindow::handleEditDifG(const QString &text)
{
    this->interfaceQT->updateEditDifG(text);
}
void MainWindow::handleEditDifB(const QString &text)
{
    this->interfaceQT->updateEditDifB(text);
}
void MainWindow::handleEditSpeR(const QString &text)
{
    this->interfaceQT->updateEditSpeR(text);
}
void MainWindow::handleEditSpeG(const QString &text)
{
    this->interfaceQT->updateEditSpeG(text);
}
void MainWindow::handleEditSpeB(const QString &text)
{
    this->interfaceQT->updateEditSpeB(text);
}
void MainWindow::handleEditSpeExp(const QString &text)
{
    this->interfaceQT->updateEditSpeExp(text);
}

/* QComboBox */
void MainWindow::handleEditMat()
{
    this->interfaceQT->updateEditMat(this->interfaceQT->editMat->currentText());
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
void MainWindow::delTarget()
{
    this->statusBar()->showMessage(tr("Invoked <DEL TARGET>"));
    if (this->interfaceQT->targetP != nullptr)
    {
        this->viewer->getScene()->removePointCloudAtIndex(this->interfaceQT->indexP);
        this->updateViewer();
    }
}
void MainWindow::newScene()
{
    this->statusBar()->showMessage(tr("Invoked <NEW SCENE>"));
    this->viewer->sceneNew();
    this->updateViewer();
}
void MainWindow::openScene()
{
    this->statusBar()->showMessage(tr("Invoked <OPEN SCENE>"));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(), tr("JSON Files (*.json);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        this->viewer->sceneReadJSON(fileName.toStdString());
    }
    this->updateViewer();
}
void MainWindow::saveScene()
{
    this->statusBar()->showMessage(tr("Invoked <SAVE SCENE>"));
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), QString(), tr("JSON Files (*.json);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        this->viewer->sceneWriteJSON(fileName.toStdString() + ".json");
    }
    this->updateViewer();
}

void MainWindow::drawAxis()
{
    this->statusBar()->showMessage(tr("Invoked <DRAW AXIS>"));
    this->viewer->setAxisIsDrawn(!this->viewer->axisIsDrawn());
}
void MainWindow::drawGrid()
{
    this->statusBar()->showMessage(tr("Invoked <DRAW GRID>"));
    this->viewer->setGridIsDrawn(!this->viewer->gridIsDrawn());
}
void MainWindow::drawFPS()
{
    this->statusBar()->showMessage(tr("Invoked <DRAW FPS>"));
    this->viewer->setFPSIsDisplayed(!this->viewer->FPSIsDisplayed());
}
void MainWindow::drawNormals()
{
    this->statusBar()->showMessage(tr("Invoked <DRAW NORMALS>"));
    this->viewer->toggleDrawNormals();
}

void MainWindow::importPointCloud()
{
    this->statusBar()->showMessage(tr("Invoked <IMPORT POINT CLOUD>"));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), QString(), tr("PN Files (*.pn);;All Files (*)"));
    if (!fileName.isEmpty())
    {
        PopupCreate popup(PointCloudType::IMPORT);
        popup.exec();
        this->viewer->getScene()->generateImport(fileName.toStdString(), (double)popup.getValue());
    }
}

void MainWindow::createPlane()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE PLANE>"));

    PopupCreate popup(PointCloudType::PLANE);
    popup.exec();

    this->viewer->getScene()->generatePrimitive(PointCloudType::PLANE, (int)popup.getValue());
}
void MainWindow::createCube()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE CUBE>"));

    PopupCreate popup(PointCloudType::CUBE);
    popup.exec();

    this->viewer->getScene()->generatePrimitive(PointCloudType::CUBE, (int)popup.getValue());
}
void MainWindow::createSphere()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE SPHERE>"));

    PopupCreate popup(PointCloudType::SPHERE);
    popup.exec();

    this->viewer->getScene()->generatePrimitive(PointCloudType::SPHERE, (int)popup.getValue());
}
void MainWindow::createTorus()
{
    this->statusBar()->showMessage(tr("Invoked <CREATE TORUS>"));

    PopupCreate popup(PointCloudType::TORUS);
    popup.exec();

    this->viewer->getScene()->generatePrimitive(PointCloudType::TORUS, (int)popup.getValue());
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

    /* Ctrl + a pour menu contextuel */
    delTargetAct = new QAction(tr("&Delete object"), this);
    delTargetAct->setShortcuts(QKeySequence::Delete);
    delTargetAct->setStatusTip(tr("Delete the target from the scene"));
    this->connect(delTargetAct, &QAction::triggered, this, &MainWindow::delTarget);

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

    /* Display */
    drawAxisAct = new QAction(tr("&Display Axis"), this);
    drawAxisAct->setStatusTip(tr("World axis is drawn by the viewer"));
    this->connect(drawAxisAct, &QAction::triggered, this, &MainWindow::drawAxis);
    drawGridAct = new QAction(tr("&Display Grid"), this);
    drawGridAct->setStatusTip(tr("Grid is drawn by the viewer."));
    this->connect(drawGridAct, &QAction::triggered, this, &MainWindow::drawGrid);
    drawFPSAct = new QAction(tr("&Display FPS"), this);
    drawFPSAct->setStatusTip(tr("Current frame rate is drawn by the viewer."));
    this->connect(drawFPSAct, &QAction::triggered, this, &MainWindow::drawFPS);
    drawNormalsAct = new QAction(tr("&Display Normals"), this);
    drawNormalsAct->setStatusTip(tr("Normals of points clouds are drawn by the viewer."));
    this->connect(drawNormalsAct, &QAction::triggered, this, &MainWindow::drawNormals);

    /* PointCloud */
    importPointCloudAct = new QAction(tr("&Import PointCloud"), this);
    importPointCloudAct->setShortcuts(QKeySequence::DeleteEndOfLine);
    importPointCloudAct->setStatusTip(tr("Import a point cloud from disk"));
    this->connect(importPointCloudAct, &QAction::triggered, this, &MainWindow::importPointCloud);
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

    displayMenu = menuBar()->addMenu(tr("&Display"));
    displayMenu->addAction(drawAxisAct);
    displayMenu->addAction(drawGridAct);
    displayMenu->addAction(drawFPSAct);
    displayMenu->addAction(drawNormalsAct);
    
    pointCloudMenu = menuBar()->addMenu(tr("&PointCloud"));
    pointCloudMenu->addAction(importPointCloudAct);
    pointCloudMenu->addSeparator();
    pointCloudMenu->addAction(genPlaneAct);
    pointCloudMenu->addAction(genCubeAct);
    pointCloudMenu->addAction(genSphereAct);
    pointCloudMenu->addAction(genTorusAct);
    pointCloudMenu->addSeparator();
    pointCloudMenu->addAction(delTargetAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}