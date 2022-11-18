#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameModel model;

    GameWindow w(model);
    w.show();
    return a.exec();
}
