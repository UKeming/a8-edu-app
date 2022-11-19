#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "constants.h"
#include <QPoint>

class Simulation
{
private:
    std::vector<std::vector<MapTile>> map;
    gameState gameState;
    int width;
    int height;
    QPoint cheesePos;

    QPoint robotPos;
    direction robotDirection;

    std::vector<ProgramBlock> program;
    int tickCount;
    int currentBlock;
public:
    Simulation(std::vector<std::vector<MapTile>> newMap, std::vector<ProgramBlock> newProgram);
    void step();
    QPoint getRobotPos();
    void printGameState();
private:
    void setLost();
    bool checkInBounds(QPoint);

};

#endif // SIMULATION_H
