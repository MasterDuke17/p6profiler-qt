#include "RoutineView.h"
#include "RoutineItemDelegate.h"

RoutineView::RoutineView(QWidget *parent) : QWidget(parent)
{
    vbox = new QVBoxLayout(this);
    searchField = new QLineEdit();
    searchField->setPlaceholderText("Search...");
    connect(searchField, SIGNAL(textChanged(const QString&)),
            this, SLOT(setFilterText(const QString&)));
    vbox->addWidget(searchField);
    tableView = new QTableView(this);
    tableView->verticalHeader()->hide();
    tableView->resizeColumnsToContents();
    tableView->setSortingEnabled(true);
    tableView->setItemDelegate(new RoutineItemDelegate(tableView));
    tableView->horizontalHeader()
             ->setSectionResizeMode(QHeaderView::Stretch);
    vbox->addWidget(tableView);
    setLayout(vbox);
}

void RoutineView::setModel(RoutineListModel *rlm)
{
    sfpmodel.setSourceModel(rlm);
    sfpmodel.setFilterKeyColumn(0);
    sfpmodel.setSortRole(Qt::UserRole);
    tableView->setModel(&sfpmodel);
}

void RoutineView::setFilterText(const QString& query)
{
    sfpmodel.setFilterRegExp(QRegExp(query, Qt::CaseInsensitive));
}
