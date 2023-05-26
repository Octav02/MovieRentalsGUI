//
// Created by octav on 11.05.2023.
//

#include "WatchlistCRUDGUI.h"

void WatchlistCRUDGUI::initGUI() {
    auto mainLayout = new QHBoxLayout();

    setLayout(mainLayout);
    table->setColumnCount(4);
    mainLayout->addWidget(table);

    auto formLayout = new QFormLayout();
    formLayout->addRow("Title",titleText);
    formLayout->addRow("Genre",genreText);
    formLayout->addRow("Year",yearText);
    formLayout->addRow("Main actor",mainActorText);
    formLayout->addRow("File name", fileName);
    formLayout->addRow("Number of movies", numberOfMovies);
    mainLayout->addLayout(formLayout);

    auto buttonLayout = new QVBoxLayout();

    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnSaveToFile);
    buttonLayout->addWidget(btnGenerateWatchlist);
    mainLayout->addLayout(buttonLayout);
}

void WatchlistCRUDGUI::initConnect() {
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        try {
            service.addToWatchlist(titleText->text().toStdString(), genreText->text().toStdString(),
                                 stoi(yearText->text().toStdString()), mainActorText->text().toStdString());
            loadData();
            update();
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        try {
            service.deleteFromWatchlist(titleText->text().toStdString());
            loadData();
            update();
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(btnSaveToFile, &QPushButton::clicked, [&]() {
        try {
            string savedFileName = "../Watchlists/"+fileName->text().toStdString()+".csv";
            service.saveWatchlistToFile(savedFileName);
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(btnGenerateWatchlist, &QPushButton::clicked, [&]() {
        try {
            int numberOfMoviesInt = stoi(numberOfMovies->text().toStdString());
            service.generateWatchlist(numberOfMoviesInt);
            loadData();
            update();
        }
        catch (exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
        if (table->selectedItems().isEmpty()) {
            titleText->setText("");
            genreText->setText("");
            yearText->setText("");
            mainActorText->setText("");
            return;
        }

        auto selectedRow = table->selectedItems().at(0)->row();
        auto title = table->item(selectedRow, 0)->text();
        auto genre = table->item(selectedRow, 1)->text();
        auto year = table->item(selectedRow, 2)->text();
        auto mainActor = table->item(selectedRow, 3)->text();

        titleText->setText(title);
        genreText->setText(genre);
        yearText->setText(year);
        mainActorText->setText(mainActor);
    });
}

void WatchlistCRUDGUI::loadData() {
    vector<Movie> watchList = service.getWatchlist();
    table->clear();
    table->setRowCount(0);
    for (const auto& movie : watchList) {
        auto row = table->rowCount();
        table->insertRow(row);

        auto titleItem = new QTableWidgetItem(QString::fromStdString(movie.getTitle()));
        auto genreItem = new QTableWidgetItem(QString::fromStdString(movie.getGenre()));
        auto yearItem = new QTableWidgetItem(QString::fromStdString(to_string(movie.getYear())));
        auto mainActorItem = new QTableWidgetItem(QString::fromStdString(movie.getMainActor()));

        table->setItem(row, 0, titleItem);
        table->setItem(row, 1, genreItem);
        table->setItem(row, 2, yearItem);
        table->setItem(row, 3, mainActorItem);
    }
}

