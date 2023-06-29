#include "raylib.h"
#include "level.h"
#include <ctime>
#include<cstdlib>

int main(void)
{    
    srand(time(nullptr));
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    printf("Test %u\n", rand());
    
    SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE | ConfigFlags::FLAG_VSYNC_HINT | ConfigFlags::FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "The Event Loop of Life");

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
