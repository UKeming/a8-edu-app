#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "constants.h"

class GameModel : public QObject
{
    Q_OBJECT
    int currentLevel;

public:
    explicit GameModel(int level, QObject *parent = nullptr);

public slots:
    /**
     * @brief loadLevel Loads the current level and begins sending data to the view
     */
    void loadLevel();

signals:
    /**
     * @brief showEducationalMessage Tells listeners that an educational message should be shown to the user
     */
    void showEducationalMessage(QString);
    void mapLoaded(const std::vector<std::vector<MapTile>>& map, int levelNumber);
};

#endif // GAMEMODEL_H
