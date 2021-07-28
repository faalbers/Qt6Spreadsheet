#include "spreadsheet.hpp"

SpreadSheet::SpreadSheet(QWidget *parent) :
    QTableWidget(parent)
{
}

bool SpreadSheet::readFile(const QString &fileName)
{
    Q_UNUSED(fileName);
    return false;
}

bool SpreadSheet::writeFile(const QString &fileName)
{
    Q_UNUSED(fileName);
    return false;
}

QString SpreadSheet::currentLocation()
{
    return QString(tr("B001"));
}

QString SpreadSheet::currentFormula()
{
    return QString(tr("Blah Blah Formula"));
}

void SpreadSheet::findNext(const QString &, Qt::CaseSensitivity)
{

}

void SpreadSheet::findPrevious(const QString &, Qt::CaseSensitivity)
{

}
