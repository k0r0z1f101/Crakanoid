#pragma once
#include "raylib.h"
#include "crakanoid.h"

namespace crakanoid
{
	class Level
	{
	private:
		vector<vector<int>> _leBlockPerLine;
		vector<vector<BlockColor>> _leBlockArray;
		int _leStartingBlocks;
		int _leBlocksNeededToWin;
		vector<Block> _leBlocks;

		void InitializeLevel(int lvlNbr);

	public:
		Level(int lvlNbr);
		vector<Block>& GetBlocks();
		int GetNeededToWin();
		~Level();
	};
}
