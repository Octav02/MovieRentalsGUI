
#include "GUI.h"

void GUI::initGUI() {
    auto mainLayout = new QHBoxLayout();

    setLayout(mainLayout);
    mainLayout->addWidget(table);

    auto verticalLayer1 = new QVBoxLayout();
    auto formLayout = new QFormLayout();


    formLayout->addRow("Title", titleText);
    formLayout->addRow("Genre", genreText);
    formLayout->addRow("Year", yearText);
    formLayout->addRow("Main Actor", mainActorText);

    verticalLayer1->addLayout(formLayout);
    auto horizontalLayer1 = new QHBoxLayout();
    horizontalLayer1->addWidget(btnAdd);
    horizontalLayer1->addWidget(btnExit);
    verticalLayer1->addLayout(horizontalLayer1);
    mainLayout->addLayout(verticalLayer1);

}

void GUI::loadData(const vector<Movie>& movies) {
    table->clear();
    table->setRowCount(0);
    for (const auto& movie : movies) {
        int row = table->rowCount();
        table->insertRow(row);
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
}
