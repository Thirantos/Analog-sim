#include "raylib.h"
#include "raygui.h"




int gui(void){


    const int screenWidth = 800;
    const int screenHeight = 450;

    GuiLoadStyleDefault();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "AnalogSim");

    SetTargetFPS(20);

    while (!WindowShouldClose()){
        BeginDrawing();

        Color Bg = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        Color col2 = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));

        ClearBackground(Bg);

        DrawCircle(400, 200, 10, col2);

        EndDrawing();
    }

    return 0;


}