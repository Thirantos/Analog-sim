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
    int DrawGui() const;
    const int screenWidth = 800;
    const int screenHeight = 450;
    serializer* serializer;
};

class rightClickMenu{

    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    Vector2 position{};
    rightClickMenu();
    int draw();

};

class partSelector{
    Vector2 position{};
    part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    partSelector();
    int draw();

};


#endif //ANALOGSIM_GUI_H
