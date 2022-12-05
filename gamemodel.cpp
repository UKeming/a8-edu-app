#include "gamemodel.h"
#include "constants.h"

GameModel::GameModel(int level, QObject *parent)
    : QObject{parent}
    , currentLevel(level)
{

}

void GameModel::loadLevel() {
    emit mapLoaded(levels[currentLevel], currentLevel);
    emit showEducationalMessage(educationalMessages[currentLevel]);
}

void GameModel::simulate(std::vector<ProgramBlock> program){

}
