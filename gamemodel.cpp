#include "gamemodel.h"
#include "constants.h"

GameModel::GameModel(int level, QObject *parent)
    : QObject{parent}
    , currentLevel(level)
{

}

void GameModel::loadLevel() {
    emit showEducationalMessage(educationalMessages[currentLevel]);
}


