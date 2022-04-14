#include "raylib.h"
#include "crakanoid.h"
#include "tools.h"

using namespace tools;

namespace crakanoid
{
	const float Spaceship::ssStartX = screenWidth/2;
	const float Spaceship::ssHeight = 20;

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
		rec.x = ssPos.x;
		rec.y = ssPos.y;
		Vector2 ori = { 0.0f, 0.0f };
		DrawRectanglePro(rec, ori, 0.0f, RED);
	}
	void Spaceship::MoveShip()
	{
		if(IsKeyDown(KEY_A))
			ssPos.x -= ssSpeed;

		if(IsKeyDown(KEY_D))
			ssPos.x += ssSpeed;
	}
	Vector2& Spaceship::GetShipPosition()
	{
		return ssPos;
	}
	int& Spaceship::GetShipWidth()
	{
		return ssWidth;
	}
	float Spaceship::GetShipHeight()
	{
		return ssHeight;
	}
	Spaceship::~Spaceship()
	{

	}

	//Block definitions
	Block::Block()
	{
		blColor = blockColors[0]; //block color
		blLifePoint = 1; //block life point before being destroyed
		blPos = { 30.0f, 30.0f };
	}

	Block::Block(float x, float y, BlockColor col)
	{
		blPos = { x, y }; //block position (h pos, v pos)
		blColor = blockColors[col]; //block color
		blLifePoint = col; //block life point before being destroyed
	}

	Vector2 Block::getPosition()
	{
		return blPos;
	}

	Color Block::getColor()
	{
		return blColor;
	}

	void Block::setPosition(float x, float y)
	{
		blPos.x = x;
		blPos.y = y;
	}

	Block::~Block()
	{

	}

	//Ball definitions
	const int Ball::baRadius = 6; //radius of the ball in pixels
	const float Ball::baLineSight = 30.0f;

	Ball::Ball()
	{
		baPos = { screenWidth / 2, screenHeight / 2 };
		baVelocity = 1.0f;
		baAngle = 0.0f;
		baWeight = 1;
		baLifeTime = 0.0f;
		baSticky = false;
	}

	Ball::Ball(Spaceship& ship, Vector2 pos, float velocity, float angle, int weight, float age)
	{
		baPos = { ship.GetShipPosition().x + ship.GetShipWidth() / 2, ship.GetShipPosition().y - baRadius };
		baVelocity = velocity;
		baAngle = angle;
		baWeight = weight;
		baLifeTime = age;
		baSticky = true;
	}

	void Ball::MoveBall(Spaceship& ship)
	{
		if(IsKeyDown(KEY_SPACE))
			baSticky = false;
		if(baSticky)
		{
			baPos = { ship.GetShipPosition().x + ship.GetShipWidth() / 2, ship.GetShipPosition().y - baRadius };
		}
		else
		{
			float angle = getRadianFromDegree();
			float cosx = cosf(angle);
			float siny = sinf(angle);
			cout << "x: " << (baVelocity*cosx) << endl;
			cout << "y: " << (baVelocity*siny) << endl;
			if(baAngle < 90 || baAngle > 270)
			{
				baPos.x += baVelocity*cosx;
				baPos.y += baVelocity*siny;
			}
			else
			{
				baPos.x -= baVelocity*cosx;
				baPos.y += baVelocity*siny;
			}
		}
	}

	void Ball::DrawBall()
	{
		if(baSticky)
		{
			//Draw a line that points to the mouse cursor
			Vector2 toZero = { GetMouseX() - baPos.x, GetMouseY() - baPos.y };

			float magnitude = getMagnitude(toZero);

			Vector2 toZeroNorm = normalizeVector(toZero);

			float newX = toZeroNorm.x * baLineSight;
			float newY = toZeroNorm.y * baLineSight;
			Vector2 newPos = { baPos.x + newX, baPos.y + newY };

			getAngleToMousePos(toZero, magnitude);
			cout << "1: " << baAngle << endl;
	//		cout << "2: " << baAngle * RAD2DEG << endl;
	//		cout << "3: " << asinf(toZero.y / magnitude) << endl;
	//		cout << "4: " << getRadianFromDegree() << endl;
			DrawLineEx(baPos, newPos, 2.0f, YELLOW);
		}
		DrawCircleGradient(baPos.x, baPos.y, baRadius, RED, GOLD);
	}

	//calculate new angle of ball in Degree, counterclockwise, starting from east
	void Ball::getAngleToMousePos(Vector2& toZero, float& mag)
	{
		baAngle = asinf(toZero.y / mag) * RAD2DEG;

//		cout << "rad2deg 2: " << baAngle << endl;

		if(GetMouseX() > baPos.x && GetMouseY() <= baPos.y)
		{
			baAngle = fabs(baAngle);
		}
		if(GetMouseX() > baPos.x && GetMouseY() > baPos.y)
		{
			baAngle = 360 - baAngle;
		}
		if(GetMouseX() <= baPos.x && GetMouseY() > baPos.y)
		{
			baAngle = 270 - (90 - baAngle);
		}
		if(GetMouseX() <= baPos.x && GetMouseY() <= baPos.y)
		{
			baAngle = 270 - (90 - baAngle);
		}
	}

	//calculate angle in radian of ball from DEGREE baAngle
	float Ball::getRadianFromDegree()
	{
		float angle = baAngle;

		if(baAngle < 90) //1er cadran
		{
			angle = -angle;
		}
		if(baAngle > 270)
		{
			angle = 360.0f - angle;
		}
		if(baAngle > 180 && baAngle < 270)
		{
			angle = angle - 180.0f;
		}
		if(baAngle > 90 && baAngle < 180)
		{
			angle = angle - 180.0f;
		}

		return angle = angle * DEG2RAD;
	}

	float Ball::getAngle()
	{
		return baAngle;
	}

	Vector2 Ball::getPosition()
	{
		return baPos;
	}

	void Ball::setPosition(float x, float y)
	{
		baPos.x = x;
		baPos.y = y;
	}

	void Ball::setAngle(float angle)
	{
		baAngle = angle;
	}

	void Ball::adjustSpeed(float speed)
	{
		baVelocity += speed;
	}

	Ball::~Ball()
	{

	}

}
