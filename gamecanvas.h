#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "constants.h"
#include "qmovie.h"
#include <QWidget>


class GameCanvas : public QWidget {
    Q_OBJECT
public:
    explicit GameCanvas(QWidget* parent, std::vector<std::vector<MapTile>> map);
    std::vector<std::vector<MapTile>> map;

private:

    // varibles for drawing the map
    QPixmap scaledWallMap;
    QPixmap scaledBlockMap;
    QPixmap scaledPitMap;
    QColor groundColor;

    // record the robot position
    int robotX;
    int robotY;
    int robotSize;

    // robot movies
    QMovie* rightWaiting;
    QMovie* leftWaiting;
    QMovie* rightRunning;
    QMovie* leftRunning;

    // cheese icon
    QPixmap scaledCheeseMap;

    int brickSize;

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void robotMovie(QMovie*);
    void showRobot(QPoint, int);
    void showCheese(QPixmap, QPoint, int);
};

#endif // GAMECANVAS_H
