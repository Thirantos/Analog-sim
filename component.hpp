#include "include/raygui.h"
#include "include/raylib.h"
//#include "parts.hpp"
#include "gui.hpp"

class component{
public:
    Vector2 position;
    Part part;
    int ports;

    component(int x, int y, Part part, int ports){
        this->position.x = x;
        this->position.y = y;
        this->part = part;
        this->ports = ports;
        components.push_back(this);
    }

    int draw(){
        Rectangle bounds;
        bounds.x = position.x;
        bounds.y = position.y;
        bounds.width = 200;
        bounds.height = 100;
        GuiPanel(bounds, "Hello");
    }

};