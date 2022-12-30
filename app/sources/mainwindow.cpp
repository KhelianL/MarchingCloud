#include <mainwindow.h>

MainWindow::MainWindow()
{
    // Création des divers widgets
    QProgressBar *progressBar = new QProgressBar;
    QSplitter *splitter = new QSplitter;
    QGridLayout *optionLayout = new QGridLayout;
    QWidget *optionWidget = new QWidget;
    QPushButton *button1 = new QPushButton(tr("Bouton 1"));
    QPushButton *button2 = new QPushButton(tr("Bouton 2"));
    QPushButton *button3 = new QPushButton(tr("Bouton 3"));
    QPushButton *button4 = new QPushButton(tr("Bouton 4"));
    QPushButton *button5 = new QPushButton(tr("Bouton 5"));

    // Configuration de la barre d'état et ajout de la barre de progression
    progressBar->setRange(0, 100);
    progressBar->setValue(50);
    this->statusBar()->addPermanentWidget(progressBar);

    // Liaisons des widgets et création du viewer
    optionLayout->addWidget(button1, 0, 0);
    optionLayout->addWidget(button2, 0, 1);
    optionLayout->addWidget(button3, 1, 0);
    optionLayout->addWidget(button4, 1, 1);
    optionLayout->addWidget(button5, 2, 0, 1, 2);
    optionWidget->setLayout(optionLayout);
    this->viewer = new Viewer(this->scene, splitter);
    splitter->addWidget(optionWidget);

    this->setCentralWidget(splitter);

    this->createActions();
    this->createMenus();

    this->statusBar()->showMessage(tr("A context menu is available by right-clicking"));

    this->setWindowTitle(tr("Menus"));
    this->setMinimumSize(160, 160);
    this->resize(480, 320);
}

MainWindow::~MainWindow()
{
    delete this->scene;
}

void MainWindow::showCustomMenu()
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(QCursor::pos());
    this->statusBar()->showMessage(tr("Invoked <b>shortcut ctrl+A</b>"));
}

void MainWindow::newFile()
{
    this->statusBar()->showMessage(tr("Invoked <b>File|New</b>"));
}

void MainWindow::open()
{
    this->statusBar()->showMessage(tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save()
{
    this->statusBar()->showMessage(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::print()
{
    this->statusBar()->showMessage(tr("Invoked <b>File|Print</b>"));
}

void MainWindow::undo()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::cut()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Cut</b>"));
}

void MainWindow::copy()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::bold()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::justify()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Justify</b>"));
}

void MainWindow::center()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::setLineSpacing()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing()
{
    this->statusBar()->showMessage(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void MainWindow::about()
{
    this->statusBar()->showMessage(tr("Invoked <b>Help|About</b>"));
    this->viewer->help();
}

void MainWindow::createActions()
{
    shortcut = new QShortcut(QKeySequence::SelectAll, this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(showCustomMenu()));

    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    this->connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    this->connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    this->connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the document"));
    this->connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    this->connect(exitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    this->connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));
    this->connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    this->connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    this->connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    this->connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    boldAct->setStatusTip(tr("Make the text bold"));
    this->connect(boldAct, &QAction::triggered, this, &MainWindow::bold);

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    italicAct->setStatusTip(tr("Make the text italic"));
    this->connect(italicAct, &QAction::triggered, this, &MainWindow::italic);

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
                                       "paragraph"));
    this->connect(setLineSpacingAct, &QAction::triggered, this, &MainWindow::setLineSpacing);

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    this->connect(setParagraphSpacingAct, &QAction::triggered,
                  this, &MainWindow::setParagraphSpacing);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    this->connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    leftAlignAct->setStatusTip(tr("Left align the selected text"));
    this->connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    rightAlignAct->setStatusTip(tr("Right align the selected text"));
    this->connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    justifyAct->setStatusTip(tr("Justify the selected text"));
    this->connect(justifyAct, &QAction::triggered, this, &MainWindow::justify);

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    centerAct->setStatusTip(tr("Center the selected text"));
    this->connect(centerAct, &QAction::triggered, this, &MainWindow::center);

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);

    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
}