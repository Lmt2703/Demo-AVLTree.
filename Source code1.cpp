#include "raylib.h"
#include "Application.h"

const int screenWidth = 2000;
const int screenHeight = 1000;

int main()
{
    InitWindow(screenWidth, screenHeight, "AVL Tree Visualization");
    SetTargetFPS(60);

    Application app(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        app.Update();

        BeginDrawing();
        app.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
