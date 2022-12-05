#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "constants.h"
#include <QPoint>

class Simulation
{
private:
    gameState gameState;
    int width;
    int height;
    QPoint cheesePos;

    QPoint robotPos;
    direction robotDirection;

    std::vector<ProgramBlock> program;
    int tickCount;
    int currentBlock;
    int level;
    std::map<int, int> ifWhileToEnd;
    std::map<int, int> endToIfWhile;
public:
    Simulation(std::vector<std::vector<MapTile>> newMap, std::vector<ProgramBlock> newProgram);
    void step();
    void run();
    std::vector<std::vector<MapTile>> map;

    QPoint getRobotPos();
    QPoint getCheesePos();
    int getCurrentBlock();
    void printGameState();
private:
    void setLost();
    bool checkInBounds(QPoint);
    bool checkCondition(bool, ProgramBlock);
    QPoint getFacingPoint(int offset = 1);

signals:
    void mapData(std::vector<std::vector<MapTile>>);

};

#endif // SIMULATION_H
