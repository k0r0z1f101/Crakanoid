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
	const float Ball::baLineSight = 30.0f;

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
		//Draw a line that points to the mouse cursor
		Vector2 origin = { float(baPos[0]), float(baPos[1]) };
		Vector2 toZero = { GetMouseX() - float(baPos[0]), GetMouseY() - float(baPos[1]) };

		float magnitude = sqrtf(pow(toZero.x,2) + pow(toZero.y,2));

		float xNorm = toZero.x / magnitude;
		float yNorm = toZero.y / magnitude;

		float newX = xNorm * baLineSight;
		float newY = yNorm * baLineSight;
		Vector2 newPos = { float(baPos[0]) + newX, float(baPos[1]) + newY };

		//calculate new angle of ball
		baAngle = asinf(toZero.y / magnitude);

		cout << "toZero.y " << toZero.y << endl;
		cout << "magnitude " << magnitude << endl;
		cout << "angle " << baAngle << endl;
		cout << "radian to degree " << baAngle * RAD2DEG << endl;

		DrawCircleGradient(baPos[0], baPos[1], baRadius, RED, GOLD);
		DrawLineEx(origin, newPos, 2.0f, YELLOW);

//		cout << "mouse x: " << GetMouseX() << ", mouse y: " << GetMouseY() << endl;
//		cout << "mouse x - center ball x: " << GetMouseX() - baPos[0] << ", mouse y - center ball y: " << GetMouseY() - baPos[1] << endl;
//		cout << "center ball x: " << baPos[0] << ", center ball y: " << baPos[1] << endl;
//		cout << "toZero x: " << toZero.x << ", toZero y: " << toZero.y << endl;
//		cout << "magnitude: " << magnitude << endl;
//		cout << "xNorm: " << xNorm << "yNorm: " << yNorm << endl;
//		cout << "newX: " << newX << "newY: " << newY << endl;
	}

	Ball::~Ball()
	{

	}

}
