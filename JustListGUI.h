#pragma once
#include "GUI.h"

class JustListGUI : public QWidget {
private:
    vector<Movie> movies;
    QTableWidget *table = new QTableWidget(0, 4);

    void initGUI();
    void loadData();
public:
    JustListGUI(vector<Movie> movies) : movies{movies} {
        initGUI();
        loadData();
    }

};
