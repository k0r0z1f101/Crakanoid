#pragma once

#include <string>
#include <iostream>
#include <random>
#include <array>

#include "sound.h"
#include "block.h"
#include "level.h"
#include "spaceship.h"
#include "upgrade.h"
#include "ball.h"

using std::cout;   using std::cin;
using std::endl;   using std::string;
using std::vector; using std::array;
using namespace crakanoid;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const float PLAYSCREEN_MARGIN = 20.0f;

const int NUMBER_OF_LEVEL = 4;
const array<vector<vector<int>>, NUMBER_OF_LEVEL> LEVELS_BLOCKSPERLINE = {
		vector<vector<int>>{
			{ 30 },
			{ 30 },
			{ 30 },
			{ 30 },
			{ 30 },
			{ 1, 3, 2, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 3, 2, 1 },
			{ 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 2, 2, 1, 3, 2, 2, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
			{ 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 1 }
		},
		vector<vector<int>>{
			{ 30 },
			{ 30 },
			{ 30 },
			{ 30 }
		},
		vector<vector<int>>{
			{ 30 },
			{ 30 },
			{ 30 },
			{ 6, 4, 3, 4, 3, 4 },
			{ 6, 4, 3, 4, 3, 4 },
			{ 6, 4, 3, 4, 3, 4 },
			{ 6, 4, 3, 4, 3, 4 },
			{ 30 },
			{ 30 },
			{ 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
		},
		vector<vector<int>>{
			{ 13, 1 }
		}
};
const array<vector<vector<BlockColor>>, NUMBER_OF_LEVEL> LEVELS_BLOCKARRAY = {
		vector<vector<BlockColor>>{
			{ B_NONE },
			{ B_NONE },
			{ B_NONE },
			{ B_NONE },
			{ B_NONE },
			{ B_NONE, B_RED, B_BLUE, B_NONE, B_GREEN, B_RED, B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED, B_GREEN, B_BLUE, B_RED, B_NONE },
			{ B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_GREEN, B_NONE, B_GREEN, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_NONE, B_RED, B_GREEN, B_NONE, B_GREEN, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED },
			{ B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_GREEN, B_RED, B_NONE, B_BLUE, B_NONE, B_RED, B_GREEN, B_NONE, B_GREEN, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED },
			{ B_NONE, B_RED, B_BLUE, B_NONE, B_BLUE, B_GREEN, B_NONE, B_GREEN, B_RED, B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED, B_GREEN, B_BLUE, B_RED, B_NONE }
		},
		vector<vector<BlockColor>>{
			{ B_NONE },
			{ B_BLUE },
			{ B_GREEN },
			{ B_RED }
		},
		vector<vector<BlockColor>>{
			{ B_NONE },
			{ B_NONE },
			{ B_NONE },
			{ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED },
			{ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED },
			{ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED },
			{ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED },
			{ B_NONE },
			{ B_NONE },
			{ B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER}
		},
		vector<vector<BlockColor>>{
			{ B_NONE, B_RED }
		}
};

namespace crakanoid
{

}
