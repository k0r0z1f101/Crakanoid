#pragma once
#include "raylib.h"
#include <array>

using std::array;

namespace crakanoid
{
	//red: 1hp, green: 2, blue: 3, silver/lightgray: invicible
	enum BlockColor	{ B_NONE = -1, B_RED = 0, B_GREEN, B_BLUE, B_SILVER	};
	const int BLOCK_COLOR_SIZE = 4;
	const array<Color, BLOCK_COLOR_SIZE> BLOCK_COLORS = { RED, GREEN, BLUE, LIGHTGRAY };
	const Vector2 BLOCK_SIZE = { 30.0f, 15.0f }; //h size, v size

	class Block
	{
	private:
		Vector2 _blPos; 	//h pos, v pos
		int _blLifePoint;	//block life point before being destroyed
		Color _blColor; 	//block color

	public:
		Block(Vector2 pos, BlockColor col);

		void Draw();

		Vector2 GetPosition();
		Color GetColor();
		Vector2 GetSize();
		int GetLifePoint();
		int LoseLifePoint(int life);
		void SetPosition(Vector2 pos);
		void SetColor(Color color);
	};
}
