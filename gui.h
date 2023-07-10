//
// Created by thijm on 05/07/2023.
//

#ifndef ANALOGSIM_GUI_H
#define ANALOGSIM_GUI_H


#include "raylib.h"
#include "component.h"


class gui {
    public:
    int DrawGui();
    const int screenWidth = 800;
    const int screenHeight = 450;
};

class rightClickMenu{
    Vector2 position{};
    Part* partSelected;
    Rectangle rect{};
    Rectangle newRect{};
    Rectangle delRect{};
public:
    rightClickMenu();
    int draw();

};


#endif //ANALOGSIM_GUI_H
