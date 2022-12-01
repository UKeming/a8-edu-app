#include "gamecanvas.h"
#include "constants.h"
#include <QMovie>
#include <QPainter>

GameCanvas::GameCanvas(QWidget* parent, std::vector<std::vector<MapTile>> map)
    : QWidget{ parent }
    , map(map)
{
    this->setMinimumSize(QSize(1000,2000));
}

void GameCanvas::paintEvent(QPaintEvent * /* event */)
{
    int brickSize = 100;

    QPainter painter(this);
    painter.begin(this);

    QPixmap wallMap(":/elements/brickwall.jpg");
    QPixmap scaledWallMap = wallMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap blockMap(":/elements/block.png");
    QPixmap scaledBlockMap = blockMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QPixmap pitMap(":/elements/pit.png");
    QPixmap scaledPitMap = pitMap.scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    QColor groundColor = QColor::fromRgb(222,184,135);

    for(unsigned long long y = 0; y < map.size(); y++){
            for(unsigned long long x = 0; x < map[y].size(); x++){
                if(map[y][x] == start){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, groundColor);
                    QPoint pos;
                    pos.setX(x * brickSize);
                    pos.setY(y * brickSize);
                    emit showRobot(pos);
                }
                if(map[y][x] == cheese){
                    painter.fillRect(x*brickSize, y*brickSize, brickSize, brickSize, groundColor);
                    QPoint pos;
                    pos.setX(x * brickSize);
                    pos.setY(y * brickSize);
                    emit showCheese(pos);
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
