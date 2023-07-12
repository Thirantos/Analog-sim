
#ifndef ANALOGSIM_COMPONENT_H
#define ANALOGSIM_COMPONENT_H
#define PART_DIAL 1
#define PART_PLUS 2
#define PART_SENSOR 3

#include <vector>
#include <string>
#include "include/raylib.h"
#include "include/raygui.h"
#include "serializer.h"



class part;
class Port;

extern std::vector<part*> partsList;
extern std::vector<part*> partsInput;
extern std::vector<part*> partsProcess;
extern std::vector<part*> tempPartsProcess;
extern std::vector<Port*> portsList;
extern bool mouseDragging;
//extern int identifierX;


class part{

public:
    const char* name{};
    int id{};

    Vector2 position{};
    Vector2 mousepos{};
    int _ports{};


    //std::vector<Port*> portsIN;
    /*
    std::vector<Port*> portsOUT;
*/
    Rectangle bounds{};
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;

    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;

    virtual void  onUse(){}
    bool drag();
    void kill();


    void updateBounds();

    virtual ~part();

    part(int x, int y, int id);

    void next(part* part, int port);

    void Output(float value);
    void drawPorts();
    virtual void draw();


};

class Port{
private:
    float _value = 0.0f;
public:

    int id;

    part* nextPart;
    part* prevPart;

    int nextPort;
    [[nodiscard]] float value() const { return _value; }
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

    Port(part* next, int port, part* prev, int id);

    ~Port();

    void setValue(float value);
    void kill();


};




#endif //ANALOGSIM_COMPONENT_H
