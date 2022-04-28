#pragma once
#include "raylib.h"
#include <array>

using std::array;

namespace crakanoid
{
	enum UpgradeColor
	{
		NONE = -1,
		U_YELLOW = 0, 	//pass through blocks, no rebound
		U_RED,			//multiball
		U_BLUE,			//one life
		U_GREEN,		//sticky ball
		U_WHITE			//larger ship
	};
	const int UPGRADE_COLOR_SIZE = 5;
	const array<Color, UPGRADE_COLOR_SIZE> upgradeColors = { YELLOW, RED, BLUE, GREEN, WHITE };

	class Upgrade
	{
	private:
		Vector2 _upPos; //position of the upgrade, h pos, v pos
		int _upType; 	//type of the upgrade, randomly instanciate, associated to the color
		bool _upOnShip; //true if the upgrade has been caught by the ship
	public:
		Upgrade();
		Upgrade(Vector2 pos);

		void Draw();

		Vector2 GetPos() const;
		bool GetOnShip() const;
		int GetType() const;

		void SetPos(Vector2 pos);
		void setOnShip();
	};
}
