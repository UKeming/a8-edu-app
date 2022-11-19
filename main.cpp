#include "gamewindow.h"
#include "simulation.h"
#include "constants.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameModel model;

//    GameWindow w(model);
//    w.show();
//    return a.exec();


    Simulation sim(levels[1], std::vector<ProgramBlock>{moveForward, turnRight, moveForward, turnLeft, moveForward, moveForward, turnLeft, moveForward, eatCheese, turnLeft, turnLeft, moveForward});
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();
    sim.step();
    sim.printGameState();

    return 0;
}
