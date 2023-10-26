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
    void init();
    const int screenWidth = 800;
    const int screenHeight = 450;
    serializer* serializer;
    Camera2D camera;
    void mouseMove();
    void imGuiMainMenu();
    int save();
    int load();
    void updateParts();

    void dragSelection();
};






#endif //ANALOGSIM_GUI_H
