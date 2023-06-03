#pragma once

#include "Service.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <vector>
#include <string>
#include "WatchlistCRUDGUI.h"
#include "JustListGUI.h"
#include "WatchListReadOnlyGUI.h"
#include "Observer.h"
#include "TableModel.h"
#include <QHeaderView>

class GUI : public QWidget{
private:
    Service& service;
    QTableWidget* table = new QTableWidget(0,4);
    QTableView* tableView = new QTableView();
    TableModel* model = new TableModel(service);

    QPushButton* btnExit = new QPushButton("Exit");
    QPushButton* btnAdd = new QPushButton("Add");
    QPushButton* btnUpdate = new QPushButton("Update");
    QPushButton* btnDelete = new QPushButton("Delete");
    QPushButton* btnReadOnly = new QPushButton("Read Only Watchlist");
    QPushButton* btnUndo = new QPushButton("Undo");

    QVBoxLayout* buttonLayout = new QVBoxLayout();

    QPushButton* btnFilterByTitle = new QPushButton("Filter by title");
    QPushButton* btnFilterByYear = new QPushButton("Filter by year");
    QPushButton* btnFilterByGenre = new QPushButton("Filter by genre");
    QPushButton* btnSortByTitle = new QPushButton("Sort by title");
    QPushButton* btnSortByGenre = new QPushButton("Sort by genre");
    QPushButton* btnSortByYear = new QPushButton("Sort by year");
    QPushButton* btnSortByMainActor = new QPushButton("Sort by main actor");
    QPushButton* btnWatchList = new QPushButton("Watchlist Window");


    vector<QPushButton*> genreButtons;


    QLineEdit* titleText = new QLineEdit();
    QLineEdit* genreText = new QLineEdit();
    QLineEdit* yearText = new QLineEdit();
    QLineEdit* mainActorText = new QLineEdit();

    void initGUI();
    void loadData(const vector<Movie>& movies);
    void initConnect();
    void addButtons();

public:
    GUI(Service& service) : service{service} {
        initGUI();
        loadData(service.getAll());
        addButtons();
        initConnect();

    }
    GUI() = delete;

    void addMovie();

    void updateMovie();

    void deleteMovie();
};

