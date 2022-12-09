#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "simulation.h"
#include "constants.h"
#include "qmovie.h"
#include <QWidget>
#include <QPainter>


class GameCanvas : public QWidget {
    Q_OBJECT
    QPainter painter;

public:
    explicit GameCanvas(QWidget* parent, std::vector<std::vector<MapTile>> map);

private:
    Simulation *s;
    // varibles for drawing the map
    QPixmap scaledWallMap;
    QPixmap scaledBlockMap;
    QPixmap scaledPitMap;
    QColor groundColor;

    // record the robot position
    int robotX;
    int robotY;
    int robotSize;
    int interval;
    direction preDir;

    // robot movies
    QTimer * timer;
    QMovie* rightWaiting;
    QMovie* leftWaiting;
    QMovie* upWaiting;
    QMovie* downWaiting;
    QMovie* rightRunning;
    QMovie* leftRunning;

    // cheese icon
    QPixmap scaledCheeseMap;

    // current map
    std::vector<std::vector<MapTile>> map;

    int brickSize;

public slots:
    void setMap(std::vector<std::vector<MapTile>> map);
    void simulate(std::vector<ProgramBlock> program);
    void step();
    void run(int interval);
    void setInterval(int interval);
    void stop();
    void emitRunningBlock(int block);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void robotMovie(QMovie*);
    void showRobot(QPoint, int);
    void showCheese(QPoint, int);
    void gameLost();
    void gameWon();
    void restartGame();
    void currentBlock(int);
};

#endif // GAMECANVAS_H
