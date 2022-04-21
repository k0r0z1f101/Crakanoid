#include "raylib.h"
#include "crakanoid.h"
#include "tools.h"

using namespace tools;

namespace crakanoid
{
	//UPGRADE
	Upgrade::Upgrade()
	{
		upOnShip = false;
	}
	Vector2 Upgrade::getPos()
	{
		return upPos;
	}
	void Upgrade::setPos(float x, float y)
	{

	}
	bool Upgrade::getOnShip()
	{
		return upOnShip;
	}
	void Upgrade::setOnShip()
	{

	}
	Upgrade::~Upgrade()
	{

	}

	//SPACESHIP
	const float Spaceship::ssStartX = screenWidth/2;
	const float Spaceship::ssHeight = 20;
	const int Spaceship::ssBlockUpgrade = 10;

	Spaceship::Spaceship()
	{
		ssWidth = 50; //starting horizontal size
		ssPos = { ssStartX - (ssWidth / 2), screenHeight - 40 }; //position of spaceship (h pos, v pos)
		ssSpeed = 5.0f; //speed in pixel of lateral movement
		ssBall = 3; //balls left before game over
		ssBlockDestroyed = {}; //number of blocks destroyed without dying
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
	int Spaceship::GetBallsLeft()
	{
		return ssBall;
	}
	float Spaceship::GetShipSpeed()
	{
		return ssSpeed;
	}
	int Spaceship::LoseBall(int ball)
	{
		ssBall -= ball;
		ssSpeed = 5.0f;
		return ssBall;
	}
	void Spaceship::AdjustSpeed(float speed)
	{
		ssSpeed = ssSpeed + speed < 5.0f ? 5.0f : ssSpeed + speed;
	}
	void Spaceship::SetSpeed(float speed)
	{
		ssSpeed = speed;
	}
	void Spaceship::DestroyBlock()
	{
		++ssBlockDestroyed;
		if(ssBlockDestroyed >= ssBlockUpgrade)
		{
			//spawn upgrade at destroyed block
			ssBlockDestroyed = {};
		}
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
		blLifePoint = col + 1; //block life point before being destroyed
	}

	Vector2 Block::getPosition()
	{
		return blPos;
	}

	Color Block::getColor()
	{
		return blColor;
	}

	Vector2 Block::getSize()
	{
		return blSize;
	}

	int Block::getLifePoint()
	{
		return blLifePoint;
	}

	int Block::loseLifePoint(int life)
	{
		blLifePoint -= life;
		setColor(blockColors[blLifePoint-1]);
		return blLifePoint;
	}

	void Block::setPosition(float x, float y)
	{
		blPos.x = x;
		blPos.y = y;
	}

	void Block::setColor(Color color)
	{
		blColor = color;
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
		baSpeed = 5.0f;
		baAngle = 0.0f;
		baWeight = 1;
		baLifeTime = 0.0f;
		baSticky = false;
	}

	Ball::Ball(Spaceship& ship, Vector2 pos, float speed, float angle, int weight, float age)
	{
		baPos = { ship.GetShipPosition().x + ship.GetShipWidth() / 2, ship.GetShipPosition().y - baRadius };
		baSpeed = speed;
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
			if(baAngle < 90 || baAngle > 270)
			{
				baPos.x += baSpeed*cosx;
				baPos.y += baSpeed*siny;
			}
			else
			{
				baPos.x -= baSpeed*cosx;
				baPos.y += baSpeed*siny;
			}
		}
		cout << "baPos.x " << baPos.x << "baPos.y " << baPos.y << endl;
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
			DrawLineEx(baPos, newPos, 2.0f, YELLOW);
		}
		DrawCircleGradient(baPos.x, baPos.y, baRadius, RED, GOLD);
	}

	//calculate new angle of ball in Degree, counterclockwise, starting from east
	void Ball::getAngleToMousePos(Vector2& toZero, float& mag)
	{
		baAngle = asinf(toZero.y / mag) * RAD2DEG;

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

	bool Ball::getSticky()
	{
		return baSticky;
	}

	float Ball::getRadius()
	{
		return baRadius;
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
		baSpeed = baSpeed + speed < 5.0f ? 5.0f : baSpeed + speed;
	}

	void Ball::setSpeed(float speed)
	{
		baSpeed = speed;
	}

	void Ball::setSticky(bool sticky)
	{
		baSticky = sticky;
	}

	Ball::~Ball()
	{

	}
}
