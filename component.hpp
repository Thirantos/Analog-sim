//#include "include/raygui.h"
//#include "include/raylib.h"
#include <iostream>
#include <vector>
#include <string>

class Part;
class Port;
std::vector<Part*> parts;
std::vector<Part*> partsInput;
std::vector<Port> ports;

bool insideRect(Rectangle rect, Vector2 point){
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;

}


class Part{
public:
    char* name;
    std::vector<float> input;

    Vector2 position;
    Vector2 mousepos;
    int _ports;
    std::vector<Port*> portsIN;
    std::vector<Port*> portsOUT;

    Rectangle bounds;
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;

    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;

    virtual void onUse(){}
    int drag();


    Part(int x = 0, int y = 0, int ports = 0){
        name = nullptr; // Initialize name to nullptr to avoid potential issues
    
        this->position.x = x;
        this->position.y = y;
        this->_ports = ports;
        
        // Initialize bounds first
        
        
        // Use bounds to initialize other rectangles
        updateBounds();
        

    };
    int updateBounds();

    void next(Part* part, int port);

    void Output(Part* self, float value);
    int draw();


};

class Port{
public:  
    Part* next;
    int port;
    Part* prev;

    Port(Part* next, int port, Part* prev){
        this->next = next;
        this->port = port;
        this->prev = prev;
        prev->portsOUT.push_back(this);
        next->portsIN.push_back(this);
    }
    void kill(){

        this->next = nullptr;
        this->prev = nullptr;

        //delete this;
       
    }
};

class Dial : public Part{
public:
    float voltage;
    using Part::Part;

    Dial(int x, int y, int ports): Part(x, y, ports){
        name = "Dial";
        

        parts.push_back(this);
        partsInput.push_back(this);
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

    Sensor(int x, int y, int ports): Part(x, y, ports){
        
        name = "Sensor";

        parts.push_back(this);
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
    Plus(int x, int y, int ports): Part(x, y, ports){
        
        name = "Plus";

        parts.push_back(this);
    }

    void onUse() override {
        
        float voltage = input[0] + input[1];
        Output(this, voltage);
        

    }
};


void Part::next(Part* part, int port){

    if (part == nullptr) {
        std::cout << "Error: 'part' pointer is null!" << std::endl;
        return;
    }

    if (port < 0 || port >= part->_ports) {
        std::cout << "Error: Invalid 'port' value!" << std::endl;
        return;
    }
    
    ports.push_back(Port(part, port, this));
}
    

        
void Part::Output(Part* self, float value) {
    std::vector<Port*> portsToProcess;  // New vector to store ports to process

    // Find the ports that need to be processed
    for (Port port : ports) {
        if (port.prev == self) {
            portsToProcess.push_back(&port);
        }
    }

    // Process the ports
    for (Port* port : portsToProcess) {
        port->next->input.insert(port->next->input.begin() + port->port, value);
        //std::cout << port->prev->name << "-->" << value << "-->" << port->next->name << port->next->input[0] << std::endl;
        port->next->onUse();
    }
}
        

int Part::draw() {

    for (Port port : ports) {
        if (port.prev != this) {
            continue;
        }
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height / 2, port.next->bounds.x, port.next->bounds.y + bounds.height / 2, BLACK);
    }

    GuiPanel(bounds, name);

    if(isDraggingNext){
        Vector2 startPoint;
        startPoint.x = bounds.x + bounds.width;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineV(startPoint, GetMousePosition(), BLACK);
        
    }
    if(isDraggingPrev){
        Vector2 startPoint;
        startPoint.x = bounds.x + bounds.width;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineEx(startPoint, GetMousePosition(),4, CLITERAL(Color){255,0,0,100});
        
    }

    if (name == "Sensor") {
        if (input.empty()) {
            input.push_back(0.0f);
        }
        std::string str = std::to_string(input[0]);
        //std::cout << str << std::endl;
        char* value = const_cast<char*>(str.c_str());
        //std::cout << value << std::endl;
        GuiDrawText(value, bounds, 1, BLACK);
        input.clear();
    }

    

    return 1;
}

int Part::drag(){
    

    if(debug){
        DrawRectangleRec(dragBounds, CLITERAL(Color){255,0,0,128});
        DrawRectangleRec(outBounds, CLITERAL(Color){0,255,0,128});
        DrawRectangleRec(inBounds, CLITERAL(Color){0,0,255,128});

    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isDraggingNext && !isDraggingPrev && !isDragging){
        updateBounds();

        Vector2 lastmousepos; 
        lastmousepos.x = GetMousePosition().x - GetMouseDelta().x;
        lastmousepos.y = GetMousePosition().y - GetMouseDelta().y;

        if(insideRect(dragBounds, lastmousepos)){
            position.x += GetMouseDelta().x;
            position.y += GetMouseDelta().y;
            
        }
        if(insideRect(outBounds, GetMousePosition())){
            isDraggingNext = true;
            
        }
        if(insideRect(inBounds, GetMousePosition())){
            isDraggingPrev = true;
            
        }
        
    }
    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)){
    
        if(isDraggingNext){
            bool skip = false;
            for (Part* part : parts){
                if (part == this){continue;}

                

                if(insideRect(part->bounds, GetMousePosition()) && !skip){
                    std::cout << "connecting to " << part->name << std::endl;

                    Port p(part, 0, this);
                    ports.push_back(p);
                    
                    
                }
            }
            isDraggingNext = false;
        }

        if(isDraggingPrev){
            bool skip = false;
            for (Port port : ports){
                if(port.prev == this && insideRect(port.next->bounds, GetMousePosition())){
                
                    std::cout << "disconecting from " << port.next->name << std::endl;
                    port.kill();

                    
                            
                            
                }
            }
            isDraggingPrev = false;
        }

    }

}

int Part::updateBounds(){
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;


    inBounds = bounds;
    outBounds = bounds;
    dragBounds = bounds;
    dragBounds.height = 25;

    
    inBounds.width = outBounds.width = bounds.width / 2;
    inBounds.height = outBounds.height = bounds.height - dragBounds.height;
    outBounds.y = inBounds.y = bounds.y + dragBounds.height;
    outBounds.x = bounds.x + outBounds.width;
}