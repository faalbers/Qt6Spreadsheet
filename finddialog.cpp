#include "finddialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>


FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    label = new QLabel(tr("Find &what:")); //Alt-w shortcut
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit); //Shortcut Alt-w will set focus to lineEdit

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find")); //Alt-f shortcut
    findButton->setDefault(true); //Button that is pressed when pushing enter
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
        this, SLOT(enableFindButton(const QString &)));
    connect(findButton, SIGNAL(clicked()),
        this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()),
        this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height()); //sizeHint returns widget's ideal size
}

void FindDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
        caseCheckBox->isChecked()   ? Qt::CaseSensitive
                                    : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs); //signal because will be connected to slots
    } else {
        emit findNext(text, cs); //signal because will be connected to slots
    }
}

void FindDialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

