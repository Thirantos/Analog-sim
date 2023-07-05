#include <iostream>
#include "include/raylib.h"
#include "include/raygui.h"
#include "component.h"


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


        for(Part* part: partsList){
            //part->onUse();
            part->draw();
        }
        for(Part* part: partsInput){
            //part->onUse();
            part->onUse();
        }

        EndDrawing();

    }
    return 1;




}

int main(){
    Dial dial1(0, 0, 0);
    Dial dial2(100, 0, 0);
    Plus plus1(200, 0, 2);
    Sensor sensor1(0, 100, 1);
    Sensor sensor2(100, 100, 1);
    Sensor sensor3(200, 100, 1);

    for (Part* part : partsInput){
        std::cout << part->name << std::endl;
    }

    dial1.voltage = 0.2f;
    dial2.voltage = 0.5f;
    


    dial1.next(&sensor1, 0);
    dial2.next(&sensor2, 0);
    dial1.next(&plus1, 0);
    dial2.next(&plus1, 1);


    plus1.next(&sensor3, 0);


        
    DrawGui();
    return 0;
    
}
