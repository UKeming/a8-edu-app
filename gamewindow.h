#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "constants.h"
#include "gamemodel.h"
#include "levelselectwindow.h"
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
    explicit GameWindow(GameModel& model, LevelSelectWindow *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    int gameAreaX;
    int gameAreaY;

    MachineEditor *editor;


private slots:
    /**
     * @brief changeMap Change the map in the new level
     */
    void changeMap(std::vector<std::vector<MapTile>>);

    /**
     * @brief changeLevel
     */
    void changeLevel(int);

    /**
     * @brief gameStartTest Test for the elements display
     */
    void gameStartTest();

    /**
     * @brief runningTest
     */
    void runningTest();

    /**
     * @brief showIdleRobot Show the robot is wait commands
     */
    void showIdleRobot(QPoint, int size);

    /**
     * @brief showCheese Show the cheese
     */
    void showCheese(QPoint, int size);

    void showProgram();

    /**
     * @brief showRobotMovie change the robot movie
     */
    void showRobotMovie(QMovie*);

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
