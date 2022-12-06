#include "gamecanvas.h"
#include "constants.h"
#include <QMovie>
#include <QPainter>

GameCanvas::GameCanvas(QWidget* parent, std::vector<std::vector<MapTile>> map)
    : QWidget{ parent }
    , map(map)
{
    this->setMinimumSize(QSize(1000,2000));

    brickSize = 100;

    robotSize = 90;

    QPixmap wallMap(":/elements/brickwall.jpg");
    scaledWallMap = wallMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap blockMap(":/elements/block.png");
    scaledBlockMap = blockMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap pitMap(":/elements/pit.png");
    scaledPitMap = pitMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    rightWaiting = new QMovie(":/elements/robot-idle-right.gif");
    rightWaiting->setScaledSize(QSize(robotSize, robotSize));

    leftWaiting = new QMovie(":/elements/robot-idle-left.gif");
    leftWaiting->setScaledSize(QSize(robotSize, robotSize));

    rightRunning = new QMovie(":/elements/robot-run-right.gif");
    rightRunning->setScaledSize(QSize(robotSize, robotSize));

    leftRunning = new QMovie(":/elements/robot-run-right.gif");
    leftRunning->setScaledSize(QSize(robotSize, robotSize));

    QPixmap cheeseMap(":/elements/cheese.png");
    scaledCheeseMap = cheeseMap.scaled(robotSize, robotSize, Qt::KeepAspectRatio);

    groundColor = QColor::fromRgb(222,184,135);
}

void GameCanvas::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.begin(this);

    for(unsigned long long y = 0; y < map.size(); y++){
            for(unsigned long long x = 0; x < map[y].size(); x++){
                if(map[y][x] == start){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, groundColor);
                    QPoint pos;
                    pos.setX(x * brickSize);
                    pos.setY(y * brickSize);
                    emit robotMovie(rightWaiting);
                    emit showRobot(pos, robotSize);
                }
                if(map[y][x] == cheese){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, groundColor);
                    QPoint pos;
                    pos.setX(x * brickSize);
                    pos.setY(y * brickSize);
                    emit showCheese(pos, robotSize);
                }
                if(map[y][x] == ground){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, groundColor);
                }
                if(map[y][x] == pit){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, scaledPitMap);
                }
                if(map[y][x] == wall){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, scaledWallMap);
                }
                if(map[y][x] == block){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, scaledBlockMap);
                }
            }
        }
    painter.end();
}
