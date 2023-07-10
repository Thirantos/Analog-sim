//
// Created by thijm on 05/07/2023.
//

#include "gui.h"
#include "include/raylib.h"
#define RAYLIB_H
#define RAYGUI_IMPLEMENTATION
#include "component.h"
#include <ranges>
#include <iostream>
#include "include/raygui.h"
#include "component.h"


rightClickMenu* RCM;
partSelector* PSEL;

int gui::DrawGui() {



    // GuiLoadStyleDefault();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "AnalogSim");
    SetTargetFPS(60);

    for(Part* part: partsList){
        part->updateBounds();

    }



    while (!WindowShouldClose()){
        Vector2 MousePos = GetMousePosition();
        mouseDragging = false;

        for(Part* part: std::ranges::views::reverse(partsList)){
            //part->onUse();

            part->drag();

        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            RCM = new class rightClickMenu();
        }

        BeginDrawing();






        MousePos.x += GetMouseDelta().x;
        MousePos.y += GetMouseDelta().y;

        //Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        //Color colour = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));


        ClearBackground(RAYWHITE);

        for(Part* part: partsList){

            part->drawPorts();

        }

        for(Part* part: partsList){
            //part->onUse();
            part->draw();

        }

        for(Part* part: partsInput){
            //part->onUse();
            part->onUse();
        }
        if(RCM != nullptr) {
            RCM->draw();
        }

        if(PSEL != nullptr) {
            PSEL->draw();
        }

        EndDrawing();

    }
    return 1;




}

rightClickMenu::rightClickMenu(){
    position = GetMousePosition();
    partSelected == nullptr;
    for(Part* part: std::ranges::views::reverse(partsList)){

        if(CheckCollisionPointRec( GetMousePosition(),part->bounds)){
            partSelected = part;

        }

    }
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 75;
    rect.height = 70;

    newRect = delRect = rect;
    newRect.height = delRect.height = 35;
    delRect.y += newRect.height;

}

partSelector::partSelector(){
    position = RCM->position;
    position.x += 75;

    partSelected == nullptr;
    for(Part* part: std::ranges::views::reverse(partsList)){

        if(CheckCollisionPointRec( GetMousePosition(),part->bounds)){
            partSelected = part;

        }

    }
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 75;
    rect.height = 70;



    newRect = delRect = rect;
    newRect.height = delRect.height = 35;
    delRect.y += newRect.height;

}

int partSelector::draw() {

    Rectangle dialRect;
    Rectangle plusRect;
    Rectangle sensorRect;

    dialRect = plusRect = sensorRect = newRect;

    plusRect.y += newRect.height;
    sensorRect.y += 2*newRect.height;


    rect.height = plusRect.height + dialRect.height + sensorRect.height;

    if (GuiButton(dialRect,"Dial")){
        new Dial(GetMouseX(), GetMouseY(), 0);
        PSEL = nullptr;
        delete this;
    }
    if (GuiButton(plusRect,"Plus")){
        new Plus(GetMouseX(), GetMouseY(), 2);
        PSEL = nullptr;
        delete this;
    }
    if (GuiButton(sensorRect,"Sensor")){
        new Sensor(GetMouseX(), GetMouseY(), 1);
        PSEL = nullptr;
        delete this;
    }

    if(!CheckCollisionPointRec(GetMousePosition(), rect)&& IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        PSEL = nullptr;
        delete this;
    }
    return 0;
}


int rightClickMenu::draw() {
    if (GuiButton(newRect,"new")){
        PSEL = new partSelector();
        RCM = nullptr;
        delete this;

    }

    if (GuiButton(delRect,"Crash (delete)")){
        partSelected->kill();
        partSelected = nullptr;
        RCM = nullptr;
        delete this;
    }

    if(!CheckCollisionPointRec(GetMousePosition(), rect)&& IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        RCM = nullptr;
        delete this;
    }
    return 0;
}
