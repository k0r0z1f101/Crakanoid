#pragma once
#include <string>
#include <iostream>
#include <random>
#include <array>

using std::cout;   using std::cin;
using std::endl;   using std::string;
using std::vector; using std::array;

const int screenWidth = 1600;
const int screenHeight = 900;

namespace crakanoid
{
	//Player Paddle Upgrades
	class Upgrade
	{

	};

	class Consumable
	{

	};

	//Player Paddle Declarations
	class Spaceship
	{
		static const int ssStartX; //starting horizontal position
		static const int ssHeight; //height of the ship
		int ssPosX; //horizontal position
		int ssPosY; //vertical position
		int ssWidth; //horizontal size
		vector<Upgrade> ssUpgrades; //current active upgrades
		vector<Consumable> ssConsumables; //inventory of one-time use items available

	public:
		Spaceship();
		void DrawShip();
		void moveShip();
		~Spaceship();
	};


	//Bloc Declarations
	enum BlocColor
	{
		B_RED = 0,
		B_GREEN,
		B_BLUE
	};
	const int BLOC_COLOR_SIZE = 3;
	const array<Color, BLOC_COLOR_SIZE> blocColors = { RED, GREEN, BLUE };

	class Bloc
	{
		static const Vector2 bSize; //h size, v size
		Vector2 bPos; //h pos, v pos
		float bLifePoint; //bloc life point before being destroyed
		Color bColor; //bloc color

	public:
		Bloc();
		Bloc(float x, float y, BlocColor col);
		~Bloc();
	};
}
