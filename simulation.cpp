#include "simulation.h"
#include <QDebug>
#include <vector>
#include <QPoint>
#include <string>
#include "constants.h"
Simulation::Simulation(std::vector<std::vector<MapTile>> newMap, std::vector<ProgramBlock> newProgram)
    : map(newMap), gameState(notEnded), robotDirection(east), program(newProgram)
{
    height = map.size();
    width = map[0].size();
    for(unsigned long long y = 0; y < map.size(); y++){
        for(unsigned long long x = 0; x < map[y].size(); x++){
            if(map[y][x] == start){
                robotPos = QPoint(x, y);
                map[y][x] = tile;
            }
            if(map[y][x] == cheese){
                cheesePos = QPoint(x, y);
                map[y][x] = tile;
            }
        }
    }

    tickCount = 0;
    currentBlock = 0;
}

void Simulation::step(){
    if(gameState == lost)
        return;
    if(currentBlock == (int)program.size()){
        currentBlock = 0;
    }
    tickCount++;
    switch(program[currentBlock]){
        case moveForward:{
            currentBlock++;
            QPoint newPos(robotPos);
            QPoint newBoxPos(robotPos);
            //qDebug() << newPos;
            switch(robotDirection){
                case north:
                    newPos.setY(newPos.y() - 1);
                    newBoxPos.setY(newBoxPos.y() - 2);
                    break;
                case south:
                    newPos.setY(newPos.y() + 1);
                    newBoxPos.setY(newBoxPos.y() + 2);
                    break;
                case east:
                    newPos.setX(newPos.x() + 1);
                    newBoxPos.setX(newBoxPos.x() + 2);
                    break;
                case west:
                    newPos.setX(newPos.x() - 1);
                    newBoxPos.setX(newBoxPos.x() - 2);
                    break;
            }
            //qDebug() << newPos;
            //qDebug() << checkInBounds(newPos);
            if(!checkInBounds(newPos)){
                return;
            }
            //qDebug() << "should move";
            //qDebug() << newPos;

            switch(map[newPos.y()][newPos.x()]){
                case tile:
                    qDebug() << "moving";
                    robotPos = newPos;
                    break;
                case pit:
                    setLost();
                    break;
                case block:
                    if(!checkInBounds(newBoxPos)){
                        return;
                    }
                    switch(map[newBoxPos.y()][newBoxPos.x()]){
                        case tile:
                            robotPos = newPos;
                            map[newBoxPos.y()][newBoxPos.x()] = block;
                            map[newPos.y()][newPos.x()] = tile;
                            break;
                        case pit:
                            robotPos = newPos;
                            map[newPos.y()][newPos.x()] = tile;
                            break;
                        case block:
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        case turnLeft:
            currentBlock++;
            switch(robotDirection){
                case north:
                    robotDirection = west;
                    break;
                case south:
                    robotDirection = east;
                    break;
                case east:
                    robotDirection = north;
                    break;
                case west:
                    robotDirection = south;
                    break;
            }
            break;
        case turnRight:
            currentBlock++;
            switch(robotDirection){
                case north:
                    robotDirection = east;
                    break;
                case south:
                    robotDirection = west;
                    break;
                case east:
                    robotDirection = south;
                    break;
                case west:
                    robotDirection = north;
                    break;
            }
            break;
        case eatCheese:
            currentBlock++;
            if(cheesePos == robotPos){
                cheesePos = QPoint(-1, -1);
                gameState = won;
            }
            break;
        case ifStatement:
            break;
        case whileLoop:
            break;
        case endWhile:
            break;
        case conditionNot:
        case conditionFacingBlock:
        case conditionFacingWall:
        case conditionFacingPit:
        case endIf:
            qDebug() << "Ooops should not be here!!!!!!!!";
            break;
    }
}

void Simulation::setLost(){
    gameState = lost;
    robotPos = QPoint(-1, -1);
}

bool Simulation::checkInBounds(QPoint point){
    return point.x() != -1 && point.y() != -1 &&
        point.x() != width && point.y() != height;
}

void Simulation::printGameState(){
    switch(gameState){
        case lost:
            qDebug() << "Gamestate: lost";
            break;
        case won:
            qDebug() << "Gamestate: won";
            break;
        case notEnded:
            qDebug() << "Gamestate: notEnded";
            break;
    }
    std::string mapString = "";
    for(unsigned long long y = 0; y < map.size(); y++){
        mapString.append("\n");
        for(unsigned long long x = 0; x < map[y].size(); x++){
            if(robotPos == QPoint(x, y)){
                switch(robotDirection){
                    case north:
                        mapString.append("^");
                        continue;
                        break;
                    case south:
                        mapString.append("v");
                        continue;
                        break;
                    case east:
                        mapString.append(">");
                        continue;
                        break;
                    case west:
                        mapString.append("<");
                        continue;
                        break;
                }
            }
            if(cheesePos == QPoint(x, y)){
                mapString.append("C");
                continue;
            }
            switch(map[y][x]){
                case tile:
                    mapString.append("*");
                    break;
                case pit:
                    mapString.append("0");
                    break;
                case block:
                    mapString.append("@");
                    break;
                case wall:
                    mapString.append("#");
                    break;
                default:
                    qDebug() << "Ooops should not be here #2!!!!!!!!";
                    break;
            }
        }
    }
    qDebug() << mapString.c_str();
}

