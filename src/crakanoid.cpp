#include "raylib.h"
#include "crakanoid.h"

namespace crakanoid
{
	const int Spaceship::ssStartX = screenWidth/2;
	const int Spaceship::ssHeight = 20;

	Spaceship::Spaceship()
	{
		ssWidth = 50; //starting horizontal size
		ssPos = { ssStartX - (ssWidth / 2), screenHeight - 40 }; //position of spaceship (h pos, v pos)
		ssSpeed = 5; //speed in pixel of lateral movement
		ssUpgrades = {}; //initializing upgrades list
		ssConsumables = {}; // initializing consumables inventory

	}
	void Spaceship::DrawShip()
	{
		Rectangle rec;
		rec.height = ssHeight;
		rec.width = ssWidth;
		rec.x = ssPos[0];
		rec.y = ssPos[1];
		Vector2 ori = { 0.0f, 0.0f };
		DrawRectanglePro(rec, ori, 0.0f, RED);
	}
	void Spaceship::MoveShip()
	{
		if(IsKeyDown(KEY_A))
			ssPos[0] -= ssSpeed;

		if(IsKeyDown(KEY_D))
			ssPos[0] += ssSpeed;
	}
	vector<int>& Spaceship::GetShipPosition()
	{
		return ssPos;
	}
	int& Spaceship::GetShipWidth()
	{
		return ssWidth;
	}
	Spaceship::~Spaceship()
	{

	}

	//Bloc definitions
	const Vector2 Bloc::blSize = { 10.0f, 5.0f }; //h size, v size
	Bloc::Bloc()
	{
		blLifePoint = 1;
	}

	Bloc::Bloc(int x, int y, BlocColor col)
	{
		vector<int> blPos = { x, y }; //bloc position (h pos, v pos)
		blColor = blocColors[col]; //bloc color
		blLifePoint = col; //bloc life point before being destroyed
	}
	Bloc::~Bloc()
	{

	}

	//Ball definitions
	const int Ball::baRadius = 6; //radius of the ball in pixels

	Ball::Ball()
	{
		baPos = { screenWidth / 2, screenHeight / 2 };
		baVelocity = 1;
		baAngle = 0.0f;
		baWeight = 1;
		baLifeTime = 0.0f;
		baSticky = false;
	}

	Ball::Ball(Spaceship& paddle, vector<int> pos, int velocity, float angle, int weight, float age)
	{
		baPos = { paddle.GetShipPosition()[0] + paddle.GetShipWidth() / 2, paddle.GetShipPosition()[1] - baRadius };
		baVelocity = velocity;
		baAngle = angle;
		baWeight = weight;
		baLifeTime = age;
		baSticky = true;
	}

	void Ball::MoveBall(Spaceship& paddle)
	{
		if(baSticky)
		{
			baPos = { paddle.GetShipPosition()[0] + paddle.GetShipWidth() / 2, paddle.GetShipPosition()[1] - baRadius };
		}
	}

	void Ball::DrawBall()
	{
		DrawCircleGradient(baPos[0], baPos[1], baRadius, RED, GOLD);

		Vector2 origin = { float(baPos[0]), float(baPos[1]) };

		cout << "mouse x: " << GetMouseX() << ", mouse y: " << GetMouseY() << endl;
		cout << "mouse x - center ball x: " << GetMouseX() - baPos[0] << ", mouse y - center ball y: " << GetMouseY() - baPos[1] << endl;
		cout << "center ball x: " << baPos[0] << ", center ball y: " << baPos[1] << endl;

		Vector2 toZero = { GetMouseX() - float(baPos[0]), GetMouseY() - float(baPos[1]) };

		cout << "toZero x: " << toZero.x << ", toZero y: " << toZero.y << endl;

		float magnitude = sqrtf(pow(toZero.x,2) + pow(toZero.y,2));

		cout << "magnitude: " << magnitude << endl;

		float xNorm = toZero.x / magnitude;
		float yNorm = toZero.y / magnitude;

		cout << "xNorm: " << xNorm << "yNorm: " << yNorm << endl;

		float newX = xNorm * 30.0f;
		float newY = yNorm * 30.0f;

		cout << "newX: " << newX << "newY: " << newY << endl;

		Vector2 newPos = { float(baPos[0]) + newX, float(baPos[1]) + newY };

		cout << "newPos X: " << newPos.x << "newPos Y: " << newPos.y << endl;

//		float lineSightLength = 20.0f;
//		DrawCircleGradient(baPos[0], baPos[1], baRadius, RED, GOLD);
//
//		Vector2 startPos = {float(baPos[0]), float(baPos[1])};
//		Vector2 endPos = {float(GetMouseX()), float(GetMouseY())};
//
//		Vector2 diffPos = {float(baPos[0]-GetMouseX()), float(baPos[1]-GetMouseY())};
//		Vector2 start2Pos = {0.0f,0.0f};
//
//		float magnitude = sqrtf(pow(diffPos.x,2) + pow(diffPos.y,2));
//
//		float wantedMagnitude = 100.0f;
//		float xWeight = (diffPos.x * diffPos.x) / (diffPos.x * diffPos.x + diffPos.y * diffPos.y);
//
//		float newX = sqrtf(wantedMagnitude * wantedMagnitude * xWeight);
//		float newY = sqrtf(wantedMagnitude * wantedMagnitude * (1.0f - xWeight));
//
//		Vector2 realEndPos = { newX, newY };
//		cout << "new x: " << newX << ", new y: " << newY << endl;

//		Vector2 endPosNorm = {diffPos.x / magnitude, diffPos.y / magnitude};
////		Vector2 newEndPos = {-(endPosNorm.x*endPos.x),-(endPosNorm.y*endPos.y)};
//		Vector2 newEndPos = {endPosNorm.x + float(baPos[0]) + lineSightLength,endPosNorm.y + float(baPos[1]) + lineSightLength};

//		cout << "mag: " << magnitude << endl;
//		cout << "norm x: " << endPosNorm.x << ", norm y: " << endPosNorm.y << endl;
//		cout << "norm x+baPos[0]: " << endPosNorm.x + baPos[0]<< ", norm y: " << endPosNorm.y + baPos[1] << endl;

		DrawLineEx(origin, newPos, 2.0f, YELLOW);
//		DrawLineEx(start2Pos, realEndPos, 2.0f, YELLOW);
//		DrawLine(baPos[0], baPos[1], baPos[0], baPos[1] - lineSightLength, YELLOW);
	}

	Ball::~Ball()
	{

	}

}
