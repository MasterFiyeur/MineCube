/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <cstdlib>
#include <ctime>

#include "classes/Game.h"


int main()
{
	std::srand(std::time(nullptr));
    const int screenWidth = 960;
    const int screenHeight = 540;
    InitWindow(screenWidth, screenHeight, "Raylib tests");

	Game game;
    game.start();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}