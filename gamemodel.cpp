#include "gamemodel.h"
#include "constants.h"

GameModel::GameModel(int level, QObject *parent)
    : QObject{parent}
    , currentLevel(level)
{

}

void GameModel::loadLevel() {
    emit mapLoaded(levels[currentLevel]);
    emit showEducationalMessage(educationalMessages[currentLevel]);
}
