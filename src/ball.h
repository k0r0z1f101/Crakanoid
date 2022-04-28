#pragma once
#include "raylib.h"
#include "crakanoid.h"
#include "spaceship.h"
#include "tools.h"

using namespace tools;

namespace crakanoid
{
	class Ball
	{
	private:
		static const int _baRadius; //radius of the ball in pixels
		static const float _baLineSight; //length in pixels of the line that points to the mouse
		Vector2 _baPos; //position of the ball (h pos, v pos)
		float _baSpeed; //speed of the ball
		float _baAngle; //angle of the ball
		bool _baSticky; //if true the ball will stick to the ship
		bool _baNoRebound; //if true the ball will go through blocks instead of rebouncing
		bool _baOneLife; //destroyed after it pass the bottom of screen (multiball)

	public:
		Ball();
		Ball(float shipWidth, Vector2 shipPos, float speed = 5.0f, float angle = 0.0f, bool once = false);
		void MoveBall(float shipWidth, Vector2 shipPos);
		void DrawBall();

		void GetAngleToMousePos(Vector2& toZero, float& mag); //set baAngle at angle in degree to mouse cursor counterclokwise, starting from east
		float GetRadianFromDegree(); //return angle in radian from a ball rotation angle in degree
		float GetAngle();
		Vector2 GetPosition();
		bool GetSticky();
		bool GetNoRebound();
		bool GetOneLife();
		float GetRadius();

		void SetPosition(Vector2 pos);
		void SetAngle(float angle);
		void AdjustSpeed(float speed);
		void SetSpeed(float speed);
		void SetSticky(bool);
		void SetNoRebound(bool);

	};
}
