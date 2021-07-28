#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    spreadsheet(new SpreadSheet),
    findDialog(NULL)
{
    ui->setupUi(this);
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    /*
    readSettings();

    findDialog = 0;

    */
    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    // New File action
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // Open File action
    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open spreadsheet file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    // Save File action
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save to spreadsheet file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    // Save As File action
    saveAsAction = new QAction(tr("Save &As ..."), this);
    saveAsAction->setIcon(QIcon(":/images/icon.png"));
    saveAsAction->setStatusTip(tr("Save to spreadsheet file as ..."));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    // Recently opened file actions
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    // Exit action
    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Cut action
    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut"));
    //connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

    // Copy action
    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy"));
    //connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    // Paste action
    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste"));
    //connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    // Delete action
    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(tr("Del"));
    deleteAction->setStatusTip(tr("Delete"));
    //connect(deleteAction, SIGNAL(triggered()), this, SLOT(delete()));

    // Select All action, selectAll already implemented by QTabletWidget
    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(tr("Ctrl+A"));
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

    // Find action
    findAction = new QAction(tr("&Find ..."), this);
    findAction->setIcon(QIcon(":/images/find.png"));
    findAction->setShortcut(tr("Ctrl+F"));
    findAction->setStatusTip(tr("Find"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

    // Go to Cell action
    goToCellAction = new QAction(tr("&Go To Cell ..."), this);
    goToCellAction->setIcon(QIcon(":/images/goto.png"));
    goToCellAction->setShortcut(tr("F5"));
    goToCellAction->setStatusTip(tr("Go to cell in the spreadsheet"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

    // recalculate action

    // sort action
    sortAction = new QAction(tr("&Sort ..."), this);
    //goToCellAction->setIcon(QIcon(":/images/goto.png"));
    //goToCellAction->setShortcut(tr("F5"));
    goToCellAction->setStatusTip(tr("Sort in the spreadsheet"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(sort()));

    // Show grid action, setShowGrid already implemented by QTabletWidget
    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet’s grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    // About Qt info action
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library’s About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    // Create File menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Create Edit menu
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    // Create sub menu
    selectSubMenu = editMenu->addMenu(tr("&Select"));
    //selectSubMenu->addAction(selectRowAction);
    //selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    // Create Tools menu
    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    //toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    // Create Options menu
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    //optionsMenu->addAction(autoRecalcAction);

    // Create Help menu
    menuBar()->addSeparator(); // Add space between menus, only if in Motif or CDE style
    helpMenu = menuBar()->addMenu(tr("&Help"));
    //helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);
    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1); // makes this one stretchable

    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
        this, SLOT(updateStatusBar()));
    //connect(spreadsheet, SIGNAL(modified()),
    //    this, SLOT(spreadsheetModified()));
    updateStatusBar();
}

void MainWindow::newFile()
{
    if (okToContinue()) {
        spreadsheet->clear();
        setCurrentFile("");
    }

}

void MainWindow::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Spreadsheet"), ".",
            tr("Spreadsheet files (*.sp)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveFile(const QString &fileName)
{
    if (!spreadsheet->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Spreadsheet"), ".",
        tr("Spreadsheet files (*.sp)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::openRecentFile()
{
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    }

}

void MainWindow::find()
{
    if (!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, SIGNAL(findNext(const QString &,Qt::CaseSensitivity)),
            spreadsheet, SLOT(findNext(const QString &, Qt::CaseSensitivity)));
        connect(findDialog, SIGNAL(findPrevious(const QString &, Qt::CaseSensitivity)),
            spreadsheet, SLOT(findPrevious(const QString &, Qt::CaseSensitivity)));
    }
    findDialog->show();
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog dialog(this);
    // using dialog exec because we need it in modal mode,meaning
    // that only dialog is accessive and nothing else
    if (dialog.exec()) {
        QString str = dialog.get();
        //spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
        //    str[0].unicode() - ’A’);
    }
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    if (dialog.exec()) {
    }
}

void MainWindow::about()
{

}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();

}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = "Untitled";
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

bool MainWindow::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet"),
            tr("The document has been modified.\nDo you want to save your changes?"),
            QMessageBox::Yes | QMessageBox::Default,
            QMessageBox::No,
            QMessageBox::Cancel | QMessageBox::Escape);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2")
                .arg(j + 1)
                .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());

}

bool MainWindow::loadFile(const QString &fileName)
{
    if (!spreadsheet->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

void MainWindow::writeSettings()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();

    } else {
        event->ignore();
    }
}
