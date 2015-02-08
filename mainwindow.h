#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void openRecentFile();
    void find();
    void goToCell();
    void sort();
    void about();
    void updateStatusBar();
    void spreadsheetModified();

private:
    Ui::MainWindow *ui;
    SpreadSheet *spreadsheet;
    FindDialog  *findDialog;

    QMenu       *fileMenu;
    QAction     *newAction;
    QAction     *openAction;
    QAction     *saveAction;
    QAction     *saveAsAction;
    QAction     *exitAction;
    QAction     *separatorAction;
    enum        { MaxRecentFiles = 5 };
    QAction     *recentFileActions[MaxRecentFiles];
    QStringList recentFiles;
    QString     curFile;


    QMenu       *editMenu;
    QAction     *cutAction;
    QAction     *copyAction;
    QAction     *pasteAction;
    QAction     *deleteAction;

    QMenu       *selectSubMenu;
    QAction     *selectRowAction;
    QAction     *selectColumnAction;
    QAction     *selectAllAction;

    QAction     *findAction;
    QAction     *goToCellAction;

    QMenu       *toolsMenu;
    QAction     *recalculateAction;
    QAction     *sortAction;

    QMenu       *optionsMenu;
    QAction     *showGridAction;

    QMenu       *helpMenu;
    QAction     *aboutQtAction;

    QToolBar    *fileToolBar;

    QToolBar    *editToolBar;

    QLabel      *locationLabel;
    QLabel      *formulaLabel;

    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void setCurrentFile(const QString &fileName);
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void writeSettings();
    QString strippedName(const QString &fullFileName);
    void updateRecentFileActions();
    /*
    void readSettings();
    void writeSettings();
    */

};

#endif // MAINWINDOW_H
