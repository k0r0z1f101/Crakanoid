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
		vector<int> ssPos; //position of the spaceship (h pos, v pos)
		int ssSpeed; //speed in pixel of lateral movement
		int ssWidth; //horizontal size
		vector<Upgrade> ssUpgrades; //current active upgrades
		vector<Consumable> ssConsumables; //inventory of one-time use items available

	public:
		Spaceship();
		void DrawShip();
		void MoveShip();
		vector<int>& GetShipPosition();
		int& GetShipWidth();
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
		static const Vector2 blSize; //h size, v size
		vector<int> blPos; //h pos, v pos
		float blLifePoint; //bloc life point before being destroyed
		Color blColor; //bloc color

	public:
		Bloc();
		Bloc(int x, int y, BlocColor col);
		~Bloc();
	};

	//Ball declarations
	class Ball
	{
		static const int baRadius; //radius of the ball in pixels
		vector<int> baPos; //position of the ball (h pos, v pos)
		int baVelocity; //speed of the ball
		float baAngle; //angle of the ball
		int baWeight; //weight of the ball
		float baLifeTime; //life of the ball in seconds
		bool baSticky; //if true the ball will stick to surface other than blocks (except sticky blocks)

	public:
		Ball();
		Ball(Spaceship& paddle, vector<int> pos, int velocity = 0, float angle = 0.0f, int weight = 1, float age = 0.0f);
		void MoveBall(Spaceship& paddle);
		void DrawBall();
		~Ball();

	};
}
