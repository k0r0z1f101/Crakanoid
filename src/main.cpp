#include "raylib.h"
#include "crakanoid.h"
#include "sound.h"
#include "tools.h"

using namespace crakanoid;
using namespace sound;

const float PLAYSCREEN_MARGIN = 20.0f;

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

    Spaceship craker;

    vector<Ball> balls;
    Ball ball1 = Ball(craker, craker.GetShipPosition());
    balls.push_back(ball1);
//    Ball ball2 = Ball();

    vector<Block> blocks;
    Block block1;
    Block block2;
    Block block3;
    Block block4;
    blocks.push_back(block1);
    blocks.push_back(block2);
    blocks.push_back(block3);
    blocks.push_back(block4);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
    	jukebox.changeVolume();
    	jukebox.updateStream();
    	if(!jukebox.isSongPlaying())
    	{
    		jukebox.randomSongPath();
    		jukebox.playSong();
    	}

    	craker.MoveShip();

    	for(size_t i = 0; i < blocks.size(); ++i)
    	{
    		float newX = PLAYSCREEN_MARGIN + (blSize.x * i) + (2.0f * i);
    		float newY = PLAYSCREEN_MARGIN;
    		blocks[i].setPosition(newX, newY);
    	}

    	for(size_t i = 0; i < balls.size(); ++i)
    	{
    		//collision with walls
    		if(balls[i].getPosition().y <= PLAYSCREEN_MARGIN)
    		{
    			balls[i].adjustSpeed(1.0f);
				balls[i].setAngle(360 - balls[i].getAngle());
    			balls[i].setPosition(balls[i].getPosition().x, PLAYSCREEN_MARGIN + 1.0f);
    		}
    		else
    		if(balls[i].getPosition().x <= PLAYSCREEN_MARGIN)
    		{
    			balls[i].adjustSpeed(1.0f);
    			if(balls[i].getAngle() > 180.0f)
    				balls[i].setAngle((180 - balls[i].getAngle()) + 360);
    			else
    			if(balls[i].getAngle() <= 180.0f)
    				balls[i].setAngle(180 - balls[i].getAngle());
    			balls[i].setPosition(PLAYSCREEN_MARGIN + 1.0f, balls[i].getPosition().y);
    		}
    		else
    		if(balls[i].getPosition().x >= (screenWidth - PLAYSCREEN_MARGIN))
    		{
    			balls[i].adjustSpeed(1.0f);
    			if(balls[i].getAngle() <= 180.0f)
    				balls[i].setAngle(180 - balls[i].getAngle());
    			else
    			if(balls[i].getAngle() > 180.0f)
    				balls[i].setAngle((180 - balls[i].getAngle()) + 360);
    			balls[i].setPosition((screenWidth - PLAYSCREEN_MARGIN) - 1.0f, balls[i].getPosition().y);
    		}
    		else
    		if(balls[i].getPosition().y >= screenHeight - PLAYSCREEN_MARGIN)
    		{
    			craker.LoseBall(1);
    			balls[i].setSticky(true);
    		}
    		else
    		//collision with ship
    		if(balls[i].getPosition().y > craker.GetShipPosition().y && balls[i].getPosition().y < (craker.GetShipPosition().y + craker.GetShipHeight()) && balls[i].getPosition().x < (craker.GetShipPosition().x + craker.GetShipWidth()) && balls[i].getPosition().x > craker.GetShipPosition().x)
    		{
				balls[i].setAngle(360 - balls[i].getAngle());
    			balls[i].setPosition(balls[i].getPosition().x, craker.GetShipPosition().y - 1.0f);
    		}
    		else
    		{
				//collision with blocks
				for(size_t j = 0; j < blocks.size(); ++j)
				{
	        		if(blocks[j].getLifePoint() <= 0) break;
					cout << "b x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
					cout << "ball x: " << (balls[i].getPosition().x) << endl;
					cout << "ball y: " << (balls[i].getPosition().y + balls[i].getRadius()) << endl;
					if((balls[i].getPosition().y + balls[i].getRadius()) <= (blocks[j].getPosition().y + blocks[j].getSize().y) && (balls[i].getPosition().x) > blocks[j].getPosition().x && (balls[i].getPosition().x) < blocks[j].getPosition().x + blocks[j].getSize().x)
					{
						blocks[j].loseLifePoint(1);
						balls[i].setAngle(360 - balls[i].getAngle());
						balls[i].setPosition(balls[i].getPosition().x, blocks[j].getPosition().y + blocks[j].getSize().y + 1.0f);
					}
				}
    		}

    		balls[i].MoveBall(craker);
    	}
    	if(craker.GetBallsLeft() <= 0) break;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        	ClearBackground(RAYWHITE);

        	string songName = jukebox.getSongPlaying();
        	DrawText(songName.c_str(), 50, 4, 12, RED);

        	craker.DrawShip();

        	for(size_t i = 0; i < balls.size(); ++i)
        	{
        		balls[i].DrawBall();
        	}

        	for(size_t i = 0; i < blocks.size(); ++i)
        	{
        		cout << "life " << blocks[i].getLifePoint() << endl;
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

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
