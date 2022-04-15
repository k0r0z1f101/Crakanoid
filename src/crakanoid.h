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
	//Player Ship Upgrades
	class Upgrade
	{

	};

	class Consumable
	{

	};

	//Player Ship Declarations
	class Spaceship
	{
		static const float ssStartX; //starting horizontal position
		static const float ssHeight; //height of the ship
		Vector2 ssPos; //position of the spaceship (h pos, v pos)
		int ssSpeed; //speed in pixel of lateral movement
		int ssWidth; //horizontal size
		int ssBall; //lives of the player, number of balls left
		vector<Upgrade> ssUpgrades; //current active upgrades
		vector<Consumable> ssConsumables; //inventory of one-time use items available

	public:
		Spaceship();
		void DrawShip();
		void MoveShip();
		Vector2& GetShipPosition();
		int& GetShipWidth();
		float GetShipHeight();
		int GetBallsLeft();
		int LoseBall(int ball);
		~Spaceship();
	};


	//Block Declarations
	enum BlockColor
	{
		B_RED = 0,
		B_GREEN,
		B_BLUE
	};
	const int BLOCK_COLOR_SIZE = 3;
	const array<Color, BLOCK_COLOR_SIZE> blockColors = { RED, GREEN, BLUE };
	const Vector2 blSize = { 30.0f, 15.0f }; //h size, v size

	class Block
	{
		Vector2 blPos; //h pos, v pos
		int blLifePoint; //block life point before being destroyed
		Color blColor; //block color

	public:
		Block();
		Block(float x, float y, BlockColor col);
		Vector2 getPosition();
		Color getColor();
		Vector2 getSize();
		int getLifePoint();
		int loseLifePoint(int life);
		void setPosition(float x, float y);
		void setColor(Color color);
		~Block();
	};

	//Ball declarations
	class Ball
	{
		static const int baRadius; //radius of the ball in pixels
		static const float baLineSight; //length in pixels of the line that points to the mouse
		Vector2 baPos; //position of the ball (h pos, v pos)
		float baVelocity; //speed of the ball
		float baAngle; //angle of the ball
		int baWeight; //weight of the ball
		float baLifeTime; //life of the ball in seconds
		bool baSticky; //if true the ball will stick to surface other than blocks (except sticky blocks)

	public:
		Ball();
		Ball(Spaceship& ship, Vector2 pos, float velocity = 5.0f, float angle = 0.0f, int weight = 1, float age = 0.0f);
		void MoveBall(Spaceship& ship);
		void DrawBall();
		void getAngleToMousePos(Vector2& toZero, float& mag); //set baAngle at angle in degree to mouse cursor counterclokwise, starting from east
		float getRadianFromDegree(); //return angle in radian from a ball rotation angle in degree
		float getAngle();
		Vector2 getPosition();
		bool getSticky();
		float getRadius();
		void setPosition(float x, float y);
		void setAngle(float angle);
		void adjustSpeed(float speed);
		void setSticky(bool);
		~Ball();

	};
}
