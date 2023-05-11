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
#include "JustListGUI.h"

class GUI : public QWidget{
private:
    Service& service;
    QTableWidget* table = new QTableWidget(0,4);
    QPushButton* btnExit = new QPushButton("Exit");
    QPushButton* btnAdd = new QPushButton("Add");
    QPushButton* btnUpdate = new QPushButton("Update");
    QPushButton* btnDelete = new QPushButton("Delete");

    QPushButton* btnUndo = new QPushButton("Undo");

    QVBoxLayout* buttonLayout = new QVBoxLayout();

    QPushButton* btnFilterByTitle = new QPushButton("Filter by title");
    QPushButton* btnFilterByYear = new QPushButton("Filter by year");
    QPushButton* btnFilterByGenre = new QPushButton("Filter by genre");
    QPushButton* btnSortByTitle = new QPushButton("Sort by title");
    QPushButton* btnSortByGenre = new QPushButton("Sort by genre");
    QPushButton* btnSortByYear = new QPushButton("Sort by year");
    QPushButton* btnSortByMainActor = new QPushButton("Sort by main actor");


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

