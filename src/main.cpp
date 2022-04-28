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


    //LEVEL 1
    array<int,LEVELONELINES> levelOneBlocksPerLine = { 30, 30, 30 };

    array<Block,LEVELONELINES> levelOneBlockArray = {
    		Block({0.0f, 0.0f}, B_BLUE),
    		Block({0.0f, 0.0f}, B_GREEN),
    		Block({0.0f, 0.0f}, B_RED)
    };

    int levelOneStartingBlocks = {};
    for(int i = 0;i < LEVELONELINES; ++i)
    	levelOneStartingBlocks += levelOneBlocksPerLine[i];

//    vector<Block> blocks;
//	for(int i = 0; i < LEVELONELINES; i++)
//	{
//		for(int j = 0; j < levelOneBlocksPerLine[i]; ++j)
//		{
//			float newX = PLAYSCREEN_MARGIN + (blSize.x * j) + (2.0f * j);
//			float newY = PLAYSCREEN_MARGIN + (blSize.y * i) + (2.0f * i);
//			Block newBlock = levelOneBlockArray[i];
//			newBlock.setPosition(newX, newY);
//			blocks.push_back(newBlock);
////			cout << "i j " << i << " " << j << endl;
////			cout << "newX newY " << newX << " " << newY << endl;
//		}
//	}

	//LEVEL INTRO
    vector<vector<int>> levelIntro = 	{ { 30 }, { 30 }, { 30 }, { 30 }, { 30 }, { 1, 3, 2, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 3, 2, 1 } };
    vector<vector<BlockColor>> introBlockColors = { { B_NONE }, { B_NONE }, { B_NONE }, { B_NONE }, { B_NONE }, { B_NONE, B_RED, B_BLUE, B_NONE, B_GREEN, B_RED, B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED, B_GREEN, B_BLUE, B_RED, B_NONE } };
    levelIntro.push_back({ 1,1,2,1,1,1,1,1,1,2,2,1,1,1,1,3,1,1,1,1,1,1,1,1,1 });
    introBlockColors.push_back( { B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_GREEN, B_NONE, B_GREEN, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_NONE, B_RED, B_GREEN, B_NONE, B_GREEN, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED });
    levelIntro.push_back({ 1,1,2,2,1,3,2,2,3,1,3,1,1,1,1,1,1,1,1,1 });
    introBlockColors.push_back( { B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_GREEN, B_RED, B_NONE, B_BLUE, B_NONE, B_RED, B_GREEN, B_NONE, B_GREEN, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED } );
    levelIntro.push_back({ 1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,2,1 });
    introBlockColors.push_back( { B_NONE, B_RED, B_BLUE, B_NONE, B_BLUE, B_GREEN, B_NONE, B_GREEN, B_RED, B_NONE, B_RED, B_NONE, B_BLUE, B_NONE, B_BLUE, B_NONE, B_RED, B_NONE, B_RED, B_GREEN, B_BLUE, B_RED, B_NONE } );

//    vector<Block> blocks;
//    for(size_t i = {}; i < levelIntro.size(); ++i)
//    {
//		int blockInLine = {};
//    	for(size_t j = {}; j < levelIntro[i].size(); ++j)
//		{
//    		for(int k = {}; k < levelIntro[i][j]; ++k)
//    		{
//    			float newX = PLAYSCREEN_MARGIN + (blSize.x * blockInLine) + (2.0f * blockInLine);
//    			float newY = PLAYSCREEN_MARGIN + (blSize.y * i) + (2.0f * i);
//    			BlockColor newColor = introBlockColors[i][j];
//				blocks.push_back(Block(newX, newY, newColor));
//    			++blockInLine;
//    		}
//		}
//    }

    //LEVEl ONE
    vector<vector<int>> levelOne = 	{ { 30 }, { 30 }, { 30 }, { 30 } };
    vector<vector<BlockColor>> levelOneBlockColors = { { B_NONE }, { B_BLUE }, { B_GREEN }, { B_RED } };
    vector<Block> blocks;
    int levelOneNeededToWin = {};
	for(size_t i = {}; i < levelOne.size(); ++i)
	{
		int blockInLine = {};
		for(size_t j = {}; j < levelOne[i].size(); ++j)
		{
			for(int k = {}; k < levelOne[i][j]; ++k)
			{
				float newX = PLAYSCREEN_MARGIN + (BLOCK_SIZE.x * blockInLine) + (2.0f * blockInLine);
				float newY = PLAYSCREEN_MARGIN + (BLOCK_SIZE.y * i) + (2.0f * i);
				BlockColor newColor = levelOneBlockColors[i][j];
				blocks.push_back(Block({newX, newY}, newColor));
				levelOneNeededToWin += int(newColor) != -1 && int(newColor) < 3 ? 1 : 0;
				++blockInLine;
			}
		}
	}


    //LEVEl TWO
    vector<vector<int>> levelTwo = 	{ { 30 }, { 30 }, { 30 }, { 6, 4, 3, 4, 3, 4 }, { 6, 4, 3, 4, 3, 4 }, { 6, 4, 3, 4, 3, 4 }, { 6, 4, 3, 4, 3, 4 }, { 30 }, { 30 } };
    vector<vector<BlockColor>> levelTwoBlockColors = { { B_NONE }, { B_NONE }, { B_NONE }, { B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED } };
    levelTwoBlockColors.push_back({ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED });
    levelTwoBlockColors.push_back({ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED });
    levelTwoBlockColors.push_back({ B_NONE, B_RED, B_NONE, B_GREEN, B_NONE, B_RED });
    levelTwoBlockColors.push_back( { B_NONE });
    levelTwoBlockColors.push_back( { B_NONE });
    levelTwo.push_back({ 9,1,1,1,1,1,1,1,1,1,1,1});
    levelTwoBlockColors.push_back({ B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER, B_NONE, B_SILVER});
    int levelTwoNeededToWin = {};
//    vector<Block> blocks;
//	for(size_t i = {}; i < levelTwo.size(); ++i)
//	{
//		int blockInLine = {};
//		for(size_t j = {}; j < levelTwo[i].size(); ++j)
//		{
//			for(int k = {}; k < levelTwo[i][j]; ++k)
//			{
//				float newX = PLAYSCREEN_MARGIN + (blSize.x * blockInLine) + (2.0f * blockInLine);
//				float newY = PLAYSCREEN_MARGIN + (blSize.y * i) + (2.0f * i);
//				BlockColor newColor = levelTwoBlockColors[i][j];
//				blocks.push_back(Block(newX, newY, newColor));
//				levelTwoNeededToWin += int(newColor) != -1 && int(newColor) < 3 ? 1 : 0;
//				++blockInLine;
//			}
//		}
//	}
//	cout << "level2: " << levelTwoNeededToWin << endl;


    //LEVEl ONEBRICK
    vector<vector<int>> levelTest = 	{ { 30 }, { 30 }, { 30 }, { 14, 1 } };
    vector<vector<BlockColor>> levelTestBlockColors = { { B_NONE }, { B_NONE }, { B_NONE }, { B_NONE, B_RED } };
    int levelTestNeededToWin = {};
//    vector<Block> blocks;
//	for(size_t i = {}; i < levelTest.size(); ++i)
//	{
//		int blockInLine = {};
//		for(size_t j = {}; j < levelTest[i].size(); ++j)
//		{
//			for(int k = {}; k < levelTest[i][j]; ++k)
//			{
//				float newX = PLAYSCREEN_MARGIN + (BLOCK_SIZE.x * blockInLine) + (2.0f * blockInLine);
//				float newY = PLAYSCREEN_MARGIN + (BLOCK_SIZE.y * i) + (2.0f * i);
//				BlockColor newColor = levelTestBlockColors[i][j];
//				blocks.push_back(Block({newX, newY}, newColor));
//				levelTwoNeededToWin += int(newColor) != -1 && int(newColor) < 3 ? 1 : 0;
//				++blockInLine;
//			}
//		}
//	}
//	cout << "leveltest: " << levelTestNeededToWin << endl;


    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crakanoid");

    InitAudioDevice();              // Initialize audio device
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    int _score = {};
    int hitInARow = {};
    int scoreMultiplierThreshold = 10;
    int blocksLeftToWin = levelOneNeededToWin;

    SongPlayer jukebox;
    jukebox.randomSongPath();
    jukebox.playSong();

    SamplePlayer sampler;

    Spaceship craker;
    cout << "here " << craker.GetShipPosition().x << endl;
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
    		if((balls[i].GetPosition().y + balls[i].GetRadius()) > craker.GetShipPosition().y && (balls[i].GetPosition().y + balls[i].GetRadius())  < (craker.GetShipPosition().y + craker.GetShipHeight()) && (balls[i].GetPosition().x - balls[i].GetRadius()) < (craker.GetShipPosition().x + craker.GetShipWidth()) && (balls[i].GetPosition().x + balls[i].GetRadius()) > craker.GetShipPosition().x)
    		{
    			if(craker.GetUpgrade().GetType() != 3)
    			{
					sampler.playSample("ballhit.wav");
					//get on which side of the ship the ball hit and adjust angle of ball accordingly
					float newAngle = 360.0f - balls[i].GetAngle();
					float toCenterShip = ((craker.GetShipPosition().x + craker.GetShipWidth()/2) - balls[i].GetPosition().x)/(craker.GetShipWidth()/2);
	//    			cout << "distance to center of ship: " << toCenterShip << endl;
	//    			cout << "ship x: " << craker.GetShipPosition().x << ", y: " << craker.GetShipPosition().y << endl;
	//    			cout << "ball x: " << balls[i].getPosition().x << ", y: " << balls[i].getPosition().y << endl;
	//    			cout << "angle of ball: " << balls[i].getAngle() << endl;
	//    			cout << "awaited angle of ball: " << newAngle << endl;
					if(toCenterShip < 0.0f) //right of center of ship
						newAngle = newAngle + (180.0f - newAngle) * toCenterShip;
					else //left of center of ship
						newAngle = newAngle + (180.0f - newAngle) * toCenterShip;

					balls[i].SetAngle(newAngle);
	//    			cout << "angle of ball: " << balls[i].getAngle() << endl;
					balls[i].SetPosition({balls[i].GetPosition().x, craker.GetShipPosition().y - balls[i].GetRadius()});
	//    			cout << "ball x: " << balls[i].getPosition().x << ", y: " << balls[i].getPosition().y << endl;
					balls[i].SetSpeed(5.0f);
					craker.SetSpeed(5.0f);
    			}
    			else
    				balls[i].SetSticky(true);
    		}
    		else
    		{
				//collision with blocks
				for(size_t j = 0; j < blocks.size(); ++j)
				{
//					cout << "b# " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
	        		if(blocks[j].GetLifePoint() <= 0) continue;
//					cout << "ball x: " << (balls[i].getPosition().x) << endl;
//					cout << "ball y: " << (balls[i].getPosition().y) << endl;
					if((balls[i].GetPosition().y - balls[i].GetRadius()) < (blocks[j].GetPosition().y + blocks[j].GetSize().y) && (balls[i].GetPosition().y - balls[i].GetRadius()) > blocks[j].GetPosition().y && (balls[i].GetPosition().x) > blocks[j].GetPosition().x && (balls[i].GetPosition().x) < blocks[j].GetPosition().x + blocks[j].GetSize().x && balls[i].GetAngle() < 180.0f && balls[i].GetAngle() > 0.0f) //bottom
					{
//						cout << "BLOCK #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << " angle: " << balls[i].getAngle() << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						blocks[j].LoseLifePoint(1);
						if(blocks[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(blocks[j], _upgrades);
			    		    sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
			    		    sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							balls[i].SetAngle(360 - balls[i].GetAngle());
							balls[i].SetPosition({balls[i].GetPosition().x, blocks[j].GetPosition().y + blocks[j].GetSize().y + balls[i].GetRadius()});
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
		    		if((balls[i].GetPosition().x - balls[i].GetRadius()) < (blocks[j].GetPosition().x + blocks[j].GetSize().x) && (balls[i].GetPosition().x + balls[i].GetRadius()) > blocks[j].GetPosition().x && (balls[i].GetPosition().y + balls[i].GetRadius()) > blocks[j].GetPosition().y && (balls[i].GetPosition().y - balls[i].GetRadius()) < (blocks[j].GetPosition().y + blocks[j].GetSize().y) && balls[i].GetAngle() < 270.0f && balls[i].GetAngle() > 90.0f) //right
		    		{
//						cout << "BALL #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						blocks[j].LoseLifePoint(1);
						if(blocks[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(blocks[j], _upgrades);
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
							balls[i].SetPosition({blocks[j].GetPosition().x + blocks[j].GetSize().x + balls[i].GetRadius(), balls[i].GetPosition().y});
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
		    		if((balls[i].GetPosition().x + balls[i].GetRadius()) > blocks[j].GetPosition().x && (balls[i].GetPosition().x + balls[i].GetRadius()) < (blocks[j].GetPosition().x + blocks[j].GetSize().x) && (balls[i].GetPosition().y + balls[i].GetRadius()) > blocks[j].GetPosition().y && (balls[i].GetPosition().y - balls[i].GetRadius()) < (blocks[j].GetPosition().y + blocks[j].GetSize().y) && ((balls[i].GetAngle() < 270.0f && balls[i].GetAngle() > 360.0f) || (balls[i].GetAngle() < 90.0f && balls[i].GetAngle() > 0.0f))) //left
		    		{
//						cout << "BALL #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						blocks[j].LoseLifePoint(1);
						if(blocks[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(blocks[j], _upgrades);
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
							balls[i].SetPosition({blocks[j].GetPosition().x - balls[i].GetRadius(), balls[i].GetPosition().y});
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
					if((balls[i].GetPosition().y + balls[i].GetRadius()) > blocks[j].GetPosition().y && (balls[i].GetPosition().y + balls[i].GetRadius()) < (blocks[j].GetPosition().y + blocks[j].GetSize().y) && (balls[i].GetPosition().x) > blocks[j].GetPosition().x && (balls[i].GetPosition().x) < blocks[j].GetPosition().x + blocks[j].GetSize().x && balls[i].GetAngle() < 360.0f && balls[i].GetAngle() > 180.0f) //top
					{
//						cout << "BLOCK #: " << j << " x: " << blocks[j].getPosition().x << ", b y: " << blocks[j].getPosition().y << " angle: " << balls[i].getAngle() << endl;
						craker.AdjustSpeed(-1.0f);
						balls[i].AdjustSpeed(-1.0f);
						blocks[j].LoseLifePoint(1);
						if(blocks[j].GetLifePoint() == 0)
						{
							_upgrades = craker.DestroyBlock(blocks[j], _upgrades);
							sampler.playSample("blockdestroyed.wav");
			    		    --blocksLeftToWin;
						}
						else
							sampler.playSample("ballhit.wav");
						if(craker.GetUpgrade().GetType() != 0)
						{
							balls[i].SetAngle(360 - balls[i].GetAngle());
							balls[i].SetPosition({balls[i].GetPosition().x, blocks[j].GetPosition().y - balls[i].GetRadius()});
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
		cout << "destroy " << toDestroy.size() << endl;
		for(int i = {}; i < toDestroy.size(); ++i)
			_upgrades.erase(_upgrades.begin() + toDestroy[i]);

    	cout << blocksLeftToWin << endl;
    	if(blocksLeftToWin == 0)
    	{
    		jukebox.playSongPath("victory/Arkanoid Piano Victory Theme.mp3");
    		blocksLeftToWin = -1;
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

        	for(size_t i = 0; i < blocks.size(); ++i)
        	{
        		blocks[i].Draw();
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
    		DrawText(std::__cxx11::to_string(_score).c_str(), SCREEN_WIDTH - PLAYSCREEN_MARGIN * 2.0f, 6.0f, 12.0f, WHITE);
    		DrawText("x", SCREEN_WIDTH - 50.0f - PLAYSCREEN_MARGIN * 2.0f, 6.0f, 12.0f, WHITE);
    		DrawText(std::__cxx11::to_string(int((hitInARow / scoreMultiplierThreshold) + 1)).c_str(), SCREEN_WIDTH - 40.0f - PLAYSCREEN_MARGIN * 2.0f, 6.0f, 12.0f, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
