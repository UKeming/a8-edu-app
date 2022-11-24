#include "levelselectwindow.h"
#include "celebrationwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LevelSelectWindow levelSelectWindow;
    CelebrationWindow celebrationWindow;
    celebrationWindow.show();
    return a.exec();
}
