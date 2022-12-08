#include "gamecanvas.h"
#include "constants.h"
#include "qtimer.h"
#include "simulation.h"
#include <QMovie>
#include <QPainter>

GameCanvas::GameCanvas(QWidget *parent, std::vector<std::vector<MapTile>> map)
    : QWidget{parent}, map(map) {
    this->setMinimumSize(QSize(1000, 2000));

    brickSize = 100;
    robotSize = 90;
    preDir = east;

    QPixmap wallMap(":/elements/brickwall.jpg");
    scaledWallMap = wallMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap blockMap(":/elements/block.png");
    scaledBlockMap = blockMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap pitMap(":/elements/pit.png");
    scaledPitMap = pitMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    rightWaiting = new QMovie(":/elements/robot-right.gif");
    rightWaiting->setScaledSize(QSize(robotSize, robotSize));
    leftWaiting = new QMovie(":/elements/robot-left.gif");
    leftWaiting->setScaledSize(QSize(robotSize, robotSize));
    upWaiting = new QMovie(":/elements/robot-up.gif");
    upWaiting->setScaledSize(QSize(robotSize, robotSize));
    downWaiting = new QMovie(":/elements/robot-down.gif");
    downWaiting->setScaledSize(QSize(robotSize, robotSize));

    rightRunning = new QMovie(":/elements/robot-run-right.gif");
    rightRunning->setScaledSize(QSize(robotSize, robotSize));

    leftRunning = new QMovie(":/elements/robot-run-right.gif");
    leftRunning->setScaledSize(QSize(robotSize, robotSize));

    QPixmap cheeseMap(":/elements/cheese.png");
    scaledCheeseMap = cheeseMap.scaled(robotSize, robotSize, Qt::KeepAspectRatio);

    groundColor = QColor::fromRgb(222, 184, 135);

    timer = new QTimer();

    connect(timer, &QTimer::timeout, this, &GameCanvas::step);
}

void GameCanvas::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);
    //    painter.begin(this);

    for (unsigned long long y = 0; y < map.size(); y++) {
        for (unsigned long long x = 0; x < map[y].size(); x++) {
            if (map[y][x] == start) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 groundColor);
                QPoint pos;
                pos.setX(x * brickSize);
                pos.setY(y * brickSize);
                emit robotMovie(rightWaiting);
                emit showRobot(pos, robotSize);
            }
            if (map[y][x] == cheese) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 groundColor);
                QPoint pos;
                pos.setX(x * brickSize);
                pos.setY(y * brickSize);
                emit showCheese(pos, robotSize);
            }
            if (map[y][x] == ground) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 groundColor);
            }
            if (map[y][x] == pit) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 scaledPitMap);
            }
            if (map[y][x] == wall) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 scaledWallMap);
            }
            if (map[y][x] == block) {
                painter.fillRect(x * brickSize, y * brickSize, brickSize, brickSize,
                                 scaledBlockMap);
            }
        }
    }
    //    painter.end();
}

void GameCanvas::setMap(std::vector<std::vector<MapTile>> map) {
    this->map = map;
    update();
}

void GameCanvas::simulate(std::vector<ProgramBlock> program) {
    stop();
    s = new Simulation(map, program);
    connect(s, &Simulation::runningBlock, this, &GameCanvas::emitRunningBlock);
    emit restartGame();
    run(1000);
}

void GameCanvas::step() {
    s->step();
    s->printGameState();
    if(s->getGameState() == lost){
        emit robotMovie(rightWaiting);
        emit gameLost();
        stop();
        return;
    }
    if(s->getGameState() == won){
        emit gameWon();
        stop();
        return;
    }
    emit showRobot(s->getRobotPos() * brickSize, robotSize);
    direction currentDir = s->getRobotDirection();
    if (preDir != currentDir) {
        switch (currentDir) {
        case north:
            emit robotMovie(upWaiting);
            preDir = north;
            break;
        case south:
            emit robotMovie(downWaiting);
            preDir = south;
            break;
        case east:
            emit robotMovie(rightWaiting);
            preDir = east;
            break;
        case west:
            emit robotMovie(leftWaiting);
            preDir = west;
            break;
        }
    }
    setMap(s->getMap());
}

void GameCanvas::run(int interval) { timer->start(interval); }

void GameCanvas::stop() { timer->stop(); }
void GameCanvas::emitRunningBlock(int block){
    emit currentBlock(block);
}
