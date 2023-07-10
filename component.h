
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
extern bool mouseDragging;
//extern int identifierX;


class Part{

public:
    char* name;
    int id;

    Vector2 position;
    Vector2 mousepos;
    int _ports;


    //std::vector<Port*> portsIN;
    /*
    std::vector<Port*> portsOUT;
*/
    Rectangle bounds;
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;

    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;

    virtual void  onUse(){}
    bool drag();
    int kill();

    Part() = default;
    int updateBounds();

    ~Part(){
        delete this;
    }

    Part(int x, int y, int ports) {

    }

    void next(Part* part, int port);

    void Output(float value);
    int drawPorts();
    int draw();

};

class Port{
private:
    float _value;
public:
    int id;

    Part* nextPart;
    Part* prevPart;
    float value() const { return _value; }
    bool operator==(const Port& other) const {
        // Define your own equality comparison logic here
        // Return true if the objects are considered equal, false otherwise
        // Example: Compare relevant members of the objects
        return this->id == other.id;
    }

    bool operator!=(const Port& other) const {
        // Define your own inequality comparison logic here
        // Return true if the objects are considered not equal, false otherwise
        // Example: Use the negation of the equality operator
        return this->id != other.id;
    }

    Port(Part* next, int port, Part* prev);

    void setValue(float x);
    void kill();


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
