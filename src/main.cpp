#include "raylib.h"
#include "crakanoid.h"

using namespace crakanoid;

int main(void)
{
	srand(time(0));

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Crakanoid");

    InitAudioDevice();              // Initialize audio device
    SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);

    //convert string to char* and play the song
	vector<string> songPlayedOnce{};
    string songPlayPath = randomSong(songPlayedOnce);
    int n = songPlayPath.length();
    char char_array[n + 1];
    strcpy(char_array, songPlayPath.c_str());
    cout << "char: " << char_array << endl;
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
