#pragma once
#include "raylib.h"
#include "crakanoid.h"
#include "block.h"
#include "upgrade.h"
#include "ball.h"
#include <random>

using std::vector;

namespace crakanoid
{
	class Spaceship
	{
	private:
		static const float _ssStartX; 		//starting horizontal position
		static const float _ssHeight; 		//height of the ship
		static const int _ssBlockUpgrade; 	//number of blocks to destroyed to spawn an upgrade
		Vector2 _ssPos; 					//position of the spaceship (h pos, v pos)
		float _ssSpeed; 					//speed in pixel of lateral movement
		int _ssWidth; 						//horizontal size
		int _ssBall; 						//lives of the player, number of balls left
		int _ssBlockDestroyed; 				//number of blocks destroyed without dying
		Upgrade _ssUpgrade; 				//current active upgrade

	public:
		Spaceship();
		void DrawShip();
		void MoveShip();
//		vector<Ball> UpdateUpgrade();
//		vector<Ball> Test();
//		void Test(Ball ball);

		Vector2& GetShipPosition();
		int& GetShipWidth();
		float GetShipHeight();
		int GetBallsLeft();
		float GetShipSpeed();
		Upgrade GetUpgrade();

		int LoseBall(int ball);
		int GainBall(int ball);
		void AdjustSpeed(float speed);
		void SetSpeed(float speed);
		void SetWidth(int width);
		vector<Upgrade> DestroyBlock(Block block, vector<Upgrade> upgrades);
		void SetUpgrade(Upgrade upgrade);
		int ActivateAbility();
		~Spaceship();
	};
}
