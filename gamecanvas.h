#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "constants.h"
#include <QWidget>


class GameCanvas : public QWidget {
    Q_OBJECT
public:
    explicit GameCanvas(QWidget* parent, std::vector<std::vector<MapTile>> map);
    std::vector<std::vector<MapTile>> map;

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void showRobot(QPoint);
    void showCheese(QPoint);
};

#endif // GAMECANVAS_H
