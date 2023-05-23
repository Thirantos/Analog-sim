//#include "include/raygui.h"
//#include "include/raylib.h"
#include <iostream>
#include <vector>
#include <string>

class Part;
class Port;
std::vector<Part*> parts;
std::vector<Part*> partsInput;
std::vector<Port*> ports;

class Port{
public:
    Part* next;
    int port;
    Part* prev;

    Port(Part* next, int port, Part* prev){
        this->next = next;
        this->port = port;
        this->prev = prev;
        ports.push_back(this);
    }
};


class Part{
public:
    char* name;
    std::vector<float> input;

    Vector2 position;
    Vector2 mousepos;
    int _ports;

    Rectangle bounds;
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;

    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;

    virtual void onUse(){}

    Part() = default;

    Part(int x, int y, int ports){
        
    }

    void next(Part* part, int port){
        new Port(part, port, this);
    }

    void Output(Part* self, float value){
        
        for (Port* port : ports){
            if(port->prev != self){continue;}
            
            port->next->input.insert(port->next->input.begin() + port->port, value);
            std::cout << port->prev->name << "-->" << value << "-->" << port->next->name << port->next->input[0] << std::endl;
            port->next->onUse();
        }
        
    }
    int draw();

};


class Dial : public Part{
public:
    float voltage;
    using Part::Part;

    Dial(int x, int y, int ports){
        name = "Dial";
        

        parts.push_back(this);
        partsInput.push_back(this);
        this->position.x = x;
        this->position.y = y;
        this->_ports = ports;
        bounds.x = position.x;
        bounds.y = position.y;
        bounds.width = 200;
        bounds.height = 75;
    }

    void onUse() override {
        Output(this, voltage);
    }

    void set(float voltage) {
       
        
        input.push_back(float(voltage));
    }
};

class Sensor : public Part{
public:
    using Part::Part;

    Sensor(int x, int y, int ports){
        
        name = "Sensor";

        parts.push_back(this);
        this->position.x = x;
        this->position.y = y;
        this->_ports = ports;
        bounds.x = position.x;
        bounds.y = position.y;
        bounds.width = 200;
        bounds.height = 75;
    }


    void onUse() override {
        std::string str = "";
        for (float val : input) {
            str += std::to_string(val) + " ";
        }
        /*
        str = "sensor: "+ str;
        name = const_cast<char*>(str.c_str());
        */
    }
};

class Plus : public Part{
public:
    using Part::Part;
    Plus(int x, int y, int ports){
        
        name = "Plus";

        parts.push_back(this);
        this->position.x = x;
        this->position.y = y;
        this->_ports = ports;
        bounds.x = position.x;
        bounds.y = position.y;
        bounds.width = 200;
        bounds.height = 75;
    }

    void onUse() override {
        
        float voltage = input[0] + input[1];
        Output(this, voltage);
        

    }
};



int Part::draw(){
    //std::cout << "Drawing";
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;

    dragBounds.height = 25;
    inBounds.width, outBounds.width = bounds.width/2;
    inBounds.height, outBounds.height = bounds.height;
    outBounds.x = bounds.x + outBounds.width;
    
    if (!isDragging && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

        if(CheckCollisionPointRec(GetMousePosition(), dragBounds)){
            isDragging = true;
        }
        if(CheckCollisionPointRec(GetMousePosition(), outBounds)){
            isDraggingNext = true;
        }
        if(CheckCollisionPointRec(GetMousePosition(), inBounds)){
            isDraggingPrev = true;
        }
    }

    if (isDragging){

        bounds.x += GetMouseDelta().x;
        bounds.y += GetMouseDelta().y;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isDragging = false;
        }

    }

    if (isDraggingNext){
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height/2, GetMouseX(), GetMouseY(), BLACK);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
        
            for(Part* part : parts){
                 if(CheckCollisionPointRec(GetMousePosition(), part->inBounds)){
                    next(part, 0);
                 }
            }
            isDraggingNext = false;
        }
    }

    if (isDraggingPrev){
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
        
            for(Port* port : ports){
                if(port->next != this){continue;}
                 if(CheckCollisionPointRec(GetMousePosition(), port->prev->outBounds)){
                    delete port;
                 }
            }
            isDraggingPrev = false;
        }
    }

    for (Port* port : ports){
            if(port->prev != this){continue;}
            DrawLine(bounds.x + bounds.width, bounds.y + bounds.height/2, port->next->bounds.x, port->next->bounds.y + bounds.height/2, BLACK);
        }

    GuiPanel(bounds, name);
    if(name == "Sensor"){
        if (input.empty()){input.push_back(0.0f);}
        std::string str = std::to_string(input[0]);
        std::cout << str << std::endl;
        char* value = const_cast<char*>(str.c_str());
        std::cout << value << std::endl;
        GuiDrawText( value, bounds, 1, BLACK);
        input.clear();
    }
    

    //GuiPanel(bounds, name);
    return 1;
}

