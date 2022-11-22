#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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

private:
    Ui::GameWindow *ui;
    int gameAreaX;
    int gameAreaY;
    int robotX;
    int robotY;
    QTimer* robotTimer;

private slots:
    /**
     * @brief gameStartTest Test for the elements display
     */
    void gameStartTest();
    void runningTest();

    //void robotMoving();

    /**
     * @brief showIdleRobot
     */
    void showIdleRobot(QPoint);

    void showOneBrick(QPoint);

    void showMovingRobot(QPoint);

    void move();

signals:
    void drawWall(int x, int y);
};

#endif // GAMEWINDOW_H
