#include "raylib.h"
#include "crakanoid.h"

namespace crakanoid
{
	const int Spaceship::ssStartX = screenWidth/2;
	const int Spaceship::ssHeight = 20;

	Spaceship::Spaceship()
	{
		ssWidth = 50; //starting horizontal size
		ssPosX = ssStartX - (ssWidth / 2); //horizontal position from the bottom
		ssPosY = 40; //starting vertical position from the bottom
		ssUpgrades = {}; //initializing upgrades list
		ssConsumables = {}; // initializing consumables inventory

	}
	void Spaceship::DrawShip()
	{
		DrawRectangle(ssPosX, screenHeight - ssPosY, ssWidth, ssHeight, RED);
	}
	void Spaceship::moveShip()
	{
		if(IsKeyDown(KEY_A))
			--ssPosX;

		if(IsKeyDown(KEY_D))
			++ssPosX;
	}
	Spaceship::~Spaceship()
	{

	}

	//Bloc definitions
	const Vector2 Bloc::bSize = { 10.0f, 5.0f }; //h size, v size
	Bloc::Bloc()
	{

	}
	Bloc::Bloc(float x, float y, BlocColor col)
	{
		bPos.x = x; //h pos
		bPos.y = y; //v pos
		bColor = blocColors[col]; //bloc color
		bLifePoint = col; //bloc life point before being destroyed
	}
	Bloc::~Bloc()
	{

	}

}
