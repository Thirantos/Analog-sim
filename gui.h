//
// Created by thijm on 05/07/2023.
//

#ifndef ANALOGSIM_GUI_H
#define ANALOGSIM_GUI_H

#include "include/raymath.h"
#include "component.h"
#include "serializer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

#if _WIN32
#include <imgui_impl_opengl3.h>
#else
#include <imgui_impl_opengl3.h>
#include <imgui_impl_metal.h>
#endif
#include "Rectangle.h"


class input{


public:
    bool mouseButtons[8];

    bool isMouseButtonDown(int i){
        return mouseButtons[i];
    }

};

class gui {
    public:
    int DrawGui();
    Vector2 oldMousePos;
    //static input Input;
    GLFWwindow *window{};
    const int screenWidth = 800;
    const int screenHeight = 450;
    serializer* serializer{};
    camera camera;
    void mouseMove(GLFWwindow *window) const;
    static void save() ;
    static void open() ;
    static struct camera* getCamera() ;
    void updateParts();


    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

class rightClickMenu{

    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    Vector2 position{};
    rightClickMenu(GLFWwindow *window, camera camera);

    int draw(GLFWwindow *window, camera camera);


};

class partSelector{
    Vector2 position{};
    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    partSelector(GLFWwindow *window);
    int draw(GLFWwindow *window, camera camera);

};


#endif //ANALOGSIM_GUI_H
