//
// Created by thijm on 05/07/2023.
//

#ifndef ANALOGSIM_GUI_H
#define ANALOGSIM_GUI_H

#include "raylib.h"
#include "component.h"
#include "serializer.h"

class gui {
    public:
    int DrawGui();
    const int screenWidth = 800;
    const int screenHeight = 450;
    serializer* serializer;
    Camera2D camera;
    void mouseMove();
};

class rightClickMenu{

    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    Vector2 position{};
    rightClickMenu(Camera2D camera);

    int draw(Camera2D camera);


};

class partSelector{
    Vector2 position{};
    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    partSelector();
    int draw(Camera2D camera);

};


#endif //ANALOGSIM_GUI_H
