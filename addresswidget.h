



#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H


#include <QItemSelection>
#include <QTabWidget>
#include "tablemodel.h"
#include "tableview.h"

QT_BEGIN_NAMESPACE

#ifndef PROJECTDATA_H
#define PROJECTDATA_H
struct ProjectData{
    QByteArray memorydata;
    QVector< QList<QPair<QString, QString>>>   vectorListofPairs;
    QStringList regviewtablelist;
    QString SPUFileDir;
    QString MPUFileDir;
//    QVector<QList<QString>>     vectorBreakPointList;                    //breakpoints
//    QList<QString>              spuBreakPointList;
//    QList<QString>              mpuBreakPointList;

};
#endif // PROJECTDATA_H

QT_END_NAMESPACE

//! [0]
class AddressWidget : public QTabWidget
{
    Q_OBJECT

public:
    AddressWidget(QWidget *parent = 0);
    TableView *tableView[100];

public slots:

//    void addEntry(QString name, QString address);
//    void editEntry();
//    void removeEntry();

signals:
//    void selectionChanged (const QItemSelection &selected);

private:
    void setupTabs();

//    TableModel *table;
//    QSortFilterProxyModel *proxyModel;
};
//! [0]



#endif // ADDRESSWIDGET_H

