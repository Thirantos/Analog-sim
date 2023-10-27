//
// Created by thijm on 05/07/2023.
//

#include "gui.h"
#include "component.h"
#include <ranges>
#include <iostream>
#include <raylib.h>

#include "parts.h"
#include <nfd.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <rlImGui.h>
#include <raymath.h>


#warning "here are more classes added"


float min(float a, float b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}


Rectangle selection;


std::vector<part*> selectedParts;
Vector2 selection1;
Vector2 selection2;

int gui::DrawGui() {


    init();


    while (!WindowShouldClose()) {
        Vector2 MousePos = GetMousePosition();

        dragSelection();


        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyDown(KEY_S)) {
                save();
            }
            if (IsKeyDown(KEY_O)) {
                load();
            }
        }

        BeginDrawing();
        rlImGuiBegin();

        mouseMove();


        MousePos.x += GetMouseDelta().x;
        MousePos.y += GetMouseDelta().y;

        ClearBackground(RAYWHITE);

        std::cout << mouseMode << std::endl;

        updateParts();


        dragSelection();


        imGuiMainMenu();

        rlImGuiEnd();
        EndDrawing();


    }


    rlImGuiShutdown();
    CloseWindow();
    return 1;

}


void gui::imGuiMainMenu() {

    ImGui::SetNextWindowSize(ImVec2(400, GetScreenHeight() -20));
    ImGui::SetNextWindowPos(ImVec2(10, 10));


    ImGui::Begin("main menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoResize);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { load(); }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { save(); }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    const char* components[] = {
        "areaPolygon",
        "average",
        "dial",
        "dotProduct",
        "normalizePolygon",
        "plus",
        "sensor",
    };
    static const char* current_item = NULL;
    if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(components); n++)
        {
            bool is_selected = (current_item == components[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(components[n], is_selected))
                current_item = components[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    if(ImGui::Button("add") && current_item != NULL)auto* p = constructorFromName(current_item, camera.target.x + GetScreenWidth() / 2 - 100, camera.target.y + GetScreenHeight() / 2 - 75);


    ImGui::BeginChild("Scrolling", ImVec2(150, 0), true);
        std::vector<part*> sortedParts = partsList;
        std::sort(sortedParts.begin(), sortedParts.end());

        for (part* p: sortedParts) {
            bool selected = false;
            if (std::find(selectedParts.begin(), selectedParts.end(),p) != selectedParts.end()){
                selected = true;
            }

            if(ImGui::Selectable(p->name == NULL? "loading.." : p->name, selected)){
                selectedParts.push_back(p);
            }
        }
    ImGui::EndChild();





    ImGui::End();

}

void gui::dragSelection(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseMode == none) {
        mouseMode = selectingMultiple;


        selection1.x = GetMouseX();
        selection1.y = GetMouseY();
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouseMode == selectingMultiple){
        selection2.x = GetMouseX();
        selection2.y = GetMouseY();

        selection = {
                .x = min(selection1.x, selection2.x),.y= min(selection1.y, selection2.y),
                .width= abs(selection1.x- selection2.x),.height=  abs(selection1.y- selection2.y)
        };


        DrawRectangleRec(selection, {75,75,128,100});
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mouseMode == selectingMultiple){
        mouseMode = none;
        selectedParts.clear();

        for (part* p: partsList) {
            if (CheckCollisionRecs(selection, p->bounds)) selectedParts.push_back(p);
        }

        //selection.x = 0.0;
        //selection.y = 0.0;
        //selection.width = 0.0;
        //selection.height = 0.0;
    }
}

void gui::init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "AnalogSim");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    rlImGuiSetup(true);

    camera.target = (Vector2) {0, 0};
    camera.offset = (Vector2) {0, 0};
    camera.zoom = 1.0f;
    camera.rotation = 0;
}

int gui::save() {


    NFD_Init();

    nfdchar_t *outPath;

    nfdfilteritem_t filterItem[1] = {{"Analogsim file", "analogsim"}};
    nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, NULL, "save.analogsim");
    if (result == NFD_OKAY) {
        serializer->serialize(outPath);
        NFD_FreePath(outPath);
        NFD_Quit();
        return 0;
    } else if (result == NFD_CANCEL) {return 1;
    } else {
        printf("Error: %s\n", NFD_GetError());
        return 1;
    }


}

int gui::load() {


    NFD_Init();
    nfdchar_t *outPath;

    nfdfilteritem_t filterItem[1] = {{"Analogsim file", "analogsim"}};
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
    if (result == NFD_OKAY) {
        serializer->deserialize(outPath);
        NFD_FreePath(outPath);
        NFD_Quit();
        return 0;
    } else if (result == NFD_CANCEL) {
        return 1;
    } else {
        printf("Error: %s\n", NFD_GetError());
        return 1;
    }


}

void gui::updateParts() {


    for (part* part: std::ranges::views::reverse(partsList)) {
        //part->onUse();

        part->drag(camera);

    }


    tempPartsProcess = partsInput;
    for (part *part: partsProcess) {
        if (partsProcess.empty()) break;
        part->onUse();
    }
    partsProcess.clear();
    partsProcess = tempPartsProcess;
    tempPartsProcess.clear();

    BeginMode2D(camera);

    for (part* part: partsList) {
        if (part->bounds.height == 0) delete part;
        part->drawPorts(camera);

    }
    for(part* part: selectedParts){
        Rectangle b = part->bounds;
        int out = 7;
        b.width += 2 * out;
        b.height += 2 * out;
        b.x -= out;
        b.y -= out;
        DrawRectangleRec(b, {75,75,128,100});
    }

    for (part* part: partsList) {
        //part->onUse();
        if (part->bounds.height == 0)  delete part;
        part->draw(camera);
    }

    EndMode2D();

    for (part* part: partsList) {
        if (part->bounds.height == 0) delete part;
        part->drawIgnoreCam(camera);

    }

}

void gui::mouseMove() { // adapted from https://github.com/raylib-extras/examples-c/blob/main/mouse_zoom/mouse_zoom.c
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);

        camera.target = Vector2Add(camera.target, delta);
    }

    auto x = float(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT)) * 5;
    auto y = float(IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)) * 5;
    camera.target = Vector2Add(camera.target, {x, y});


    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        // set the offset to where the mouse is
        camera.offset = GetMousePosition();

        // set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
        camera.target = mouseWorldPos;

        // zoom
        camera.zoom += wheel * 0.125f;
        if (camera.zoom < 0.125f)
            camera.zoom = 0.125f;
    }
}

