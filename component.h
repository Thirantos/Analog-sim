
#ifndef ANALOGSIM_COMPONENT_H
#define ANALOGSIM_COMPONENT_H

#include <vector>
#include <string>
#include "include/raylib.h"
#include "include/raygui.h"



class Part;
class Port;

extern std::vector<Part*> partsList;
extern std::vector<Part*> partsInput;
extern std::vector<Port> portsList;


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

    Part() = default;

    Part(int x, int y, int ports){
        
    }

    void next(Part* part, int port);

    void Output(Part* self, float value);
    int draw();

};

class Port{
public:  
    Part* next;
    int port;
    Part* prev;

    Port(Part* next, int port, Part* prev);
    void kill(){

        delete this;
       
    }
};

class Dial : public Part{
public:
    float voltage;
    using Part::Part;

    Dial(int x, int y, int ports);

    void onUse() override;

    void set(float voltage);
};

class Sensor : public Part{
public:
    using Part::Part;

    Sensor(int x, int y, int ports);


    void onUse() override;
};

class Plus : public Part{
public:
    using Part::Part;
    Plus(int x, int y, int ports);

    void onUse() override;
};

#endif //
