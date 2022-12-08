#ifndef CELEBRATIONWINDOW_H
#define CELEBRATIONWINDOW_H

#include <QMainWindow>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QPainter>
#include <QPaintDevice>

const float WORLD_WIDTH = 10.0f;
const float WORLD_HEIGHT = 7.0f;

const float WALL_THICKNESS = 0.001f;

const int NUM_CONFETTI = 300;
const float CONFETTI_RADIUS = 0.06f;

namespace Ui {
class CelebrationWindow;
}

class CelebrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CelebrationWindow(int nextLevelIndex, QWidget *parent = nullptr);
    ~CelebrationWindow();

public slots:
    void updatePhysics();

private:
    Ui::CelebrationWindow *ui;
    b2World physicsWorld;
    std::array<b2Body* , NUM_CONFETTI> confettiBodies;
    QTimer timer;
    QPainter painter;
    int nextLevelIndex;
private slots:
    void showMainMenu();
    void nextLevel();

signals:

};

class CelebrationWidget : public QWidget {
    Q_OBJECT

public:
    explicit CelebrationWidget(QWidget *parent = nullptr);

    void setBodies(std::array<b2Body*, NUM_CONFETTI>* bodiesReference);

private:
    std::array<b2Body*, NUM_CONFETTI>* confettiBodiesReference;
    std::array<QColor, NUM_CONFETTI> confettiColors;

    void paintEvent(QPaintEvent *);
};

#endif // CELEBRATIONWINDOW_H
