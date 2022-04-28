#include "ball.h"

namespace crakanoid
{
	const int Ball::_baRadius = 6; //radius of the ball in pixels
	const float Ball::_baLineSight = 30.0f;

	Ball::Ball(float shipWidth, Vector2 shipPos, float speed, float angle, bool once)
	{
		_baPos = {shipPos.x + shipWidth / 2, shipPos.y - _baRadius };
		_baSpeed = speed;
		_baAngle = angle;
		_baSticky = true;
		_baNoRebound = false;
		_baOneLife = once;
	}

	void Ball::MoveBall(float shipWidth, Vector2 shipPos)
	{
		if(IsKeyDown(KEY_SPACE))
			_baSticky = false;
		if(_baSticky)
		{
			_baPos = {shipPos.x + shipWidth / 2, shipPos.y - _baRadius};
		}
		else
		{
			float angle = GetRadianFromDegree();
			float cosx = cosf(angle);
			float siny = sinf(angle);
			if(_baAngle < 90 || _baAngle > 270)
			{
				_baPos.x += _baSpeed*cosx;
				_baPos.y += _baSpeed*siny;
			}
			else
			{
				_baPos.x -= _baSpeed*cosx;
				_baPos.y += _baSpeed*siny;
			}
		}
	//		cout << "_baPos.x " << _baPos.x << "_baPos.y " << _baPos.y << endl;
		}

	void Ball::DrawBall()
	{
		if(_baSticky)
		{
			//Draw a line that points to the mouse cursor
			Vector2 toZero = { GetMouseX() - _baPos.x, GetMouseY() - _baPos.y };

			float magnitude = getMagnitude(toZero);

			Vector2 toZeroNorm = normalizeVector(toZero);

			float newX = toZeroNorm.x * _baLineSight;
			float newY = toZeroNorm.y * _baLineSight;
			Vector2 newPos = { _baPos.x + newX, _baPos.y + newY };

			GetAngleToMousePos(toZero, magnitude);
			DrawLineEx(_baPos, newPos, 2.0f, YELLOW);
		}
		DrawCircleGradient(_baPos.x, _baPos.y, _baRadius, RED, GOLD); //draw a ball
	}

	//calculate new angle of ball in Degree, counterclockwise, starting from east
	void Ball::GetAngleToMousePos(Vector2& toZero, float& mag)
	{
		_baAngle = asinf(toZero.y / mag) * RAD2DEG;

		if(GetMouseX() > _baPos.x && GetMouseY() <= _baPos.y)
		{
			_baAngle = fabs(_baAngle);
		}
		if(GetMouseX() > _baPos.x && GetMouseY() > _baPos.y)
		{
			_baAngle = 360 - _baAngle;
		}
		if(GetMouseX() <= _baPos.x && GetMouseY() > _baPos.y)
		{
			_baAngle = 270 - (90 - _baAngle);
		}
		if(GetMouseX() <= _baPos.x && GetMouseY() <= _baPos.y)
		{
			_baAngle = 270 - (90 - _baAngle);
		}
	}

	//calculate angle in radian of _ball from DEGREE baAngle
	float Ball::GetRadianFromDegree()
	{
		float angle = _baAngle;

		if(_baAngle < 90) //1er cadran
		{
			angle = -angle;
		}
		if(_baAngle > 270)
		{
			angle = 360.0f - angle;
		}
		if(_baAngle > 180 && _baAngle < 270)
		{
			angle = angle - 180.0f;
		}
		if(_baAngle > 90 && _baAngle < 180)
		{
			angle = angle - 180.0f;
		}

		return angle = angle * DEG2RAD;
	}

	float Ball::GetAngle()
	{
		return _baAngle;
	}

	bool Ball::GetSticky()
	{
		return _baSticky;
	}

	bool Ball::GetNoRebound()
	{
		return _baNoRebound;
	}

	bool Ball::GetOneLife()
	{
		return _baOneLife;
	}

	float Ball::GetRadius()
	{
		return _baRadius;
	}

	Vector2 Ball::GetPosition()
	{
		return _baPos;
	}

	void Ball::SetPosition(Vector2 pos)
	{
		_baPos = pos;
	}

	void Ball::SetAngle(float angle)
	{
		_baAngle = angle;
	}

	void Ball::AdjustSpeed(float speed)
	{
		_baSpeed = _baSpeed + speed < 5.0f ? 5.0f : _baSpeed + speed;
	}

	void Ball::SetSpeed(float speed)
	{
		_baSpeed = speed;
	}

	void Ball::SetSticky(bool sticky)
	{
		_baSticky = sticky;
	}

	void Ball::SetNoRebound(bool noRebound)
	{
		_baNoRebound = noRebound;
	}
}
