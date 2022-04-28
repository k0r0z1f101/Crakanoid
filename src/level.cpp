#include "level.h"

namespace crakanoid
{
	void Level::InitializeLevel(int lvlNbr)
	{
		for(size_t i = {}; i < LEVELS_BLOCKSPERLINE[lvlNbr].size(); ++i)
		{
			int blockInLine = {};
			for(size_t j = {}; j < LEVELS_BLOCKSPERLINE[lvlNbr][i].size(); ++j)
			{
				for(int k = {}; k < LEVELS_BLOCKSPERLINE[lvlNbr][i][j]; ++k)
				{
					float newX = PLAYSCREEN_MARGIN + (BLOCK_SIZE.x * blockInLine) + (2.0f * blockInLine);
					float newY = PLAYSCREEN_MARGIN + (BLOCK_SIZE.y * i) + (2.0f * i);
					BlockColor newColor = LEVELS_BLOCKARRAY[lvlNbr][i][j];
					_leBlocks.push_back(Block({newX, newY}, newColor));
					_leBlocksNeededToWin += int(newColor) != -1 && int(newColor) < 3 ? 1 : 0;
					++blockInLine;
				}
			}
		}
	}

	Level::Level(int lvlNbr)
	{
		lvlNbr = lvlNbr == 4 ? 0 : lvlNbr;
		_leBlockPerLine = LEVELS_BLOCKSPERLINE[lvlNbr];
		_leBlockArray = LEVELS_BLOCKARRAY[lvlNbr];
		_leBlocksNeededToWin = {};
		_leBlocks = {};
		InitializeLevel(lvlNbr);
	}

	vector<Block>& Level::GetBlocks()
	{
		return _leBlocks;
	}

	int Level::GetNeededToWin()
	{
		return _leBlocksNeededToWin;
	}

	Level::~Level()
	{

	}
}
