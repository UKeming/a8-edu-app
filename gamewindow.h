#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "constants.h"
#include "gamemodel.h"

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
    void changeMap(std::vector<std::vector<MapTile>>);

private:
    Ui::GameWindow *ui;
    int gameAreaX;
    int gameAreaY;
    int robotX;
    int robotY;
    int robotSize;
    bool facingRight;
    QTimer* robotTimer;

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

    /**
     * @brief facingRightWaiting
     */
    void facingRightWaiting();

    void facingLeftWaiting();

    void facingRightRunning();

    void facingLeftRunning();

<<<<<<< HEAD
=======
    /**
     * @brief changeMap Change the map in the new level
     */
    void changeMap(std::vector<std::vector<MapTile>>);

    /**
     * @brief showEducationalMessage Shows an educational message to the user.
     */
    void showEducationalMessage(QString);

>>>>>>> c48f7bb (Add educational dialog boxes for levels)
signals:
    void drawWall(int x, int y);
    void viewReady();
};

#endif // GAMEWINDOW_H
