#include "gotocelldialog.hpp"
#include "./ui_gotocelldialog.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
    , ui_(new Ui::GoToCellDialog)
{
    ui_->setupUi(this);
    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    //Setting 'this' on new Qt objects will automatically delete
    //them if 'this' gets deleted. It makes it it's child
    //If adding child to QWidget it will also be shown within the
    //parents area
    ui_->lineEdit->setValidator(new QRegularExpressionValidator(regExp, this));

    //Connecting to existing sllots of the dialog
    //Close Dialog and set it's result value QDialog::Accepted
    connect(ui_->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    //Close Dialog and set it's result value QDialog::Rejected
    connect(ui_->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

}

GoToCellDialog::~GoToCellDialog()
{
}

QString GoToCellDialog::get()
{
    return ui_->lineEdit->text().toUpper();
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    //hasAcceptableInput() based on validator of lineEdit
    ui_->okButton->setEnabled(ui_->lineEdit->hasAcceptableInput());
}

