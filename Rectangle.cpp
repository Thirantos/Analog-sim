//
// Created by thijm on 21/10/2023.
//


#include "Rectangle.h"

Vector2 getMousePosition(GLFWwindow *window){
    double *mouseposX;
    double *mouseposY;

    glfwGetCursorPos(window, mouseposX, mouseposY);



    return {static_cast<float>(*mouseposX), static_cast<float>(*mouseposY)};
}

Vector2 camToWorld(Vector2 point, camera relative){
    float dX = point.x - relative.x;
    float dY = point.y - relative.y;

    dX *= relative.zoom;
    dY *= relative.zoom;

    return {.x = dX, .y = dY};

}

Vector2 worldToCam(Vector2 point, camera relative){
    float dX = point.x + relative.x;
    float dY = point.y + relative.y;

    dX /= relative.zoom;
    dY /= relative.zoom;

    return {.x = dX, .y = dY};

}

bool CheckCollisionPointRec(Vector2 point, Rectangle rect){
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;
}