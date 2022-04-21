#include "raylib.h"
#include "crakanoid.h"
#include "sound.h"
#include "tools.h"

using namespace crakanoid;
using namespace sound;

const float PLAYSCREEN_MARGIN = 20.0f;
const int LEVELONELINES = 3;

int main(void)
{
	srand(time(0));

    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "Crakanoid");

    InitAudioDevice();              // Initialize audio device
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    SongPlayer jukebox;
    jukebox.randomSongPath();
    jukebox.playSong();

    SamplePlayer sampler;

    Spaceship craker;
    sampler.playSample("newball.wav");

    vector<Ball> balls;
    Ball ball1 = Ball(craker, craker.GetShipPosition());
    balls.push_back(ball1);
//    Ball ball2 = Ball();

    array<int,LEVELONELINES> levelOneBlocksPerLine = { 30, 30, 30 };

    array<Block,LEVELONELINES> levelOneBlockArray = {
    		Block(0.0f, 0.0f, B_BLUE),
    		Block(0.0f, 0.0f, B_GREEN),
    		Block(0.0f, 0.0f, B_RED)
    };

    int levelOneStartingBlocks = {};
    for(int i = 0;i < LEVELONELINES; ++i)
    	levelOneStartingBlocks += levelOneBlocksPerLine[i];

    vector<Block> blocks;
	for(int i = 0; i < LEVELONELINES; i++)
	{
		for(int j = 0; j < levelOneBlocksPerLine[i]; ++j)
		{
			float newX = PLAYSCREEN_MARGIN + (blSize.x * j) + (2.0f * j);
			float newY = PLAYSCREEN_MARGIN + (blSize.y * i) + (2.0f * i);
			Block newBlock = levelOneBlockArray[i];
			newBlock.setPosition(newX, newY);
			blocks.push_back(newBlock);
//			cout << "i j " << i << " " << j << endl;
//			cout << "newX newY " << newX << " " << newY << endl;
		}
	}

	//Stars in the background
	vector<array<int,2>> stars = {
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight },
		{ rand() % screenWidth, rand() % screenHeight }
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
    		if(stars[i][0] + craker.GetShipSpeed() > screenWidth || stars[i][0] + craker.GetShipSpeed() > screenHeight)
    		{
        		stars[i][0] = rand() % screenWidth;
        		stars[i][1] = -(rand() % (screenHeight / 2));
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


    	for(size_t i = 0; i < balls.size(); ++i)
    	{
    		//collision with walls
    		if(balls[i].getPosition().y <= PLAYSCREEN_MARGIN) //top
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].adjustSpeed(1.0f);
				balls[i].setAngle(360 - balls[i].getAngle());
    			balls[i].setPosition(balls[i].getPosition().x, PLAYSCREEN_MARGIN + 1.0f);
    		}
    		else
    		if(balls[i].getPosition().x <= PLAYSCREEN_MARGIN) //left
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].adjustSpeed(1.0f);
    			if(balls[i].getAngle() > 180.0f)
    				balls[i].setAngle((180 - balls[i].getAngle()) + 360);
    			else
    			if(balls[i].getAngle() <= 180.0f)
    				balls[i].setAngle(180 - balls[i].getAngle());
    			balls[i].setPosition(PLAYSCREEN_MARGIN + 1.0f, balls[i].getPosition().y);
    		}
    		else
    		if(balls[i].getPosition().x >= (screenWidth - PLAYSCREEN_MARGIN)) //right
    		{
    		    sampler.playSample("ballhit.wav");
    			craker.AdjustSpeed(1.0f);
    			balls[i].adjustSpeed(1.0f);
    			if(balls[i].getAngle() <= 180.0f)
    				balls[i].setAngle(180 - balls[i].getAngle());
    			else
    			if(balls[i].getAngle() > 180.0f)
    				balls[i].setAngle((180 - balls[i].getAngle()) + 360);
    			balls[i].setPosition((screenWidth - PLAYSCREEN_MARGIN) - 1.0f, balls[i].getPosition().y);
    		}
    		else
    		if(balls[i].getPosition().y >= screenHeight - PLAYSCREEN_MARGIN) //bottom
    		{
    			craker.LoseBall(1);
    		    sampler.playSample("balldestroyed.wav");
    			balls[i].setSpeed(5.0f);
    			balls[i].setSticky(true);
    		    sampler.playSample("newball.wav");
    		}
    		else
    		//collision with ship
    		if(balls[i].getPosition().y > craker.GetShipPosition().y && balls[i].getPosition().y < (craker.GetShipPosition().y + craker.GetShipHeight()) && balls[i].getPosition().x < (craker.GetShipPosition().x + craker.GetShipWidth()) && balls[i].getPosition().x > craker.GetShipPosition().x)
    		{
    		    sampler.playSample("ballhit.wav");
    			//get on which side of the ship the ball hit and adjust angle of ball accordingly
    			float newAngle = 360.0f - balls[i].getAngle();
    			float toCenterShip = ((craker.GetShipPosition().x + craker.GetShipWidth()/2) - balls[i].getPosition().x)/(craker.GetShipWidth()/2);
//    			cout << "distance to center of ship: " << toCenterShip << endl;
//    			cout << "ship x: " << craker.GetShipPosition().x << ", y: " << craker.GetShipPosition().y << endl;
//    			cout << "ball x: " << balls[i].getPosition().x << ", y: " << balls[i].getPosition().y << endl;
//    			cout << "angle of ball: " << balls[i].getAngle() << endl;
//    			cout << "awaited angle of ball: " << newAngle << endl;
    			if(toCenterShip < 0.0f) //right of center of ship
    				newAngle = newAngle + (180.0f - newAngle) * toCenterShip;
    			else //left of center of ship
    				newAngle = newAngle + (180.0f - newAngle) * toCenterShip;

				balls[i].setAngle(newAngle);
//    			cout << "angle of ball: " << balls[i].getAngle() << endl;
    			balls[i].setPosition(balls[i].getPosition().x, craker.GetShipPosition().y - balls[i].getRadius());
//    			cout << "ball x: " << balls[i].getPosition().x << ", y: " << balls[i].getPosition().y << endl;
    			balls[i].setSpeed(5.0f);
    			craker.SetSpeed(5.0f);
    		}
    		else
    		{
				//collision with blocks
				for(size_t j = 0; j < blocks.size(); ++j)
				{
					cout << "b# " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
	        		if(blocks[j].getLifePoint() <= 0) continue;
					cout << "ball x: " << (balls[i].getPosition().x) << endl;
					cout << "ball y: " << (balls[i].getPosition().y) << endl;
					if((balls[i].getPosition().y - balls[i].getRadius()) < (blocks[j].getPosition().y + blocks[j].getSize().y) && (balls[i].getPosition().x) > blocks[j].getPosition().x && (balls[i].getPosition().x) < blocks[j].getPosition().x + blocks[j].getSize().x && balls[i].getAngle() < 180.0f && balls[i].getAngle() > 0.0f) //bottom
					{
						cout << "BLOCK #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << " angle: " << balls[i].getAngle() << endl;
		    		    sampler.playSample("blockdamage.wav");
						craker.AdjustSpeed(-1.0f);
						balls[i].adjustSpeed(-1.0f);
						blocks[j].loseLifePoint(1);
						balls[i].setAngle(360 - balls[i].getAngle());
						balls[i].setPosition(balls[i].getPosition().x, blocks[j].getPosition().y + blocks[j].getSize().y + balls[i].getRadius());
					}
		    		else
		    		if((balls[i].getPosition().x - balls[i].getRadius()) < (blocks[j].getPosition().x + blocks[j].getSize().x) && (balls[i].getPosition().x + balls[i].getRadius()) > blocks[j].getPosition().x && (balls[i].getPosition().y + balls[i].getRadius()) > blocks[j].getPosition().y && (balls[i].getPosition().y - balls[i].getRadius()) < (blocks[j].getPosition().y + blocks[j].getSize().y) && balls[i].getAngle() < 270.0f && balls[i].getAngle() > 90.0f) //right
		    		{
						cout << "BALL #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
		    		    sampler.playSample("blockdamage.wav");
						craker.AdjustSpeed(-1.0f);
						balls[i].adjustSpeed(-1.0f);
						blocks[j].loseLifePoint(1);
		    			if(balls[i].getAngle() > 180.0f)
		    				balls[i].setAngle(((270.0f - balls[i].getAngle()) * 2) + balls[i].getAngle());
		    			else
		    			if(balls[i].getAngle() <= 180.0f)
		    				balls[i].setAngle(180 - balls[i].getAngle());
		    			balls[i].setPosition(blocks[j].getPosition().x + blocks[j].getSize().x + balls[i].getRadius(), balls[i].getPosition().y);
		    		}
		    		else
		    		if((balls[i].getPosition().x + balls[i].getRadius()) > blocks[j].getPosition().x && (balls[i].getPosition().x + balls[i].getRadius()) < (blocks[j].getPosition().x + blocks[j].getSize().x) && (balls[i].getPosition().y + balls[i].getRadius()) > blocks[j].getPosition().y && (balls[i].getPosition().y - balls[i].getRadius()) < (blocks[j].getPosition().y + blocks[j].getSize().y) && ((balls[i].getAngle() < 270.0f && balls[i].getAngle() > 360.0f) || (balls[i].getAngle() < 90.0f && balls[i].getAngle() > 0.0f))) //left
		    		{
//						cout << "BALL #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
		    		    sampler.playSample("blockdamage.wav");
						craker.AdjustSpeed(-1.0f);
						balls[i].adjustSpeed(-1.0f);
						blocks[j].loseLifePoint(1);
		    			if(balls[i].getAngle() > 270.0f)
		    				balls[i].setAngle(balls[i].getAngle() - ((balls[i].getAngle() - 270.0f) * 2));
		    			else
		    			if(balls[i].getAngle() <= 90.0f)
		    				balls[i].setAngle(balls[i].getAngle() + ((90.0f - balls[i].getAngle()) * 2));
		    			balls[i].setPosition(blocks[j].getPosition().x - balls[i].getRadius(), balls[i].getPosition().y);
		    		}
				}
    		}

    		balls[i].MoveBall(craker);
    	}
    	if(craker.GetBallsLeft() <= 0) break; //Game Over

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

        	for(size_t i = 0; i < blocks.size(); ++i)
        	{
//        		cout << "life " << blocks[i].getLifePoint() << endl;
        		if(blocks[i].getLifePoint() > 0)
        		{
					Rectangle rec;
					rec.height = blSize.y;
					rec.width = blSize.x;
					rec.x = blocks[i].getPosition().x;
					rec.y = blocks[i].getPosition().y;
					Vector2 ori = { 0.0f, 0.0f };
					DrawRectanglePro(rec, ori, 0.0f, blocks[i].getColor());
        		}
        	}

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
