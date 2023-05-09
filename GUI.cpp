
#include "GUI.h"

void GUI::initGUI() {
    auto mainLayout = new QHBoxLayout();

    setLayout(mainLayout);
    mainLayout->addWidget(table);

    auto verticalLayer2 = new QVBoxLayout();
    auto verticalLayer1 = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    verticalLayer2->addLayout(formLayout);
    auto horizontalLayer2 = new QHBoxLayout();
    horizontalLayer2->addWidget(btnSortByTitle);
    horizontalLayer2->addWidget(btnSortByGenre);
    horizontalLayer2->addWidget(btnSortByYear);
    horizontalLayer2->addWidget(btnSortByMainActor);
    horizontalLayer2->addWidget(btnFilterByTitle);
    horizontalLayer2->addWidget(btnFilterByYear);

    verticalLayer2->addLayout(horizontalLayer2);

    formLayout->addRow("Title", titleText);
    formLayout->addRow("Genre", genreText);
    formLayout->addRow("Year", yearText);
    formLayout->addRow("Main Actor", mainActorText);


    verticalLayer1->addLayout(verticalLayer2);
    auto horizontalLayer1 = new QHBoxLayout();
    horizontalLayer1->addWidget(btnAdd);
    horizontalLayer1->addWidget(btnExit);
    horizontalLayer1->addWidget(btnUpdate);
    horizontalLayer1->addWidget(btnDelete);
    verticalLayer1->addLayout(horizontalLayer1);
    verticalLayer1->addWidget(btnUndo);
    mainLayout->addLayout(verticalLayer1);

}

void GUI::loadData(const vector<Movie>& movies) {
    table->clear();
    table->setRowCount(0);
    for (const auto& movie : movies) {
        int row = table->rowCount();
        table->insertRow(row);
        //Set color to red
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(to_string(movie.getYear()))));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getMainActor())));

    }
}

void GUI::addMovie() {

    qDebug() << "Add apasat";
    try {
        string title = titleText->text().toStdString();
        string genre = genreText->text().toStdString();
        int year = stoi(yearText->text().toStdString());
        string mainActor = mainActorText->text().toStdString();
        service.addMovie(title, genre, year, mainActor);
        loadData(service.getAll());
    }
    catch (const RepositoryException& exception) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.what()));
    }
    catch (const ValidationException& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
    catch (const exception& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
}

void GUI::initConnect() {
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        qDebug() << "Exit apasat";
        close();
    });
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        qDebug() << "Add apasat";
        addMovie();
    });
    QObject::connect(btnUpdate, &QPushButton::clicked, [&](){
        qDebug() << "Update apasat";
        updateMovie();
    });
    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        qDebug() << "Delete apasat";
        deleteMovie();
    });
    QObject::connect(btnFilterByTitle, &QPushButton::clicked, [&]() {
        qDebug() << "Filter by title apasat";
        string title = titleText->text().toStdString();
        auto wdg = new JustListGUI(service.getMoviesByTitle(title));
        wdg->show();
    });
    QObject::connect(btnFilterByYear,&QPushButton::clicked, [&]() {
        qDebug() << "Filter by year apasat";
        try {
            int year = stoi(yearText->text().toStdString());
            auto wdg = new JustListGUI(service.getMoviesByYear(year));
            wdg->show();
        }
        catch (const exception& exception) {
            QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
        }

    });
    QObject::connect(btnSortByTitle, &QPushButton::clicked, [&]() {
        qDebug() << "Sort by title apasat";
        auto wdg = new JustListGUI(service.sortMoviesByTitle(true));
        wdg->show();
//        loadData(service.sortMoviesByTitle(true));

    });
    QObject::connect(btnSortByGenre, &QPushButton::clicked, [&]() {
        qDebug() << "Sort by genre apasat";
        auto wdg = new JustListGUI(service.sortMoviesByGenre(true));
        wdg->show();
//        loadData(service.sortMoviesByGenre(true));
    });
    QObject::connect(btnSortByYear, &QPushButton::clicked, [&]() {
        qDebug() << "Sort by year apasat";
        auto wdg = new JustListGUI(service.sortMoviesByYear(true));
        wdg->show();
        loadData(service.sortMoviesByYear(true));
    });
    QObject::connect(btnSortByMainActor, &QPushButton::clicked, [&]() {
        qDebug() << "Sort by main actor apasat";
        auto wdg = new JustListGUI(service.sortMoviesByMainActor(true));
        wdg->show();
        loadData(service.sortMoviesByMainActor(true));
    });
    QObject:connect(table, &QTableWidget::itemSelectionChanged, [&]() {
        qDebug() << "Selection changed";
        auto selectedRow = table->selectedItems();
        if (selectedRow.empty()) {
            titleText->setText("");
            genreText->setText("");
            yearText->setText("");
            mainActorText->setText("");
            return;
        }

        auto selectedTitle = selectedRow.at(0);
        auto selectedGenre = selectedRow.at(1);
        auto selectedYear = selectedRow.at(2);
        auto selectedMainActor = selectedRow.at(3);
        titleText->setText(selectedTitle->text());
        genreText->setText(selectedGenre->text());
        yearText->setText(selectedYear->text());
        mainActorText->setText(selectedMainActor->text());
    });
}

void GUI::updateMovie() {
    try {
        string title = titleText->text().toStdString();
        string genre = genreText->text().toStdString();
        int year = stoi(yearText->text().toStdString());
        string mainActor = mainActorText->text().toStdString();
        service.updateMovie(title, genre, year, mainActor);
        loadData(service.getAll());
    }
    catch (const RepositoryException& exception) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.what()));
    }
    catch (const ValidationException& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
    catch (const exception& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
}

void GUI::deleteMovie() {
    try {
        string title = titleText->text().toStdString();
        service.removeMovie(title,"",2,"");
        loadData(service.getAll());
    }
    catch (const RepositoryException& exception) {
        QMessageBox::information(nullptr, "Error", QString::fromStdString(exception.what()));
    }
    catch (const ValidationException& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
    catch (const exception& exception) {
        QMessageBox::critical(this, "Error", QString::fromStdString(exception.what()));
    }
}
