#include "block.h"

namespace crakanoid
{
	Block::Block(Vector2 pos, BlockColor col)
			: _blPos(pos) 					//block position (h pos, v pos)
			, _blColor(BLOCK_COLORS[col]) 	//block color
			, _blLifePoint(col + 1) 		//block life point before being destroyed
	{}

	void Block::Draw()
	{
		if(_blLifePoint > 0)
		{
			Rectangle rec;
			rec.height = BLOCK_SIZE.y;
			rec.width = BLOCK_SIZE.x;
			rec.x = _blPos.x;
			rec.y = _blPos.y;
			Vector2 ori = { 0.0f, 0.0f };
			DrawRectanglePro(rec, ori, 0.0f, _blColor);
		}
	}

	Vector2 Block::GetPosition()
	{
		return _blPos;
	}

	Color Block::GetColor()
	{
		return _blColor;
	}

	Vector2 Block::GetSize()
	{
		return BLOCK_SIZE;
	}

	int Block::GetLifePoint()
	{
		return _blLifePoint;
	}

	int Block::LoseLifePoint(int life)
	{
		if(_blLifePoint < 4)
		{
			_blLifePoint -= life;
			SetColor(BLOCK_COLORS[_blLifePoint-1]);
		}

		return _blLifePoint;
	}

	void Block::SetPosition(Vector2 pos)
	{
		_blPos = pos;
	}

	void Block::SetColor(Color color)
	{
		_blColor = color;
	}
}
