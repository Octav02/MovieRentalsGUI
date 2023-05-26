#pragma once

#include "GUI.h"

class WatchlistCRUDGUI : public QWidget, public Observer{
private:
    Service &service;
    QTableWidget *table = new QTableWidget();
    QPushButton *btnAdd = new QPushButton("Add");
    QPushButton *btnDelete = new QPushButton("Delete");
    QPushButton *btnSaveToFile = new QPushButton("Save to file");
    QPushButton *btnGenerateWatchlist = new QPushButton("Generate watchlist");

    QLineEdit *titleText = new QLineEdit("");
    QLineEdit *genreText = new QLineEdit("");
    QLineEdit *yearText = new QLineEdit("");
    QLineEdit *mainActorText = new QLineEdit("");
    QLineEdit *fileName = new QLineEdit("");
    QLineEdit *numberOfMovies = new QLineEdit("");

    void initGUI();

    void initConnect();

    void loadData();
public:
    WatchlistCRUDGUI(Service &service1) : service{service1} {
        service.addObserver(this);
        initGUI();
        initConnect();
        loadData();
    }

    void update() override {
        loadData();
    }

};

