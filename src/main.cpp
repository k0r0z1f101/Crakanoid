#include "raylib.h"
#include "crakanoid.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <experimental/filesystem>

using namespace crakanoid;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;
using std::experimental::filesystem::directory_iterator;

const string PATH = "../resources/";
const auto DIR = directory_iterator(PATH);

void randomSong(vector<string>& songPlayedOnce, vector<string>& songPaths)
{
	songPaths = {};
	for(const auto & file : DIR)
	{
		cout << file.path() << endl;
		auto teststr = std::find(songPlayedOnce.begin(), songPlayedOnce.end(), file.path());
		if(teststr != std::end(songPlayedOnce))
		{
			cout << "In there!" << endl;
		}
		else
		{
			songPaths.push_back(file.path());
		}
//		if(std::find(songPlayedOnce.begin(), songPlayedOnce.end(), file.path()))
//		{
//			songPaths.push_back(file.path());
//		}
	}
}

int main(void)
{
	srand(time(0));

	vector<string> songPlayedOnce{};
	vector<string> songPaths{};
//	randomSong(&songPlayedOnce, &songPaths);
//	vector<string> songPaths{};

	for(const auto & file : DIR)
	{
		cout << file.path() << endl;
		auto teststr = std::find(songPlayedOnce.begin(), songPlayedOnce.end(), file.path());
		if(teststr != std::end(songPlayedOnce))
		{
			cout << "In there!" << endl;
		}
		else
		{
			songPaths.push_back(file.path());
		}
//		if(std::find(songPlayedOnce.begin(), songPlayedOnce.end(), file.path()))
//		{
//			songPaths.push_back(file.path());
//		}
	}

	cout << songPaths.size() << endl;
	cout << songPlayedOnce.size() << endl;

	vector<string> t = { "trtr" , "sdfsdf" };

	int randNumber = rand() % songPaths.size();
	cout << "rand: " << randNumber << endl;
	cout << "song path: " << songPaths[1] << endl;

//	const int randomSong = rand() % songPaths.size();

	string songPlayPath = songPaths[randNumber];
	songPlayedOnce.push_back(songPaths[randNumber]);
	cout << songPlayedOnce.size() << endl;

	cout << "song played: " << songPlayPath << endl;


    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Crakanoid");

    InitAudioDevice();              // Initialize audio device


    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    int n = songPlayPath.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, songPlayPath.c_str());

    Music songPlayed = LoadMusicStream(char_array);
    PlayMusicStream(songPlayed);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(songPlayed);   // Update music buffer with new stream data


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        	ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
