#include <QApplication>
#include <QTableView>
#include <QtSql>
#include <QStandardItemModel>

#include "MultisortTableView.h"
#include "MultisortTreeView.h"

void createDataTable()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(":memory:");
    db.open();

    db.transaction();
    QSqlQuery query;
    query.exec("CREATE TABLE users "
               "("
               "surname TEXT, "
               "name TEXT, "
               "birth_year INTEGER"
               ")");
    query.exec("insert into users values('Page', 'Larry', 1973);");
    query.exec("insert into users values('Jobs', 'Steve', 1955);");
    query.exec("insert into users values('Gates', 'Bill', 1955);");
    query.exec("insert into users values('Gates', 'Bill12', 11);");
    query.exec("insert into users values('Zuckerberg', 'Mark11', 1);");
    query.exec("insert into users values('Zuckerberg', 'Mark09', 2);");

    db.commit();
}

QList<QStandardItem *> prepareRow(const QString &first,
                                  const QString &second,
                                  const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    rowItems << new QStandardItem(third);
    return rowItems;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // -------------------------------------
    // Table View
    // -------------------------------------
    createDataTable();

    QSqlTableModel *users = new QSqlTableModel;
    users->setTable( "users" );
    users->select( );

    MultisortTableView* tableView = new MultisortTableView;
    tableView->setModifier( Qt::ControlModifier );
    tableView->setSortingEnabled( true );
    tableView->setSortIcons( QIcon(":/icons/bullet_arrow_up.png"),
                            QIcon(":/icons/bullet_arrow_down.png") );
    tableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    tableView->setModel( users );

    // -------------------------------------
    // Tree View
    // -------------------------------------
    QStandardItemModel* standardModel = new QStandardItemModel;
    QList<QStandardItem *> preparedRow =prepareRow("first", "second", "third");
    QStandardItem *item = standardModel->invisibleRootItem();
    item->appendRow(preparedRow);
    preparedRow.first()->appendRow(prepareRow("Page", "Larry", "1973"));
    preparedRow.first()->appendRow(prepareRow("Jobs", "Steve", "1955"));
    preparedRow.first()->appendRow(prepareRow("Gates", "Bill", "1955"));
    preparedRow.first()->appendRow(prepareRow("Gates", "Bill12", "11"));
    preparedRow.first()->appendRow(prepareRow("Zuckerberg", "Mark11", "1"));
    preparedRow.first()->appendRow(prepareRow("Zuckerberg", "Mark09", "2"));

    MultisortTreeView* treeView = new MultisortTreeView;
    treeView->setModifier( Qt::ControlModifier );
    treeView->setSortingEnabled( true );
    treeView->setSortIcons( QIcon(":/icons/bullet_arrow_up.png"),
                            QIcon(":/icons/bullet_arrow_down.png") );
    treeView->setSelectionBehavior( QAbstractItemView::SelectRows );
    treeView->setModel( standardModel );

    // -------------------------------------
    // Combine In Tab Widget
    // -------------------------------------
    QTabWidget tabWidget;
    tabWidget.addTab(tableView,"Table View");
    tabWidget.addTab(treeView,"Tree View");
    tabWidget.resize(400, 300);
    tabWidget.show();

    return a.exec();
}
