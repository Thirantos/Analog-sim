//
// Created by thijm on 21/10/2023.
//

#ifndef ANALOGSIM_RECTANGLE_H
#define ANALOGSIM_RECTANGLE_H
#include "include/raymath.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

#if _WIN32
#include <imgui_impl_opengl3.h>
#else
#include <imgui_impl_metal.h>
#endif

struct camera{
    float x;
    float y;
    float zoom;

};

struct Rectangle{
    float x;
    float y;
    float width;
    float height;

};

Vector2 getMousePosition(GLFWwindow *window);

Vector2 camToWorld(Vector2 point, camera relative);

Vector2 worldToCam(Vector2 point, camera relative);

bool CheckCollisionPointRec(Vector2 point, Rectangle rect);



#endif //ANALOGSIM_RECTANGLE_H
