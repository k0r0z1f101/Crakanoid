/*
vcxproj properties setup:
- C/C++ > general > additional include folder > $(SolutionDir)include\raylib; $(SolutionDir)include\
- C/C++ > general > preprocessor > GRAPHICS_API_OPENGL_33; PLATFORM_DESKTOP
- Linker > general > additional Library Directory > $(SolutionDir)Lib\$(Platform)\$(Configuration)\
- Linker > input > additional dependencies > raylib.lib;winmm.lib
*/
#include "raylib.h"
#include "raygui.h"
#include "Code_Utilities_Light.h"
using namespace BdB;

int main()
{
    // Initialisation
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Bdeb - core window");
    //-------------------------------------------------------------
    int boxValue = 0;
    bool boxEditMode = false;

    char textBoxText[64] = "Hello BdeB!";
    bool textBoxEditMode = false;

    GuiLoadStyle("styles/cyber/cyber.rgs");
    //boucle temp réel
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLANK);
            DrawText("Hello BdeB!", 20, 20, 20, YELLOW);
            if (GuiTextBox({ 25, 215, 125, 30 }, textBoxText, 64, textBoxEditMode)) textBoxEditMode = !textBoxEditMode;
        }
        EndDrawing();
    }

    // libération
    CloseWindow();
    //--------------------------------------------------------------
}
