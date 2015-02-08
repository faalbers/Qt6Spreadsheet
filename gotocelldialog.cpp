#include "gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    //Setting 'this' on new Qt objects will automatically delete
    //them if 'this' gets deleted. It makes it it's child
    //If adding child to QWidget it will also be shown within the
    //parents area
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    //Connecting to existing sllots of the dialog
    //Close Dialog and set it's result value QDialog::Accepted
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    //Close Dialog and set it's result value QDialog::Rejected
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

}

GoToCellDialog::~GoToCellDialog()
{
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    //hasAcceptableInput() based on validator of lineEdit
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}

