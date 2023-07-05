#include "include/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#include "component.hpp"

    int DrawGui(){

        const int screenWidth = 800;
        const int screenHeight = 450;

        // GuiLoadStyleDefault();
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(screenWidth, screenHeight, "AnalogSim");
        SetTargetFPS(24);

        while (!WindowShouldClose()){
            Vector2 MousePos = GetMousePosition();
            BeginDrawing();
            MousePos.x += GetMouseDelta().x;
            MousePos.y += GetMouseDelta().y;

            Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
            Color colour = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));


            ClearBackground(BackGroundColour);

        
            for(Part* part: parts){
                //part->onUse();
                part->draw();
                part->drag();
            }
            for(Part* part: partsInput){
                //part->onUse();
                part->onUse();
            }
            
            EndDrawing();
            
        }

        


    }
