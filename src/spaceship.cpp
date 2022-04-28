#include "spaceship.h"

namespace crakanoid
{
	const float Spaceship::_ssStartX = SCREEN_WIDTH/2;
	const float Spaceship::_ssHeight = 20;
	const int Spaceship::_ssBlockUpgrade = 3;

	Spaceship::Spaceship()
	{
		_ssWidth = 80; 												//starting horizontal size
		_ssPos = {_ssStartX - (_ssWidth / 2), SCREEN_HEIGHT - 40}; 	//position of spaceship (h pos, v pos)
		_ssSpeed = 5.0f;											//speed in pixel of lateral movement
		_ssBall = 3;												//balls left before game over
		_ssBlockDestroyed = {};										//number of blocks destroyed without dying
		_ssUpgrade = {};
	}
	void Spaceship::DrawShip()
	{
		Rectangle rec;
		rec.height = _ssHeight;
		rec.width = _ssWidth;
		rec.x = _ssPos.x;
		rec.y = _ssPos.y;
		Vector2 ori = { 0.0f, 0.0f };
		DrawRectanglePro(rec, ori, 0.0f, RED);
	}
	void Spaceship::MoveShip()
	{
		if(IsKeyDown(KEY_A))
			_ssPos.x -= _ssSpeed;

		if(IsKeyDown(KEY_D))
			_ssPos.x += _ssSpeed;

		//if there is an upgrade setOnShip, change its position to center ship
		if(_ssUpgrade.GetType() != -1)
		{
			Vector2 shipCenter = _ssPos;
			shipCenter.x += _ssWidth/2;
			shipCenter.y += _ssHeight/2;
			_ssUpgrade.SetPos(shipCenter);
		}
	}
//	vector<Ball> Spaceship::Test()
//	{
//		vector<Ball> newBalls = {Ball()};
//		return newBalls;
//	}
//	void Spaceship::Test(Ball ball)
//	{
//		cout << "AUE: " << ball.GetPosition().x << endl;
//	}

	Vector2& Spaceship::GetShipPosition()
	{
		return _ssPos;
	}
	int& Spaceship::GetShipWidth()
	{
		return _ssWidth;
	}
	float Spaceship::GetShipHeight()
	{
		return _ssHeight;
	}
	int Spaceship::GetBallsLeft()
	{
		return _ssBall;
	}
	float Spaceship::GetShipSpeed()
	{
		return _ssSpeed;
	}
	Upgrade Spaceship::GetUpgrade()
	{
		return _ssUpgrade;
	}
	int Spaceship::LoseBall(int ball)
	{
		_ssBall -= ball;
		_ssSpeed = 5.0f;
		return _ssBall;
	}
	int Spaceship::GainBall(int ball)
	{
		_ssBall += ball;
		return _ssBall;
	}
	void Spaceship::AdjustSpeed(float speed)
	{
		_ssSpeed = _ssSpeed + speed < 5.0f ? 5.0f : _ssSpeed + speed;
	}
	void Spaceship::SetSpeed(float speed)
	{
		_ssSpeed = speed;
	}
	vector<Upgrade> Spaceship::DestroyBlock(Block block, vector<Upgrade> upgrades)
	{
		++_ssBlockDestroyed;
		if(_ssBlockDestroyed >= _ssBlockUpgrade)
		{
			//spawn upgrade at destroyed block
			Vector2 startPos = block.GetPosition();
			startPos.x += block.GetSize().x/2;
			startPos.y += block.GetSize().y/2;
			upgrades.push_back(Upgrade(startPos));
			_ssBlockDestroyed = {};
		}
//		cout << "_ssBlockDestroyed: " << _ssBlockDestroyed << endl;
		return upgrades;
	}
	void Spaceship::SetUpgrade(Upgrade upgrade)
	{
		_ssUpgrade = upgrade;
	}
	void Spaceship::SetWidth(int width)
	{
		_ssWidth = width;
	}
	int Spaceship::ActivateAbility()
	{
		switch (_ssUpgrade.GetType()) {
			case 0:

				break;
			case 1:
				break;
			case 2: //blue, life
				break;
			case 3:
				break;
			case 4:
				break;
		}
		return _ssUpgrade.GetType();
	}
	Spaceship::~Spaceship()
	{

	}
}
