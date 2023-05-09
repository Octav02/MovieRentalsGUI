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

class GUI : public QWidget{
private:
    Service& service;
    QTableWidget* table = new QTableWidget(0,4);
    QPushButton* btnExit = new QPushButton("Exit");
    QPushButton* btnAdd = new QPushButton("Add");


    QLineEdit* titleText = new QLineEdit();
    QLineEdit* genreText = new QLineEdit();
    QLineEdit* yearText = new QLineEdit();
    QLineEdit* mainActorText = new QLineEdit();

    void initGUI();
    void loadData(const vector<Movie>& movies);
    void initConnect();

public:
    GUI(Service& service) : service{service} {
        initGUI();
        loadData(service.getAll());
        initConnect();
    }
    GUI() = delete;

    void addMovie();

};

