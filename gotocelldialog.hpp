#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>
//#include "ui_gotocelldialog.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class GoToCellDialog; }
QT_END_NAMESPACE

class GoToCellDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();

    QString get();

private slots:
    //All slots following convention on_objectName_signalName()
    //will automatically be connected by setupUi()
    void on_lineEdit_textChanged();

private:
    Ui::GoToCellDialog                  *ui_;
};

#endif // GOTOCELLDIALOG_H
