#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "constants.h"
#include "gamecanvas.h"
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
    explicit GameWindow(std::vector<std::vector<MapTile>> map, int levelNumber, LevelSelectWindow *parent = nullptr);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    int gameAreaX;
    int gameAreaY;

    MachineEditor *editor;
    GameCanvas* canvas;


private slots:
    /**
     * @brief changeMap Change the map in the new level
     */
    void changeMap(std::vector<std::vector<MapTile>>);

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


signals:
    void viewReady();
};

#endif // GAMEWINDOW_H
