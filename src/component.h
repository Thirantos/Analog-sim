
#ifndef ANALOGSIM_COMPONENT_H
#define ANALOGSIM_COMPONENT_H

#include <vector>
#include <string>
#include <raylib.h>
#include "serializer.h"
#include "matrix.h"


enum mouseModeEnum: unsigned int  {none, selectingMultiple, select, dragginPart, usingMenu};
extern mouseModeEnum mouseMode;

class part;
class Port;

extern std::vector<part*> partsList;
extern std::vector<part*> partsInput;
extern std::vector<part*> partsProcess;
extern std::vector<part*> tempPartsProcess;
extern std::vector<Port*> portsList;
extern std::vector<part*> selectedParts;
extern bool mouseDragging;
extern int identifierPART;
extern int identifierPORT;

Rectangle cameraDisplace(Rectangle rect, Camera2D camera);
Rectangle cameraAntiDisplace(Rectangle rect, Camera2D camera);
Color colorFromType(std::string type);


struct packet{

    float _float;
    Vector3 _vector3;
    matrix _matrix = matrix(0,0);
    bool _boolean;

};

class part{

public:
    const char* name{};
    int id{};
    Vector2 position{};

    Rectangle bounds{};
    std::vector<Rectangle> inBounds;
    std::vector<Rectangle> outBounds;
    Rectangle outBound = bounds;
    Rectangle inBound = bounds;
    Rectangle dragBounds = bounds;
    std::vector<std::string> portsInName{};
    std::vector<std::string> portsOutName{};
    bool noMaxPorts = false;

    int currentDragginOut = 0;

    std::vector<Port*> portsIn;
    std::vector<Port*> portsOut;

    std::map<std::string, packet> getInputs();


    bool dragOut = true;
    bool isDragging = false;
    bool isDraggingNext = false;
    bool isDraggingPrev = false;
    bool isDraggingMove = false;


    virtual void  onUse(){}
    bool drag(Camera2D camera);


    void postInitialize();

    virtual ~part();

    part(int x, int y, int id = identifierPART);

    void next(int prevPort, part *next, int nextPort);

    void Output(packet packet, std::string outName = "f_out");
    void drawPorts(Camera2D camera);
    virtual void draw(Camera2D camera);
    virtual void drawIgnoreCam(Camera2D camera){};
    virtual void serialize(json* Data, json properties = NULL);
    virtual void menu();


};

class Port{
private:
    packet _packet = packet{
        ._float = 0,
        ._vector3 = {0,0,0},
        ._matrix = matrix(0,0),
    };
public:

    int id;

    part* nextPart;
    part* prevPart;

    int _port;

    int nextPort;
    int prevPort;
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

    Port(part *next, int nextPort, part *prev, int prevPort, int id = identifierPORT);

    ~Port();

    void setValue(packet packet);

    void serialize(json* Data);
};

part* constructorFromName(const std::string& className, int x, int y, int id = identifierPART, json data = nullptr);
part* partFromId(int id);

#endif //ANALOGSIM_COMPONENT_H
