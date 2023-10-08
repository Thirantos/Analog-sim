
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
extern int identifierPART;
extern int identifierPORT;

Rectangle cameraDisplace(Rectangle rect, Camera2D camera);

struct packet{
    float voltage;
    float amperage;
};

class part{

public:
    const char* name{};
    int id{};
    Vector2 position{};

    Rectangle bounds{};
    std::vector<Rectangle> inBounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;
    int maxPorts{};
    int currentPorts{};


    bool dragOut{};
    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;

    virtual void  onUse(){}
    bool drag(Camera2D camera);


    void updateBounds();

    virtual ~part();

    part(int x, int y, int id = identifierPART);

    void next(part* part, int port);

    void Output(packet packet);
    void drawPorts(Camera2D camera);
    virtual void draw(Camera2D camera);
    virtual void drawIgnoreCam(Camera2D camera){};
    virtual void serialize(json* Data, json properties = NULL);


};

class Port{
private:
    packet _packet = packet{
        .voltage = 0,
        .amperage = 0
    };
public:

    int id;

    part* nextPart;
    part* prevPart;
    int _port;

    int nextPort;
    [[nodiscard]] packet value() const { return _packet; }
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

    Port(part *next, int port, part *prev, int id = identifierPORT);

    ~Port();

    void setValue(packet packet);

    void serialize(json* Data);
};

part* constructorFromName(const std::string& className, int x, int y, int id = identifierPART);
part* partFromId(int id);

#endif //ANALOGSIM_COMPONENT_H
