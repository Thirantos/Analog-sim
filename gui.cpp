//
// Created by thijm on 05/07/2023.
//

#include "gui.h"
#include "component.h"
#include <ranges>
#include <iostream>
#include "include/raylib.h"
#define RAYLIB_H
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#include "parts.h"

#warning "here are more classes added"

#include "raymath.h"

#define BUTTON(part) \
    Rectangle button_##part = buttonRect; \
    if (GuiButton(button_##part,#part)){  \
        Vector2 pos = GetScreenToWorld2D(GetMousePosition(), camera);             \
        new part(pos.x, pos.y);\
        PSEL = nullptr;  \
        delete this;     \
    }                    \
    buttonRect.y += buttonRect.height;




rightClickMenu* RCM;
partSelector* PSEL = nullptr;

int gui::DrawGui() {



    // GuiLoadStyleDefault();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "AnalogSim");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    for(part* part: partsList){
        part->postInitialize();

    }

    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){0,0};
    camera.zoom = 1.0f;
    camera.rotation = 0;


    while (!WindowShouldClose()){
        Vector2 MousePos = GetMousePosition();
        mouseDragging = false;

        for(part* part: std::ranges::views::reverse(partsList)){
            //part->onUse();

            part->drag(camera);

        }

        tempPartsProcess = partsInput;
        for(part* part: partsProcess){
            if(partsProcess.empty()) break;
            part->onUse();
        }
        partsProcess.clear();
        partsProcess = tempPartsProcess;
        tempPartsProcess.clear();

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            RCM = new rightClickMenu(camera);
        }



        BeginDrawing();

        mouseMove();


        BeginMode2D(camera);


        MousePos.x += GetMouseDelta().x;
        MousePos.y += GetMouseDelta().y;

        //Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        //Color colour = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));


        ClearBackground(RAYWHITE);

        for(part* part: partsList){

            part->drawPorts(camera);

        }

        for(part* part: partsList){
            //part->onUse();
            part->draw(camera);

        }



        EndMode2D();

        for(part* part: partsList){

            part->drawIgnoreCam(camera);

        }



        if(RCM != nullptr) {
            RCM->draw(camera);
        }

        if(PSEL != nullptr) {
            PSEL->draw(camera);
        }


        if(GuiButton( Rectangle{0,0,200,100}, "save" )){
            serializer->serialize("./save.json");

        }
        if(GuiButton( Rectangle{200,0,200,100}, "load" )){
            serializer->deserialize("./save.json");

        }


        EndDrawing();


    }
    return 1;




}

rightClickMenu::rightClickMenu(Camera2D camera){
    position = GetMousePosition();
    for(part* part: std::ranges::views::reverse(partsList)){

        if(CheckCollisionPointRec( GetScreenToWorld2D(GetMousePosition(), camera),part->bounds)){
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

int partSelector::draw(Camera2D camera) {

    Rectangle buttonRect;

    buttonRect = newRect;


    BUTTON(dial)
    BUTTON(plus)
    BUTTON(sensor)
    BUTTON(average)
    BUTTON(normalizePolygonA)
    BUTTON(normalizePolygonB)
    BUTTON(normalizePolygonC)
#
#warning "here are more classes added"

    rect.height = buttonRect.y - rect.y;




    if(!CheckCollisionPointRec(GetMousePosition(), rect)&& IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        PSEL = nullptr;
        delete this;
    }
    return 0;
}

int rightClickMenu::draw(Camera2D camera) {
    if (GuiButton(newRect,"new")){
        PSEL = new partSelector();
        RCM = nullptr;
        delete this;

    }
    if(partSelected != nullptr) {
        if (GuiButton(delRect, "delete")) {
            delete partSelected;
            partSelected = nullptr;
            RCM = nullptr;
            delete this;
        }
    }

    if(!CheckCollisionPointRec(GetMousePosition(), rect)&& IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        RCM = nullptr;
        delete this;
    }
    return 0;
}

void gui::mouseMove(){ // adapted from https://github.com/raylib-extras/examples-c/blob/main/mouse_zoom/mouse_zoom.c
    if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);

        camera.target = Vector2Add(camera.target, delta);
    }


    float wheel = GetMouseWheelMove();
    if(wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // set the offset to where the mouse is
        camera.offset = GetMousePosition();

        // set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
        camera.target = mouseWorldPos;

        // zoom
        camera.zoom += wheel*0.125f;
        if (camera.zoom < 0.125f)
            camera.zoom = 0.125f;
    }
}

