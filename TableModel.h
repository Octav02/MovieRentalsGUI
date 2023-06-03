#pragma once

#include "Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class TableModel : public QAbstractTableModel {
private:
    Service& service;
public:
    TableModel(Service& service1) : service{service1} {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return service.getAll().size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 4;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        int row = index.row();
        int column = index.column();
        Movie movie = service.getAll()[row];
        if (role == Qt::DisplayRole) {
            switch (column) {
                case 0:
                    return QString::fromStdString(movie.getTitle());
                case 1:
                    return QString::fromStdString(movie.getGenre());
                case 2:
                    return QString::fromStdString(std::to_string(movie.getYear()));
                case 3:
                    return QString::fromStdString(movie.getMainActor());
                default:
                    break;
            }
        }
        return QVariant();
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) {
                switch (section) {
                    case 0:
                        return QString("Title");
                    case 1:
                        return QString("Genre");
                    case 2:
                        return QString("Year of release");
                    case 3:
                        return QString("Main actor");
                    default:
                        break;
                }
            }
        }
        return QVariant();
    }
    void update() {
        emit layoutChanged();
    }

    void updateInternalData(const vector<Movie> &vector) {
        beginResetModel();
        endResetModel();
    }
};

