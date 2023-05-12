#pragma once

#include "GUI.h"

class WatchlistGUI : public QWidget {
private:
    Service &service;
    QTableWidget *table = new QTableWidget();
    QPushButton *btnAdd = new QPushButton("Add");
    QPushButton *btnDelete = new QPushButton("Delete");
    QPushButton *btnSaveToFile = new QPushButton("Save to file");

    QLineEdit *titleText = new QLineEdit("Title");
    QLineEdit *genreText = new QLineEdit("Genre");
    QLineEdit *yearText = new QLineEdit("Year");
    QLineEdit *mainActorText = new QLineEdit("Main Actor");
    QLineEdit *fileName = new QLineEdit("File name");

    void initGUI();

    void initConnect();

    void loadData();
public:
    WatchlistGUI(Service &service1) : service{service1} {
        initGUI();
        initConnect();
        loadData();
    }

};

