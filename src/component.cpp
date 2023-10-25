//
// Created by thijm on 05/07/2023.
//

#include "component.h"

#include "settings.h"


#include "raylib.h"

#define RAYLIB_H

#include "raymath.h"


#include <iostream>
#include <utility>
#include <vector>

std::vector<part *> partsList;
std::vector<part *> partsInput;
std::vector<Port *> portsList;
std::vector<part *> partsProcess;
std::vector<part *> tempPartsProcess;

bool mouseDragging;
int identifierPART = 0;
int identifierPORT = 0;


int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

bool insideRect(Rectangle rect, Vector2 point) {
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;

}

Rectangle cameraDisplace(Rectangle rect, Camera2D camera) {


    Vector2 topLeft = (Vector2) {rect.x, rect.y};
    Vector2 botRight = (Vector2) {rect.x + rect.width, rect.y + rect.height};
    topLeft = Vector2Transform(topLeft, GetCameraMatrix2D(camera));
    botRight = Vector2Transform(botRight, GetCameraMatrix2D(camera));

    rect.x = topLeft.x;
    rect.y = topLeft.y;

    rect.width = botRight.x - topLeft.x;
    rect.height = botRight.y - topLeft.y;

    return rect;
}


part::part(int x, int y, int id) {
    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->id = id;

    identifierPART = max(id, identifierPART) + 1;
}

std::map<std::string, packet> part::getInputs(){
 // for(port* port : portsIn)
    std::map<std::string, packet> dict;
    if(noMaxPorts) throw "not implemented";

    for (int i = 0; i < Ports.size(); ++i) {

        if(portsIn[i] != nullptr){


            float volt = portsIn[i]->value().voltage == NAN? 0 : portsIn[i]->value().voltage;
            float amp = portsIn[i]->value().amperage == NAN? 0 : portsIn[i]->value().amperage;


            dict[Ports[i]] = packet{.voltage = volt,.amperage = amp};


        }else {

            dict[Ports[i]] = packet{0,0};

        }
    }

    return dict;

}


void part::drawPorts(Camera2D camera) {
    for (Port *port: portsOut) {
        if(port->nextPart->bounds.height == 0) {delete port; return;};
        DrawLineBezierCubic(Vector2{outBounds.x + outBounds.width, outBounds.y + outBounds.height / 2},
                            Vector2{port->nextPart->inBounds[port->nextPort].x,
                                    port->nextPart->inBounds[port->nextPort].y +
                                    port->nextPart->inBounds[port->nextPort].height / 2},
                            Vector2{outBounds.x + outBounds.width + LINEBEND, outBounds.y + outBounds.height / 2},
                            Vector2{port->nextPart->inBounds[port->nextPort].x - LINEBEND,
                                    port->nextPart->inBounds[port->nextPort].y +
                                    port->nextPart->inBounds[port->nextPort].height / 2},
                            1, DARKGRAY);

    }
}

void part::draw(Camera2D camera) {

    //GuiPanel(bounds, name);

    DrawRectangleRec(bounds, WHITE);
    DrawRectangleRec(dragBounds, LIGHTGRAY);
    DrawText(name, dragBounds.x + (bounds.width - MeasureText(name, FONTSIZE)) / 2,
             dragBounds.y, FONTSIZE, DARKBLUE);


    DrawRectangleLinesEx(bounds, 1 / camera.zoom, DARKGRAY);

    if (Ports.size() > 0) {

        for (int i = 0; i < Ports.size(); ++i) {

            Rectangle inRect = inBounds[i];

            DrawCircle(
                    inRect.x,
                    inRect.y + inRect.height / 2,
                    6 + 1 / camera.zoom, DARKGRAY
            );
            DrawText(Ports[i].c_str(), inRect.x + 10, inRect.y + inRect.height / 6, 20, DARKGRAY);
            DrawCircle(
                    inRect.x,
                    inRect.y + inRect.height / 2,
                    6, GOLD
            );
        }
    }
    if (noMaxPorts) {

        Rectangle inRectangle;
        inRectangle.x = inBounds[0].x - 6;
        inRectangle.y = inBounds[0].y + inBounds[0].height / 2 - 12;
        inRectangle.width = 12;
        inRectangle.height = 24;

        DrawRectangleRounded(inRectangle, 10, 10, GOLD);
        DrawRectangleRoundedLines(inRectangle, 10, 10, 1 / camera.zoom, DARKGRAY);

    }
    if (dragOut) {
        DrawCircle(
                outBounds.x + outBounds.width,
                outBounds.y + outBounds.height / 2,
                6 + 1 / camera.zoom, DARKGRAY
        );
        DrawCircle(
                outBounds.x + outBounds.width,
                outBounds.y + outBounds.height / 2,
                6, GOLD
        );
    }


    if (isDraggingNext) {
        Vector2 startPoint;
        startPoint.x = outBounds.x + outBounds.width;
        startPoint.y = outBounds.y + outBounds.height / 2;
        DrawLineV(startPoint, GetScreenToWorld2D(GetMousePosition(), camera), DARKGRAY);

    }
    if (isDraggingPrev) {
        Vector2 startPoint;
        startPoint.x = bounds.x;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineEx(startPoint, GetScreenToWorld2D(GetMousePosition(), camera), 4, CLITERAL(Color){255, 0, 0, 100});

    }

}

bool part::drag(Camera2D camera) {

#ifdef ANASIMDEBUG

    DrawRectangleRec(dragBounds, CLITERAL(Color){255,0,0,128});
    DrawRectangleRec(outBounds, CLITERAL(Color){0,255,0,128});
    DrawRectangleRec(inBounds, CLITERAL(Color){0,0,255,128});

#endif


    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        mouseDragging = false;
        if (isDraggingNext) {
            isDraggingNext = false;
            for (part *part: partsList) {
                if (part == this) { continue; }
                bool skip = false;
                for (Port *p: portsOut) {
                    if (p->nextPart == part) {
                        skip = true;
                    }
                }
                Vector2 worldmouse = GetScreenToWorld2D(GetMousePosition(), camera);
                if (skip || !insideRect(part->bounds,worldmouse)) continue;
                int i = 0;
                for (Rectangle bound: part->inBounds) {
                    if (insideRect(bound, worldmouse)) {
                        this->next(part, i);
                        return true;
                    } else {
                        i++;
                    }
                }


            }


        }
        if (isDraggingPrev) {
            for (Port *port: portsIn) {
                if (port == NULL) continue;
                if (!insideRect(port->prevPart->bounds, GetScreenToWorld2D(GetMousePosition(), camera))) continue;


                auto it = std::find(portsList.begin(), portsList.end(), port);

                if (it != portsList.end()) {
                    // Erase the object from the vector
                    portsList.erase(it);
                }
                delete port;


            }
            isDraggingPrev = false;
        }
        return false;

    }


    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isDraggingNext && !isDraggingPrev && !mouseDragging) {
        postInitialize();


        if (insideRect(bounds, GetScreenToWorld2D(GetMousePosition(), camera))) {
            mouseDragging = true;

            partsList.erase(std::remove(partsList.begin(), partsList.end(), this), partsList.end());
            partsList.push_back(this);


        }


        Vector2 lastmousepos;
        lastmousepos.x = GetScreenToWorld2D(GetMousePosition(), camera).x - GetMouseDelta().x;
        lastmousepos.y = GetScreenToWorld2D(GetMousePosition(), camera).y - GetMouseDelta().y;

        if (insideRect(dragBounds, lastmousepos)) {
            position.x += GetMouseDelta().x / camera.zoom;
            position.y += GetMouseDelta().y / camera.zoom;


        }
        if (insideRect(outBounds, GetScreenToWorld2D(GetMousePosition(), camera)) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isDraggingNext = true;

        }
        if (Ports.size() > 0) {
            for (int i = 0; i <= Ports.size(); i++) {
                if (insideRect(inBounds[i], GetScreenToWorld2D(GetMousePosition(), camera)) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isDraggingPrev = true;

                }

            }
        } else if (noMaxPorts) {
            if (insideRect(inBounds[0], GetScreenToWorld2D(GetMousePosition(), camera)) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                isDraggingPrev = true;

            }
        }

        return true;
    }
    return false;

}

void part::postInitialize() {


    if(portsIn.size() < Ports.size()) {
        for (int i = 0; i < Ports.size(); ++i) {
            portsIn.push_back(nullptr);
        }
    }


    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;

    bounds.height = max(75, Ports.size() * 25);

    dragBounds = bounds;
    dragBounds.height = 25;

    inBounds.clear();

    if (Ports.size() > 0) {
        float step = (bounds.height - dragBounds.height) / (Ports.size());


        for (int i = 1; i <= Ports.size(); ++i) {
            Rectangle P{bounds.x, bounds.y + (i - 1) * step + dragBounds.height, bounds.width / 8, step};
            inBounds.push_back(P);
        }

    } else if (noMaxPorts) {
        Rectangle P{bounds.x, bounds.y + dragBounds.height, bounds.width / 8, bounds.height - dragBounds.height};
        inBounds.push_back(P);
    }


    outBounds = bounds;

    outBounds.width = bounds.width / 8;
    outBounds.height = bounds.height - dragBounds.height;
    outBounds.y = bounds.y + dragBounds.height;
    outBounds.x = bounds.x + bounds.width - outBounds.width;
}

void part::Output(packet packet) {
    //std::vector<Port*> portsToProcess;


    for (Port *port: portsOut) {
        port->setValue(packet);
        /*
        if(port->prevPart == nullptr || port->nextPart == nullptr) { continue; }
        if(port->prevPart->id > identifierPART || port->nextPart->id > identifierPART) { continue; }*/
        /*
        std::cout << port->prevPart->name << "(id: " << port->prevPart->id << ") --> " << value << " --> "
                  << port->nextPart->name << "(id: " << port->nextPart->id << ")" << std::endl;
        */

        tempPartsProcess.push_back(port->nextPart);
    }
}

void part::next(part *part, int port) {

    for (Port *p: portsOut) {
        if (p->nextPart == part && p->_port == port) return;
    }

    if (!part->noMaxPorts) delete part->portsIn[port];

    new Port(part, port, this);
}


Port::Port(part *next, int port, part *prev, int id) {

    nextPart = next;
    prevPart = prev;
    nextPort = port;
    this->id = id;
    identifierPART = max(id, identifierPART) + 1;

    if(next->noMaxPorts){
        next->portsIn.push_back(this);

    }else{
        next->portsIn[port] = this;

    }
    prev->portsOut.push_back(this);

    portsList.push_back(this); // Store the pointer to the Port object
}


void Port::setValue(packet packet) {
    _packet = packet;
}

part::~part() {

    for (Port *port: portsOut){
        delete port;
    }
    for (Port *port: portsIn){
        delete port;
    }


    auto it2 = std::find(partsInput.begin(), partsInput.end(), this);
    if (it2 != partsInput.end()) {
        partsInput.erase(it2);
    }

    auto it3 = std::find(partsProcess.begin(), partsProcess.end(), this);
    if (it3 != partsProcess.end()) {
        partsProcess.erase(it3);
    }

    auto it4 = std::find(tempPartsProcess.begin(), tempPartsProcess.end(), this);
    if (it4 != tempPartsProcess.end()) {
        tempPartsProcess.erase(it4);
    }
    auto it = std::find(partsList.begin(), partsList.end(), this);
    if (it != partsList.end()) {
        partsList.erase(it);
    }




}

void part::serialize(json *Data, json properties) {
    json partj;
    partj["id"] = id;
    partj["x"] = position.x;
    partj["y"] = position.y;
    partj["type"] = name;
    partj["data"] = std::move(properties);
    Data->push_back(partj);

}


Port::~Port() {
    // Remove the port from the portsList vector when deleted
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }

    auto next = std::find(nextPart->portsIn.begin(), nextPart->portsIn.end(), this);

    if (next != nextPart->portsIn.end()) {
        long idx = std::distance(nextPart->portsIn.begin(), next);
        nextPart->portsIn[idx] = nullptr;
    }


    std::vector<Port*> tempPortsOut;
    for (Port* port: prevPart->portsOut){
        if (port != this){
            tempPortsOut.push_back(port);
        }
    }
    prevPart->portsOut = tempPortsOut;
    tempPortsOut.clear();


    partsProcess.clear();
    tempPartsProcess.clear();


    this->nextPart = nullptr;
    this->prevPart = nullptr;
}

void Port::serialize(json *Data) {
    json portj;
    portj["id"] = id;
    portj["prev"] = prevPart->id;
    portj["next"] = nextPart->id;
    portj["port"] = nextPort;
    portj["valueAMP"] = value().amperage;
    portj["valueVOLT"] = value().voltage;
    Data->push_back(portj);
}

#include "parts.h"

part* constructorFromName(const std::string &className, int x, int y, int id, json data) {
    if (className == "dial") {
        dial* d = new dial(x, y, id);
        if(data.is_null()) return d;
        d->val = data["value"];
        return d;
    } else if (className == "sensor") {
        return new sensor(x, y, id);
    } else if (className == "normalizePolygonA") {
        return new normalizePolygonA(x, y, id);
    } else if (className == "normalizePolygonB") {
        return new normalizePolygonB(x, y, id);
    } else if (className == "normalizePolygonC") {
        return new normalizePolygonC(x, y, id);
    } else if (className == "plus") {
        return new plus(x, y, id);
    } else if (className == "average") {
        return new average(x, y, id);
    } else if (className == "dotProduct") {
        return new dotProduct(x, y, id);
    } else if (className == "areaPolygon") {
        return new areaPolygon(x, y, id);
    } else {
        // Handle unknown class names or return a default
        return new part(x, y, id);
    }


#warning "here are more classes added"
}

part *partFromId(int id) {
    for (part *p: partsList) {
        if (p->id == id) {
            return p;
        }
    }
    return nullptr;
}
