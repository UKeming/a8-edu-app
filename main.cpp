#include "levelselectwindow.h"

#include "gamewindow.h"
#include "simulation.h"
#include "constants.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LevelSelectWindow levelSelectWindow;
    levelSelectWindow.show();
    return a.exec();


//    Simulation sim(levels[3], std::vector<ProgramBlock>{begin, whileLoop, conditionNot, conditionFacingCheese, ifStatement, blank, conditionFacingPit, turnRight, endIf, moveForward, endWhile,  moveForward, eatCheese});
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();
//    sim.step();
//    sim.printGameState();

    return 0;
}
