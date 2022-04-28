#include "raylib.h"
#include "crakanoid.h"
#include "sound.h"
#include "tools.h"

using namespace crakanoid;
using namespace sound;
using std::vector;

const int LEVELONELINES = 3;
const int LEVELINTROLINES = 15;

int main(void)
{
	srand(time(0));

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crakanoid");

    InitAudioDevice();              // Initialize audio device
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    Font font = LoadFont("resources/fonts/Daco_3904520.png");

    int levelInd = 0;
    Level currentLevel = Level(levelInd);

    int _score = {};
    int hitInARow = {};
    int scoreMultiplierThreshold = 10;
    int blocksLeftToWin = currentLevel.GetNeededToWin();

    SongPlayer jukebox;
    jukebox.randomSongPath();
    jukebox.playSong();

    SamplePlayer sampler;

    Spaceship craker;
    //cout << "here " << craker.GetShipPosition().x << endl;
    sampler.playSample("newball.wav");

    vector<Ball> balls;
    Ball ball1 = Ball(craker.GetShipWidth(), craker.GetShipPosition());
    balls.push_back(ball1);
//    Ball ball2 = Ball();

	vector<Upgrade> _upgrades;

	//Stars in the background
	vector<array<int,2>> stars = {
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT },
		{ rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT }
	};

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

    	//stars movement down
    	for(size_t i = 0; i < stars.size(); ++i)
    	{
    		if(stars[i][0] + craker.GetShipSpeed() > SCREEN_WIDTH || stars[i][0] + craker.GetShipSpeed() > SCREEN_HEIGHT)
    		{
        		stars[i][0] = rand() % SCREEN_WIDTH;
        		stars[i][1] = -(rand() % (SCREEN_HEIGHT / 2));
    		}
    		else
    		{
    			stars[i][0] += 1.0f;
    			stars[i][1] += craker.GetShipSpeed();
    		}
    	}

    	jukebox.changeVolume();
    	jukebox.updateStream();
    	if(!jukebox.isSongPlaying())
    	{
    		jukebox.randomSongPath();
    		jukebox.playSong();
    	}

    	craker.MoveShip();
//    	craker.UpdateUpgrade();

    	if(craker.GetUpgrade().GetType() == 1)
    	{
    		balls.push_back(Ball(craker.GetShipWidth(), craker.GetShipPosition(), 5.0f, 90.0f, true));
    		craker.SetUpgrade(Upgrade(craker.GetShipPosition()));
    	}

    	if(craker.GetUpgrade().GetType() == 4)
    		craker.SetWidth(120);
    	else
    		craker.SetWidth(80);

    	vector<int> ballsIndexToDestroy = {};
    	for(size_t i = 0; i < balls.size(); ++i)
    	{
    		//test
//    		CheckCollisionCircleRec(balls[i].getPosition(), balls[i].getRadius(), rec)

    		//collision with walls
    		if(balls[i].GetPosition().y <= PLAYSCREEN_MARGIN) //top
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].AdjustSpeed(1.0f);
				balls[i].SetAngle(360 - balls[i].GetAngle());
    			balls[i].SetPosition({balls[i].GetPosition().x, PLAYSCREEN_MARGIN + 1.0f});
    		}
    		else
    		if(balls[i].GetPosition().x <= PLAYSCREEN_MARGIN) //left
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].AdjustSpeed(1.0f);
    			if(balls[i].GetAngle() > 180.0f)
    				balls[i].SetAngle((180 - balls[i].GetAngle()) + 360);
    			else
    			if(balls[i].GetAngle() <= 180.0f)
    				balls[i].SetAngle(180 - balls[i].GetAngle());
    			balls[i].SetPosition({PLAYSCREEN_MARGIN + 1.0f, balls[i].GetPosition().y});
    		}
    		else
    		if(balls[i].GetPosition().x >= (SCREEN_WIDTH - PLAYSCREEN_MARGIN)) //right
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].AdjustSpeed(1.0f);
    			if(balls[i].GetAngle() <= 180.0f)
    				balls[i].SetAngle(180 - balls[i].GetAngle());
    			else
    			if(balls[i].GetAngle() > 180.0f)
    				balls[i].SetAngle((180 - balls[i].GetAngle()) + 360);
    			balls[i].SetPosition({(SCREEN_WIDTH - PLAYSCREEN_MARGIN) - 1.0f, balls[i].GetPosition().y});
    		}
    		else
    		if(balls[i].GetPosition().y >= SCREEN_HEIGHT - PLAYSCREEN_MARGIN) //bottom
    		{
    			if(!balls[i].GetOneLife())
    			{
					craker.LoseBall(1);
					craker.SetUpgrade(Upgrade());
					hitInARow = {};
					sampler.playSample("balldestroyed.wav");
					balls[i].SetSpeed(5.0f);
					balls[i].SetSticky(true);
					sampler.playSample("newball.wav");
    			}
    			else
    			{
					sampler.playSample("balldestroyed.wav");
					ballsIndexToDestroy.push_back(i);
    			}
    		}
    		else
    		//collision with ship
    		if((balls[i].GetPosition().y + balls[i].GetRadius()) > craker.GetShipPosition().y && (balls[i].GetPosition().y + balls[i].GetRadius())  < (craker.GetShipPosition().y + craker.GetShipHeight()) && balls[i].GetPosition().x < (craker.GetShipPosition().x + craker.GetShipWidth()) && balls[i].GetPosition().x > craker.GetShipPosition().x)
    		{
    			if(craker.GetUpgrade().GetType() != 3)
    			{
					sampler.playSample("ballhit.wav");
					//get on which side of the ship the ball hit and adjust angle of ball accordingly
					float newAngle = 360.0f - balls[i].GetAngle();
					float toCenterShip = ((craker.GetShipPosition().x + craker.GetShipWidth()/2) - balls[i].GetPosition().x)/(craker.GetShipWidth()/2);
//	    			cout << "distance to center of ship: " << toCenterShip << endl;
//	    			cout << "ship x: " << craker.GetShipPosition().x << ", y: " << craker.GetShipPosition().y << endl;
//	    			cout << "ball x: " << balls[i].GetPosition().x << ", y: " << balls[i].GetPosition().y << endl;
//	    			cout << "angle of ball: " << balls[i].GetAngle() << endl;
//	    			cout << "awaited angle of ball: " << newAngle << endl;
//	    			cout << "calcul: " << ((newAngle - 10.0f) * fabs(toCenterShip)) << endl;
					if(toCenterShip < 0.0f) //right of center of ship
						newAngle = newAngle - ((newAngle - 10.0f) * fabs(toCenterShip));
					else //left of center of ship
						newAngle = newAngle + (170.0f - newAngle) * toCenterShip;

					balls[i].SetAngle(newAngle);
//	    			cout << "angle of ball: " << balls[i].GetAngle() << endl;
					balls[i].SetPosition({balls[i].GetPosition().x, craker.GetShipPosition().y - balls[i].GetRadius()});
//	    			cout << "ball x: " << balls[i].GetPosition().x << ", y: " << balls[i].GetPosition().y << endl;
					balls[i].SetSpeed(5.0f);
					craker.SetSpeed(5.0f);
    			}
    			else
    				balls[i].SetSticky(true);
    		}
    		else
    		{
				//collision with blocks
				for(size_t j = 0; j < currentLevel.GetBlocks().size(); ++j)
				{
//					cout << "b# " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
	        		if(currentLevel.GetBlocks()[j].GetLifePoint() <= 0) continue;
//					cout << "ball x: " << (balls[i].getPosition().x) << endl;
//					cout << "ball y: " << (balls[i].getPosition().y) << endl;
					if((balls[i].GetPosition().y - balls[i].GetRadius()) < (currentLevel.GetBlocks()[j].GetPosition().y + currentLevel.GetBlocks()[j].GetSize().y) && (balls[i].GetPosition().y - balls[i].GetRadius()) > currentLevel.GetBlocks()[j].GetPosition().y && (balls[i].GetPosition().x) > currentLevel.GetBlocks()[j].GetPosition().x && (balls[i].GetPosition().x) < currentLevel.GetBlocks()[j].GetPosition().x + currentLevel.GetBlocks()[j].GetSize().x && balls[i].GetAngle() < 180.0f && balls[i].GetAngle() > 0.0f) //bottom
					{
//						cout << "BLOCK #: " << j << " x: " << currentLevel.GetBlocks()[j].getPosition().x << ", b y: " << currentLevel.GetBlocks()[j].getPosition().y << " angle: " << balls[i].getAngle() << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						//cout << "life b4: " << currentLevel.GetBlocks()[j].GetLifePoint() << endl;
						currentLevel.GetBlocks()[j].LoseLifePoint(1);
						//cout << "life after: " << currentLevel.GetBlocks()[j].GetLifePoint() << endl;
						if(currentLevel.GetBlocks()[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(currentLevel.GetBlocks()[j], _upgrades);
			    		    sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
			    		    sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							balls[i].SetAngle(360 - balls[i].GetAngle());
							balls[i].SetPosition({balls[i].GetPosition().x, currentLevel.GetBlocks()[j].GetPosition().y + currentLevel.GetBlocks()[j].GetSize().y + balls[i].GetRadius()});
						}
						if(int(hitInARow / scoreMultiplierThreshold) < int((hitInARow + 1) / scoreMultiplierThreshold))
						{
							string wowSound = "wow";
							wowSound += std::__cxx11::to_string((1+(rand() % 5)));
							wowSound += ".wav";
							sampler.playSample(wowSound);
						}
						_score += int((hitInARow / scoreMultiplierThreshold) + 1);
						++hitInARow;
					}
		    		else
		    		if((balls[i].GetPosition().x - balls[i].GetRadius()) < (currentLevel.GetBlocks()[j].GetPosition().x + currentLevel.GetBlocks()[j].GetSize().x) && (balls[i].GetPosition().x - balls[i].GetRadius()) > currentLevel.GetBlocks()[j].GetPosition().x && balls[i].GetPosition().y > currentLevel.GetBlocks()[j].GetPosition().y && balls[i].GetPosition().y < (currentLevel.GetBlocks()[j].GetPosition().y + currentLevel.GetBlocks()[j].GetSize().y) && balls[i].GetAngle() < 270.0f && balls[i].GetAngle() > 90.0f) //right
		    		{
//						cout << "BALL #: " << j << " x: " << currentLevel.GetBlocks()[j].getPosition().x << ", b y: " << currentLevel.GetBlocks()[j].getPosition().y << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						currentLevel.GetBlocks()[j].LoseLifePoint(1);
						if(currentLevel.GetBlocks()[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(currentLevel.GetBlocks()[j], _upgrades);
			    		    sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
			    		    sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							if(balls[i].GetAngle() > 180.0f)
								balls[i].SetAngle(((270.0f - balls[i].GetAngle()) * 2) + balls[i].GetAngle());
							else
							if(balls[i].GetAngle() <= 180.0f)
								balls[i].SetAngle(180 - balls[i].GetAngle());
							balls[i].SetPosition({currentLevel.GetBlocks()[j].GetPosition().x + currentLevel.GetBlocks()[j].GetSize().x + balls[i].GetRadius(), balls[i].GetPosition().y});
						}
						if(int(hitInARow / scoreMultiplierThreshold) < int((hitInARow + 1) / scoreMultiplierThreshold))
						{
							string wowSound = "wow";
							wowSound += std::__cxx11::to_string((1+(rand() % 5)));
							wowSound += ".wav";
							sampler.playSample(wowSound);
						}
						_score += int((hitInARow / scoreMultiplierThreshold) + 1);
						++hitInARow;
		    		}
		    		else
		    		if((balls[i].GetPosition().x + balls[i].GetRadius()) > currentLevel.GetBlocks()[j].GetPosition().x && (balls[i].GetPosition().x + balls[i].GetRadius()) < (currentLevel.GetBlocks()[j].GetPosition().x + currentLevel.GetBlocks()[j].GetSize().x) && balls[i].GetPosition().y > currentLevel.GetBlocks()[j].GetPosition().y && balls[i].GetPosition().y < (currentLevel.GetBlocks()[j].GetPosition().y + currentLevel.GetBlocks()[j].GetSize().y) && ((balls[i].GetAngle() > 270.0f && balls[i].GetAngle() < 360.0f) || (balls[i].GetAngle() < 90.0f))) //left
		    		{
//						cout << "BALL #: " << j << " x: " << currentLevel.GetBlocks()[j].getPosition().x << ", b y: " << currentLevel.GetBlocks()[j].getPosition().y << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						currentLevel.GetBlocks()[j].LoseLifePoint(1);
						if(currentLevel.GetBlocks()[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(currentLevel.GetBlocks()[j], _upgrades);
			    		    sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
			    		    sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							if(balls[i].GetAngle() > 270.0f)
								balls[i].SetAngle(balls[i].GetAngle() - ((balls[i].GetAngle() - 270.0f) * 2));
							else
							if(balls[i].GetAngle() <= 90.0f)
								balls[i].SetAngle(balls[i].GetAngle() + ((90.0f - balls[i].GetAngle()) * 2));
							balls[i].SetPosition({currentLevel.GetBlocks()[j].GetPosition().x - balls[i].GetRadius(), balls[i].GetPosition().y});
						}
						if(int(hitInARow / scoreMultiplierThreshold) < int((hitInARow + 1) / scoreMultiplierThreshold))
						{
							string wowSound = "wow";
							wowSound += std::__cxx11::to_string((1+(rand() % 5)));
							wowSound += ".wav";
							sampler.playSample(wowSound);
						}
						_score += int((hitInARow / scoreMultiplierThreshold) + 1);
						++hitInARow;
		    		}
		    		else
					if((balls[i].GetPosition().y + balls[i].GetRadius()) > currentLevel.GetBlocks()[j].GetPosition().y && (balls[i].GetPosition().y + balls[i].GetRadius()) < (currentLevel.GetBlocks()[j].GetPosition().y + currentLevel.GetBlocks()[j].GetSize().y) && (balls[i].GetPosition().x) > currentLevel.GetBlocks()[j].GetPosition().x && (balls[i].GetPosition().x) < currentLevel.GetBlocks()[j].GetPosition().x + currentLevel.GetBlocks()[j].GetSize().x && balls[i].GetAngle() < 360.0f && balls[i].GetAngle() > 180.0f) //top
					{
//						cout << "BLOCK #: " << j << " x: " << currentLevel.GetBlocks()[j].getPosition().x << ", b y: " << currentLevel.GetBlocks()[j].getPosition().y << " angle: " << balls[i].getAngle() << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						currentLevel.GetBlocks()[j].LoseLifePoint(1);
						if(currentLevel.GetBlocks()[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(currentLevel.GetBlocks()[j], _upgrades);
							sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
							sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							balls[i].SetAngle(360 - balls[i].GetAngle());
							balls[i].SetPosition({balls[i].GetPosition().x, currentLevel.GetBlocks()[j].GetPosition().y - balls[i].GetRadius()});
						}
						if(int(hitInARow / scoreMultiplierThreshold) < int((hitInARow + 1) / scoreMultiplierThreshold))
						{
							string wowSound = "wow";
							wowSound += std::__cxx11::to_string((1+(rand() % 5)));
							wowSound += ".wav";
							sampler.playSample(wowSound);
						}
						_score += int((hitInARow / scoreMultiplierThreshold) + 1);
						++hitInARow;
					}
				}
    		}

    		balls[i].MoveBall(craker.GetShipWidth(), craker.GetShipPosition());
    	}
    	//destroy balls that need to be
    	for(size_t i = {}; i < ballsIndexToDestroy.size(); ++i)
			balls.erase(balls.begin() + ballsIndexToDestroy[i]);

    	if(craker.GetBallsLeft() <= 0) break; //Game Over

    	//update upgrades in movement
    	vector<int> toDestroy = {};
    	for(size_t i = {}; i < _upgrades.size(); ++i)
    	{

    		if(!_upgrades[i].GetOnShip())
    		{
				Vector2 newPos = _upgrades[i].GetPos();
//				cout << _upgrades[i].GetPos().x << " " << _upgrades[i].GetPos().y << endl;
				newPos.y += 3.0f;
				_upgrades[i].SetPos(newPos);
//				cout << _upgrades[i].GetPos().x << " " << _upgrades[i].GetPos().y << endl;
				if((newPos.y + 3.0f) > SCREEN_HEIGHT - PLAYSCREEN_MARGIN)
				{
					  vector<int>::iterator it;

					  it = toDestroy.begin();
					  it = toDestroy.insert ( it , i );

					  toDestroy.insert (it,0,i);
				}
				else
				if((newPos.y + 3.0f) > craker.GetShipPosition().y && (newPos.y - 3.0f) < (craker.GetShipPosition().y + craker.GetShipHeight()) && (newPos.x + 3.0f) > craker.GetShipPosition().x && (newPos.x - 3.0f) < (craker.GetShipPosition().x + craker.GetShipWidth()))
				{
					_upgrades[i].setOnShip();
				    sampler.playSample("upgradeonship.wav");
				    craker.SetUpgrade(_upgrades[i]);
				    craker.ActivateAbility();
				    switch(craker.GetUpgrade().GetType()) {
					case 0:
						sampler.playSample("invincible.wav");
							break;
					case 1:
						sampler.playSample("multiball.wav");
							break;
					case 2:
						sampler.playSample("life.wav");
						craker.GainBall(1);
						craker.SetUpgrade(Upgrade());
							break;
					case 3:
						sampler.playSample("sticky.wav");
							break;
					case 4:
						sampler.playSample("largership.wav");
							break;
						default:
							break;
					}

				    vector<int>::iterator it;
				    it = toDestroy.begin();
				    it = toDestroy.insert ( it , i );
				    toDestroy.insert (it,0,i);
				}
    		}
//    		if(craker.GetUpgrade().GetType() != -1)
//    		{
//				Vector2 shipPos = craker.GetShipPosition();
//				shipPos.x += craker.GetShipWidth()/2;
//				shipPos.y += craker.GetShipHeight()/2;
//				craker.SetUpgrade(craker.GetUpgrade().SetPos(shipPos));
//    		}
    	}
		//cout << "destroy " << toDestroy.size() << endl;
		for(int i = {}; i < toDestroy.size(); ++i)
			_upgrades.erase(_upgrades.begin() + toDestroy[i]);

    	//cout << blocksLeftToWin << endl;
    	if(blocksLeftToWin == 0)
    	{
    		jukebox.playSongPath("victory/Arkanoid Piano Victory Theme.mp3");
    		blocksLeftToWin = -1;
    		++levelInd;

    		currentLevel = Level(levelInd);

    		hitInARow = {};
    		blocksLeftToWin = currentLevel.GetNeededToWin();

    		craker = {};
			//cout << "here " << craker.GetShipPosition().x << endl;
			sampler.playSample("newball.wav");

			balls = {};
			ball1 = Ball(craker.GetShipWidth(), craker.GetShipPosition());
			balls.push_back(ball1);

			_upgrades = {};
    	}

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        	ClearBackground(BLACK);
        	//Draw star in the background
        	for(size_t i = 0; i < stars.size(); ++i)
        	{
        		DrawPixel(stars[i][0],stars[i][1], WHITE);
        		if(craker.GetShipSpeed() >= 10.0f)
            		DrawPixel(stars[i][0],stars[i][1] - 1.0f, WHITE);
        	}

        	string songName = jukebox.getSongPlaying();
        	DrawText(songName.c_str(), 50, 4, 12, RED);

        	craker.DrawShip();

        	for(size_t i = 0; i < balls.size(); ++i)
        	{
        		balls[i].DrawBall();
        	}

        	for(size_t i = 0; i < currentLevel.GetBlocks().size(); ++i)
        	{
        		currentLevel.GetBlocks()[i].Draw();
        	}

        	//update upgrades
        	for(size_t i = {}; i < _upgrades.size(); ++i)
        	{
        		_upgrades[i].Draw();
        	}
        	//update upgrade on ship
        	if(craker.GetUpgrade().GetType() != -1)
        		DrawCircle(craker.GetUpgrade().GetPos().x, craker.GetUpgrade().GetPos().y, 3.0f, upgradeColors[craker.GetUpgrade().GetType()]);

        	//update lives display
        	for(int i = {}; i < craker.GetBallsLeft(); ++i)
        		DrawCircleGradient(SCREEN_WIDTH - 90.0f - PLAYSCREEN_MARGIN * 2.0f - i * 20.0f, 10.0f, 6.0f, RED, GOLD);

        	//update score display
        	DrawTextEx(font, std::__cxx11::to_string(_score).c_str(), {SCREEN_WIDTH - PLAYSCREEN_MARGIN * 2.0f, 6.0f}, 12.0f, 1.0, WHITE);
        	DrawTextEx(font, "x", {SCREEN_WIDTH - 50.0f - PLAYSCREEN_MARGIN * 2.0f, 6.0f}, 12.0f, 1.0, WHITE);
        	DrawTextEx(font, std::__cxx11::to_string(int((hitInARow / scoreMultiplierThreshold) + 1)).c_str(), {SCREEN_WIDTH - 40.0f - PLAYSCREEN_MARGIN * 2.0f, 6.0f}, 12.0f, 1.0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
