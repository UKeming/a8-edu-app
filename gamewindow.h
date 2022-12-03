#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "constants.h"
#include "gamemodel.h"
#include "machineeditor.h"
#include "simulation.h"

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(GameModel& model, QWidget *parent = nullptr);
    ~GameWindow();

    /**
     * @brief changeMap Change the map in the new level
     */
    void changeMap(std::vector<std::vector<MapTile>>, int);

private:
    Ui::GameWindow *ui;
    int gameAreaX;
    int gameAreaY;
    int robotX;
    int robotY;
    int robotSize;
    bool facingRight;
    MachineEditor *editor;
    QTimer* robotTimer;
    std::vector<std::vector<MapTile>> currentMap;
    std::vector<std::vector<MapTile>> emptyMap;
    std::vector<ProgramBlock> emptyProgram;
    // Simulation simu = Simulation(emptyMap, emptyProgram);

private slots:
    /**
     * @brief gameStartTest Test for the elements display
     */
    void gameStartTest();

    /**
     * @brief runningTest
     */
    void runningTest();

    /**
     * @brief refreshingRobot Get the robot position, if robot position changed, set the position again
     */
    void refreshRobot();

    /**
     * @brief showIdleRobot Show the robot is wait commands
     */
    void showIdleRobot(QPoint);

    /**
     * @brief showCheese Show the cheese
     */
    void showCheese(QPoint);

    void showProgram();


    /**
     * @brief facingRightWaiting
     */
    void facingRightWaiting();

    void facingLeftWaiting();

    void facingRightRunning();

    void facingLeftRunning();

    /**
     * @brief showEducationalMessage Shows an educational message to the user.
     */
    void showEducationalMessage(QString);

    /**
     * @brief runTheProgram When the user press get program button on the editor window,
     *                      get the program from graph, and set it
     */
    void runTheProgram(std::vector<ProgramBlock>);

signals:
    void drawWall(int x, int y);
    void viewReady();
};

#endif // GAMEWINDOW_H
