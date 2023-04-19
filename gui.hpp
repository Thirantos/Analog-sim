#include "include/raylib.h"
#include "include/raygui.h"




int drawGui(void){


    const int screenWidth = 800;
    const int screenHeight = 450;

    // GuiLoadStyleDefault();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "AnalogSim");

    SetTargetFPS(20);

    while (!WindowShouldClose()){
        BeginDrawing();

        Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        Color col2 = {255, 0, 255, 255};

        ClearBackground(BackGroundColour);

        DrawCircle(400, 200, 10, col2);

        

        EndDrawing();
    }

    return 0;


}