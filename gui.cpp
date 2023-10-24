//
// Created by thijm on 05/07/2023.
//

#include "gui.h"
#include "component.h"
#include <ranges>
#include <iostream>


#include "parts.h"
#include <nfd.h>


#warning "here are more classes added"



#define BUTTON(part)  // todo: redo
//    Rectangle button_##part = buttonRect; \
//    if (GuiButton(button_##part,#part)){  \
//        Vector2 pos = camToWorld(getMousePosition(window), camera);             \
//        new part(pos.x, pos.y);\
//        PSEL = nullptr;  \
//        delete this;     \
//    }                    \
//    buttonRect.y += buttonRect.height;


rightClickMenu *RCM;
partSelector *PSEL = nullptr;



int gui::DrawGui() {

    GLFWwindow *window;

    if (!glfwInit())
        exit(-1);

    window = glfwCreateWindow(640, 480, "Analogsim", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

// Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window,
                                 true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    glfwSetMouseButtonCallback(window, mouse_button_callback);

    for (part *part: partsList) {
        part->postInitialize();

    }

    camera.x = 0;
    camera.y = 0;
    camera.zoom = 1.0f;


    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)




        mouseDragging = false;


        mouseMove(window);




        //Color BackGroundColour = GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
        //Color colour = GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL));



        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)


    }

    return 1;


}

void gui::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {


    //if(action == GLFW_PRESS){
    //    Input.mouseButtons[button] = true;
    //}
    //if(action == GLFW_RELEASE){
    //    Input.mouseButtons[button] = false;
    //}


    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

        //RCM = new rightClickMenu(window, camera);

    }

}


void gui::open() {
    NFD_Init();
    nfdchar_t *outPath;

    nfdfilteritem_t filterItem[1] = {{"Analogsim file", "analogsim"}};
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, nullptr);
    if (result == NFD_OKAY) {
        serializer::deserialize(outPath);
        NFD_FreePath(outPath);
    } else if (result == NFD_CANCEL) {
    } else {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
}

void gui::save() {


    NFD_Init();

    nfdchar_t *outPath;

    nfdfilteritem_t filterItem[1] = {{"Analogsim file", "analogsim"}};
    nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, nullptr, "save.analogsim");
    if (result == NFD_OKAY) {
        serializer::serialize(outPath);
        NFD_FreePath(outPath);
    } else if (result == NFD_CANCEL) {
    } else {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();


}

void gui::updateParts() {

    tempPartsProcess = partsInput;
    for (part *part: partsProcess) {
        if (partsProcess.empty()) break;
        part->onUse();
    }
    partsProcess.clear();
    partsProcess = tempPartsProcess;
    tempPartsProcess.clear();

    for (part *part: std::ranges::views::reverse(partsList)) {
        //part->onUse();

        //part->drag(camera);

    }

    for (part *part: partsList) {
        if (part->bounds.height == 0) delete part;
        //part->drawPorts(camera);

    }

    for (part *part: partsList) {
        //part->onUse();
        if (part->bounds.height == 0) delete part;
        //part->draw(camera);

    }

    for (part *part: partsList) {
        if (part->bounds.height == 0) delete part;
        part->drawIgnoreCam(camera);

    }

    if (RCM != nullptr) {
        RCM->draw(window, camera);
    }

    if (PSEL != nullptr) {
        PSEL->draw(window, camera);
    }


}


rightClickMenu::rightClickMenu(GLFWwindow *window, camera camera) {
    position = getMousePosition(window);
    for (part *part: std::ranges::views::reverse(partsList)) {

        // todo: check mouse position
        //if (CheckCollisionPointRec(GetScreenToWorld2D(getMousePosition(window), camera), part->bounds)) {
        //    partSelected = part;

        //}

    }
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 75;
    rect.height = 70;

    newRect = delRect = rect;
    newRect.height = delRect.height = 35;
    delRect.y += newRect.height;

}

partSelector::partSelector(GLFWwindow *window) {
    position = RCM->position;
    position.x += 75;

    for (part *part: std::ranges::views::reverse(partsList)) {

        if (CheckCollisionPointRec(getMousePosition(window), part->bounds)) {
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

int partSelector::draw(GLFWwindow *window, camera camera) {

    Rectangle buttonRect;

    buttonRect = newRect;


    BUTTON(dial)
    BUTTON(plus)
    BUTTON(sensor)
    BUTTON(average)
    BUTTON(normalizePolygonA)
    BUTTON(normalizePolygonB)
    BUTTON(normalizePolygonC)
    BUTTON(dotProduct)
    BUTTON(areaPolygon)


#warning "here are more classes added"

    rect.height = buttonRect.y - rect.y;


    //if (!CheckCollisionPointRec(getMousePosition(window), rect) && gui::Input.isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
    //    PSEL = nullptr;
    //    delete this;
    //}
    return 0;
}

int rightClickMenu::draw(GLFWwindow *window, camera camera) {
    //if (GuiButton(newRect, "new")) {
        PSEL = new partSelector(window);
        RCM = nullptr;
        delete this;

    //}
    if (partSelected != nullptr) {
        //if (GuiButton(delRect, "delete")) {
            delete partSelected;
            partSelected = nullptr;
            RCM = nullptr;
            delete this;
        //}
    }

    //if (!CheckCollisionPointRec(getMousePosition(window), rect) && gui::Input.isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
    //    RCM = nullptr;
    //    delete this;
    //}
    return 0;
}



//todo: redo
void gui::mouseMove(GLFWwindow *window) const { // adapted from https://github.com/raylib-extras/examples-c/blob/main/mouse_zoom/mouse_zoom.c
    //if (Input.isMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE)) {
//
    //    Vector2 delta = Vector2Subtract(oldMousePos ,getMousePosition(window));
    //    delta = Vector2Scale(delta, -1.0f / camera.zoom);
//
    //    camera.x += delta.x;
    //    camera.y += delta.y;
//
    //}
//todo: revamp
    //auto x = float(IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT)) * 5;
    //auto y = float(IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP)) * 5;
    //camera.target = Vector2Add(camera.target, {x, y});


    //float wheel = GetMouseWheelMove();
    //if (wheel != 0) {
    //    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
//
    //    // set the offset to where the mouse is
    //    camera.offset = GetMousePosition();
//
    //    // set the target to match, so that the camera maps the world space point under the cursor to the screen space point under the cursor at any zoom
    //    camera.target = mouseWorldPos;
//
    //    // zoom
    //    camera.zoom += wheel * 0.125f;
    //    if (camera.zoom < 0.125f)
    //        camera.zoom = 0.125f;
    //}
}



