#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class SpreadSheet : public QTableWidget
{
    Q_OBJECT
public:
    explicit SpreadSheet(QWidget *parent = 0);

    bool    readFile(const QString &fileName);
    bool    writeFile(const QString &fileName);
    QString currentLocation();
    QString currentFormula();

signals:
    
public slots:

private slots:
    void findNext(const QString &, Qt::CaseSensitivity);
    void findPrevious(const QString &, Qt::CaseSensitivity);
};

#endif // SPREADSHEET_H
