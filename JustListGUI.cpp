
#include "JustListGUI.h"

void JustListGUI::initGUI() {
    //Print the table
    auto mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(table);

    show();
}

void JustListGUI::loadData() {
    table->clear();
    table->setRowCount(0);
    for (const auto & movie : movies) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(to_string(movie.getYear()))));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getMainActor())));
    }
}
