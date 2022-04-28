#include "upgrade.h"

namespace crakanoid
{
	Upgrade::Upgrade()
	{
		_upType = -1;
	}
	Upgrade::Upgrade(Vector2 pos)
	{
		_upPos = pos;
		_upType = rand() % UPGRADE_COLOR_SIZE;
		_upOnShip = false;
	}

	Vector2 Upgrade::GetPos() const
	{
		return _upPos;
	}

	void Upgrade::Draw()
	{
		DrawCircle(_upPos.x, _upPos.y, 3.0f, upgradeColors[_upType]);
	}

	bool Upgrade::GetOnShip() const
	{
		return _upOnShip;
	}
	int Upgrade::GetType() const
	{
		return _upType;
	}

	void Upgrade::SetPos(Vector2 pos)
	{
		 _upPos = pos;
	}
	void Upgrade::setOnShip()
	{
		_upOnShip = true;
	}
}
