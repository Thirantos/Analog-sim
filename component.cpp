//
// Created by thijm on 05/07/2023.
//

#include "component.h"

#include "settings.h"


#include "include/raylib.h"

#define RAYLIB_H
#include "include/raygui.h"


#include <iostream>
#include <vector>



std::vector<part*> partsList;
std::vector<part*> partsInput;
std::vector<Port*> portsList;
std::vector<part*> partsProcess;
std::vector<part*> tempPartsProcess;

bool mouseDragging;
int identifierPART = 0;
int identifierPORT = 0;

bool insideRect(Rectangle rect, Vector2 point){
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;

}

part::part(int x, int y, int id){
    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->id = id;

    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
    updateBounds();
}


void part::drawPorts(){
    for (Port* port : portsList) {
        if (port->prevPart != this) {
            continue;
        }
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height / 2, port->nextPart->bounds.x, port->nextPart->bounds.y + bounds.height / 2, BLACK);
    }
}
void part::draw() {

    //GuiPanel(bounds, name);

    DrawRectangleRec(bounds, WHITE );
    DrawText(name, dragBounds.x + (bounds.width - MeasureText(name, FONTSIZE))/2,
             dragBounds.y, FONTSIZE, DARKBLUE);



    DrawRectangleLinesEx(bounds, 1, DARKGRAY );



    if(isDraggingNext){
        Vector2 startPoint;
        startPoint.x = bounds.x + bounds.width;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineV(startPoint, GetMousePosition(), DARKGRAY);

    }
    if(isDraggingPrev){
        Vector2 startPoint;
        startPoint.x = bounds.x;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineEx(startPoint, GetMousePosition(),4, CLITERAL(Color){255,0,0,100});

    }

}

bool part::drag(){


    #ifdef ANASIMDEBUG

        DrawRectangleRec(dragBounds, CLITERAL(Color){255,0,0,128});
        DrawRectangleRec(outBounds, CLITERAL(Color){0,255,0,128});
        DrawRectangleRec(inBounds, CLITERAL(Color){0,0,255,128});

    #endif


    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        mouseDragging = false;
        if (isDraggingNext) {
            isDraggingNext = false;
            for (part *part: partsList) {
                if (part == this) { continue; }
                bool skip = false;
                for (Port* p : portsList) {
                    if(p->prevPart == this && p->nextPart == part){
                        skip = true;
                    }
                }
                if(!skip) {
                    if (insideRect(part->bounds, GetMousePosition())) {
                        std::cout << "connecting to " << part->name << std::endl;

                        new Port(part, 0, this, 0);
#warning "ID NOT IMPLEMENTED"
                    }
                }
            }


        }
        if (isDraggingPrev) {
            for (Port* port: portsList) {
                if(port->nextPart != this)continue;
                std::cout << "Checking " << port->prevPart->id << std::endl;
                if (insideRect(port->prevPart->bounds, GetMousePosition())) {

                    std::cout << "disconecting from " << port->prevPart->name << std::endl;

                    auto it = std::find(portsList.begin(), portsList.end(), port);

                    if (it != portsList.end()) {
                        // Erase the object from the vector
                        portsList.erase(it);
                    }

                    port->kill();


                }
            }
            isDraggingPrev = false;
        }
        return false;

    }


    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isDraggingNext && !isDraggingPrev && !mouseDragging){
        updateBounds();


        if(insideRect(bounds, GetMousePosition())){
            mouseDragging = true;

            partsList.erase(std::remove(partsList.begin(), partsList.end(), this), partsList.end());
            partsList.push_back(this);



        }


        Vector2 lastmousepos;
        lastmousepos.x = GetMousePosition().x - GetMouseDelta().x;
        lastmousepos.y = GetMousePosition().y - GetMouseDelta().y;

        if(insideRect(dragBounds, lastmousepos)){
            position.x += GetMouseDelta().x;
            position.y += GetMouseDelta().y;




        }
        if(insideRect(outBounds, GetMousePosition())&&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            isDraggingNext = true;

        }
        if(insideRect(inBounds, GetMousePosition())&&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            isDraggingPrev = true;


        }
        return true;
    }
    return false;

}

void part::updateBounds(){
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

void part::Output(float value) {
    //std::vector<Port*> portsToProcess;


    for (Port* port : portsList) {
        if(port->prevPart != this) continue;
        port->setValue(value);
        /*
        if(port->prevPart == nullptr || port->nextPart == nullptr) { continue; }
        if(port->prevPart->id > identifierPART || port->nextPart->id > identifierPART) { continue; }*/

        std::cout << port->prevPart->name << "(id: " << port->prevPart->id << ") --> " << value << " --> " << port->nextPart->name << "(id: " << port->nextPart->id << ")" << std::endl;
        tempPartsProcess.push_back(port->nextPart);
    }
}

void part::next(part* part, int port){
    Port* _p = new Port(part, port, this, 0);
#warning "ID NOT IMPLEMENTED"

}

void part::kill() {
    auto it = std::find(partsList.begin(), partsList.end(), this);
    if (it != partsList.end()) {
        partsList.erase(it);
    }
}


Port::Port(part* next, int port, part* prev, int id) {
    Port::id = id;
    nextPart = next;
    prevPart = prev;
    nextPort = port;

    portsList.push_back(this); // Store the pointer to the Port object
}


void Port::kill() {
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }
    delete this;
}



void Port::setValue(float value) {
    _value = value;
}
part::~part() {
    // Delete the ports associated with this part
    for (Port* port : portsList) {
        if (port->prevPart == this || port->nextPart == this) {
            port->kill();
        }
    }
    delete this;
}


Port::~Port() {
    // Remove the port from the portsList vector when deleted
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }
}
