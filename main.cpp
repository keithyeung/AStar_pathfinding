#include "raylib.h"
#include "level.h"
#include <ctime>
#include<cstdlib>

// IMPORTANT:
// Feel free to not use the Level, and redo everything on your own. This is just some boilerplate code to get you started.

// If you want, I suggest manually copying my code from scratch. That should help with understanding how it works a bit better.

int main(void)
{    
    srand(time(nullptr));
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    printf("Test %u\n", rand());
    
    SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_VSYNC_HINT | ConfigFlags::FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "The Event Loop of Life");

    // SetTargetFPS(60); // Uncomment this if you want to use fixed framerate (I suggest using vsync)
    // SetExitKey(0);    // Uncomment this to disable ESC as exit key

    Level level;

    level.reset();

    while (!WindowShouldClose())
    {
        // Update
        level.update();

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        level.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}