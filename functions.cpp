//
// Created by thijm on 21/10/2023.
//



#include "functions.h"
#define NANOVG_GL3_IMPLEMENTATION	// Use GL3 implementation.
#include <GL/glext.h>
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>

struct NVGcontext* NVGcontextGL3 = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
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

bool CheckCollisionPointRec(Vector2 point, struct Rectangle rect){
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;
}

void drawRectangle(struct Rectangle rect, Vector3 colour) {


    glColor3ub(int(colour.x), int(colour.y), int(colour.z));

    glRectf(rect.x ,rect.y, rect.x + rect.width, rect.y + rect.height);

}

void drawRectangleLines(struct Rectangle rect, float thickness, Vector3 colour) {
    glColor3ub(int(colour.x), int(colour.y), int(colour.z));

    glBegin(GL_LINE_LOOP);

    glVertex2f(rect.x, rect.y);
    glVertex2f(rect.x + rect.width, rect.y);
    glVertex2f(rect.x + rect.width, rect.y + rect.height);
    glVertex2f(rect.x, rect.y + rect.height);

    glEnd();


}

void drawCircle(Vector2 position, float radius, Vector3 colour) {
    glColor3ub(int(colour.x), int(colour.y), int(colour.z));

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(position.x, position.y);
    int resolution = 16;

    for (int i = 0; i < resolution; ++i) {

        float offset = 2*PI/resolution * i;

        glVertex2f(position.x + radius * cos(offset), position.y + radius * sin(offset));
    }


    glEnd();
}

void drawText(std::string text, Vector2 position, int fontsize, Vector3 colour) {
    nvgText(NVGcontextGL3, position.x, position.y, text.c_str(), reinterpret_cast<const char *>('\n'));
}

