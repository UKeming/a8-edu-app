#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <vector>

enum MapTile {
    start = 0,
    ground = 1,
    wall = 2,
    cheese = 3,
    block = 4,
    pit = 5,
};

enum ProgramBlock {
    begin = 9,
    moveForward = 1,
    turnLeft = 2,
    turnRight = 3,
    ifStatement = 4,
    endIf = 5,
    whileLoop = 6,
    endWhile = 7,
    eatCheese = 8,
    conditionNot = 0,
    conditionFacingBlock = -1,
    conditionFacingWall = -2,
    conditionFacingPit = -3,
    conditionFacingCheese = -4,

    blank = 10
};

enum gameState {
    notEnded = 0,
    won = 1,
    lost = 2,
};

enum direction {
    north = 0,
    south = 1,
    east = 2,
    west = 3
};

// TODO We'll remove this and add levels to the model? Just adding it so we have some sample data to play with.
const std::vector<std::vector<MapTile>> levels[] = {
    // Level 1
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start,  ground,  ground,  cheese}
    },

    // Level 2
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground,  wall,   cheese},
        std::vector<MapTile>{wall,  ground,  ground,  ground }
    },

    // Level 3
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground, wall,  wall,  cheese,  wall },
        std::vector<MapTile>{wall,  ground,  block, ground,  ground ,  pit }
    }
};

#endif // CONSTANTS_H
