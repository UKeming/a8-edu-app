#include "levelselectwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    LevelSelectWindow levelSelectWindow;
    levelSelectWindow.show();
    return a.exec();

    return 0;
}
