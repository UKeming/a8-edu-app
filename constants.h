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
    beginBlock = 9,
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
        std::vector<MapTile>{start,  ground, ground,  ground,  cheese, ground}
    },

    // Level 2
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground,  wall,   cheese},
        std::vector<MapTile>{wall,  ground,  ground,  ground },
        std::vector<MapTile>{wall,  wall,  wall,  wall }
    },
    // Level 3
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground, block,  ground,  ground},
        std::vector<MapTile>{wall,  wall,  wall, ground,  wall},
        std::vector<MapTile>{wall,  wall,  wall, cheese,  wall},
        std::vector<MapTile>{wall,  wall,  wall, wall,  wall}
    },

    // Level 4
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground, ground,  ground,  ground,  ground, wall },
        std::vector<MapTile>{wall,  wall,   wall,    wall,    wall,    ground, wall },
        std::vector<MapTile>{wall,  ground, ground,  ground,  wall,    ground, wall },
        std::vector<MapTile>{wall,  ground, wall,    cheese,  wall,    ground, wall },
        std::vector<MapTile>{wall,  ground, wall,    wall,    wall,    ground, wall },
        std::vector<MapTile>{wall,  ground, ground,  ground,  ground,  ground, wall },
        std::vector<MapTile>{wall,  wall,   wall,    wall,    wall,    wall, wall }
    },

    // Level 5
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground, ground,  ground,  ground,  wall },
        std::vector<MapTile>{wall,  wall,   wall,    wall,    ground,  wall },
        std::vector<MapTile>{wall,  ground, ground,  ground,  ground ,  wall },
        std::vector<MapTile>{wall,  ground, wall,    wall,    wall,     wall },
        std::vector<MapTile>{wall,  ground, ground,  ground,  ground,  wall },
        std::vector<MapTile>{wall,  wall,   wall,    wall,    ground,  wall },
        std::vector<MapTile>{wall,  cheese, ground,  ground,  ground ,  wall },
        std::vector<MapTile>{wall,  wall, wall,    wall,    wall,     wall }
    },

    // Level 6
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground,  wall,   wall,    wall,   cheese, wall},
        std::vector<MapTile>{wall,  ground,  wall,   ground,  ground, ground, pit},
        std::vector<MapTile>{wall,  ground,  block, ground,  pit,    wall,   wall},
        std::vector<MapTile>{wall,  pit,     wall,   wall,    wall,   wall,   wall}
    },


    // Level 7
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground, ground, ground, ground, wall },
        std::vector<MapTile>{wall, wall,    wall,   wall,   block, wall },
        std::vector<MapTile>{wall, ground,  ground, ground, ground, wall },
        std::vector<MapTile>{wall, ground,  wall,   wall,   ground, wall },
        std::vector<MapTile>{wall, ground,  ground, ground, ground, cheese },
        std::vector<MapTile>{wall, wall, wall, wall, wall, wall }
    },


    // Level 8
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{wall, wall,  cheese, wall, pit, wall,   wall},
        std::vector<MapTile>{wall, ground,  block, block, block, ground,   wall},
        std::vector<MapTile>{cheese, ground,  ground, ground, ground, pit,   wall},
        std::vector<MapTile>{wall, wall,  wall, wall, wall, wall,   wall}
    },

    // Level 9
    std::vector<std::vector<MapTile>>{
        std::vector<MapTile>{start, ground,  ground, ground, ground, wall,   wall,   wall,   wall,   wall},
        std::vector<MapTile>{wall,  wall,    wall,   wall,   block,  wall,   ground, ground, ground, wall },
        std::vector<MapTile>{wall,  ground,  ground, ground, ground, wall,   ground, wall,   ground, wall },
        std::vector<MapTile>{wall,  ground,  wall,   wall,   ground, wall,   ground, wall,   ground, wall },
        std::vector<MapTile>{wall,  ground,  ground, ground, ground, ground, block, ground, ground, wall },
        std::vector<MapTile>{wall,  wall,    wall,   wall,   wall,   wall,   wall,   wall,   cheese, wall }
    }
};

#endif // CONSTANTS_H
