//#include "include/raygui.h"
//#include "include/raylib.h"
#include <iostream>
#include <vector>
#include <string>

class Part;

class Component{
public:
    Vector2 position;
    Vector2 mousepos;
    Part* part;
    int ports;

    Rectangle bounds;
    bool isDragging = false;

    Component(int x, int y, Part* part, int ports);

    int draw();    

};

class Port{
public:
    Component* comp;
    int port;

    Port(Component* comp, int port){
        this->comp = comp;
        this->port = port;
    }
};

class Part{
public:
    const char* name;
    std::vector<float> input;
    std::vector<Port> output;

    virtual void onUse(){}

    void next(Component* comp, int port){
        Port p(comp, port);
        output.push_back(p);
    }

    void Output(float value){
        for (Port port : output){
            port.comp->part->input.insert(port.comp->part->input.begin() + port.port, value);
            port.comp->part->onUse();
        }
    }

};



class Dial : public Part{
public:
    float voltage;

    Dial(){
        name = "Dial";
    }

    void onUse() override {
        Output(voltage);
    }
};

class Sensor : public Part{
public:


    Sensor(){
        name = "Sensor";
    }

    void onUse() override {
        std::string str;
        for (float val : input) {
            str += std::to_string(val) + " ";
        }
        std::cout << str << "\n";
    }
};

class Plus : public Part{
public:
    Plus(){
        name = "Plus";
    }

    void onUse() override {
        if(input.size() != 2){return;}
        float voltage = input[0] + input[1];

        Output(voltage);

    }
};


std::vector<Component*> components;


Component::Component(int x, int y, Part* part, int ports){
    this->position.x = x;
    this->position.y = y;
    this->part = part;
    this->ports = ports;
    components.push_back(this);
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
}


int Component::draw(){
    if (!isDragging && CheckCollisionPointRec(GetMousePosition(), bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        isDragging = true;
    }
    if (isDragging){
        bounds.x += GetMouseDelta().x;
        bounds.y += GetMouseDelta().y;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isDragging = false;
        }
    }
    GuiPanel(bounds, part->name);
}