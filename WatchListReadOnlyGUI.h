#pragma once
#include "GUI.h"
#include <QPaintEvent>
#include <QPainter>

class WatchListReadOnlyGUI : public QWidget, public Observer{
private:
    QTableWidget* table = new QTableWidget(0,4);
    Service& service;
    void initGUI();
    void loadData();
    void paintEvent(QPaintEvent* event) override;
public:
    WatchListReadOnlyGUI(Service& service) : service{service} {
        service.addObserver(this);
        initGUI();
        loadData();
    }
    void update() override {
        loadData();
        repaint();
    }
};
