//
// Created by octav on 19.05.2023.
//

#include "WatchListReadOnlyGUI.h"

void WatchListReadOnlyGUI::initGUI() {
    auto mainLayout = new QHBoxLayout();
    setLayout(mainLayout);
    setBaseSize(500, 500);
}

void WatchListReadOnlyGUI::loadData() {
}

void WatchListReadOnlyGUI::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    vector<Movie> movies = service.getWatchlist();
    int x = 0, y = 0;
    for (const auto &movie: movies) {

        painter.drawRect(x, y, 20,30);
        QImage image("../img1.jpg");
        image.scaled(100,100,Qt::KeepAspectRatio);
        painter.drawImage(x,y,image);
        x += 150;
        y += 150;
    }

}