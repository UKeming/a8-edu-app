#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <vector>

enum MapTile {
    start = 0,
    floor = 1,
    wall = 2,
    cheese = 3,
    block = 4,
    pit = 5,
};

enum ProgramBlock {
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
};

// TODO We'll remove this and add levels to the model? Just adding it so we have some sample data to play with.
const std::vector<std::vector<MapTile>> levels[] = {
    // Level 1
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start,  floor,  floor,  cheese}
    },

    // Level 2
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, floor,  wall,   cheese},
        std::vector<MapTile>{wall,  floor,  floor,  floor }
    }
};

#endif // CONSTANTS_H
