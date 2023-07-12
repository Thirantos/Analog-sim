//
// Created by thijm on 05/07/2023.
//

#include "gui.h"
#include "component.h"
#include <ranges>
#include "include/raylib.h"
#define RAYLIB_H
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#include "parts/dial.h"
#include "parts/sensor.h"
#include "parts/plus.h"

#define BUTTON(part) \
Rectangle button_##part = buttonRect; \
if (GuiButton(button_##part,#part)){  \
    new part(GetMouseX(), GetMouseY(), 1);\
    PSEL = nullptr;  \
    delete this;     \
}                    \
buttonRect.y += buttonRect.height;
#warning "ID NOT IMPLEMENTED"




rightClickMenu* RCM;
partSelector* PSEL;

int gui::DrawGui() const {



    // GuiLoadStyleDefault();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "AnalogSim");
    SetTargetFPS(60);

    for(part* part: partsList){
        part->updateBounds();

    }



    while (!WindowShouldClose()){
        Vector2 MousePos = GetMousePosition();
        mouseDragging = false;

        for(part* part: std::ranges::views::reverse(partsList)){
            //part->onUse();

            part->drag();

        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            RCM = new class rightClickMenu();
        }



        BeginDrawing();


        if(GuiButton( Rectangle{0,0,200,100}, "save" )){
            serializer->serialize();

        }



        MousePos.x += GetMouseDelta().x;
        MousePos.y += GetMouseDelta().y;

        //Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        //Color colour = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));


        ClearBackground(RAYWHITE);

        for(part* part: partsList){

            part->drawPorts();

        }

        for(part* part: partsList){
            //part->onUse();
            part->draw();

        }

        partsProcess.clear();
        partsProcess = partsInput;
        partsProcess.insert(partsProcess.end(), tempPartsProcess.begin(), tempPartsProcess.end());
        tempPartsProcess.clear();
        for(part* part: partsProcess){
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
    for(part* part: std::ranges::views::reverse(partsList)){

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

    for(part* part: std::ranges::views::reverse(partsList)){

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

    Rectangle buttonRect;

    buttonRect = newRect;


    BUTTON(dial);
    BUTTON(plus)
    BUTTON(sensor)


    rect.height = buttonRect.y - rect.y;




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

    if (GuiButton(delRect,"delete")){
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
