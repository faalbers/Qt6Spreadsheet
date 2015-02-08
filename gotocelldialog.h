#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT
    
public:
    explicit GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();

private slots:
    //All slots following convention on_objectName_signalName()
    //will automatically be connected by setupUi()
    void on_lineEdit_textChanged();

};

#endif // GOTOCELLDIALOG_H
