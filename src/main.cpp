#include "raylib.h"
#include "crakanoid.h"
#include "sound.h"

using namespace crakanoid;
using namespace sound;

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

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
    	jukebox.updateStream();
    	if(!jukebox.isSongPlaying())
    	{
    		jukebox.randomSongPath();
    		jukebox.playSong();
    	}

    	craker.moveShip();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        	ClearBackground(RAYWHITE);

        	string songName = jukebox.getSongPlaying();
        	DrawText(songName.c_str(), 50, 20, 12, RED);

        	craker.DrawShip();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
