//
// Created by thijm on 05/07/2023.
//

#include "component.h"

#include "settings.h"


#include "include/raylib.h"

#define RAYLIB_H
#include "include/raygui.h"
#include "raymath.h"


#include <iostream>
#include <vector>

int identifierPart;
int identifierPort;

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
Rectangle cameraDisplace(Rectangle rect, Camera2D camera){


    Vector2 topLeft = (Vector2){rect.x, rect.y};
    Vector2 botRight = (Vector2){rect.x + rect.width, rect.y + rect.height};
    topLeft = Vector2Transform(topLeft ,GetCameraMatrix2D(camera));
    botRight = Vector2Transform(botRight ,GetCameraMatrix2D(camera));

    rect.x = topLeft.x;
    rect.y = topLeft.y;

    rect.width  = botRight.x - topLeft.x;
    rect.height = botRight.y - topLeft.y;
    
    return rect;
}


part::part(int x, int y) {
    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->id = identifierPART;
    identifierPART++;

    updateBounds();
}


void part::drawPorts(Camera2D camera){
    for (Port* port : portsList) {
        if (port->prevPart != this) {
            continue;
        }
        DrawLineBezierCubic(Vector2{outBounds.x + outBounds.width, outBounds.y + outBounds.height / 2},
                            Vector2{port->nextPart->inBounds[port->nextPort].x, port->nextPart->inBounds[port->nextPort].y + port->nextPart->inBounds[port->nextPort].height / 2},
                            Vector2{outBounds.x + outBounds.width + LINEBEND, outBounds.y + outBounds.height / 2},
                            Vector2{port->nextPart->inBounds[port->nextPort].x - LINEBEND, port->nextPart->inBounds[port->nextPort].y + port->nextPart->inBounds[port->nextPort].height / 2},
                                    1, DARKGRAY);

    }
}
void part::draw(Camera2D camera) {

    //GuiPanel(bounds, name);

    DrawRectangleRec(bounds, WHITE );
    DrawRectangleRec(dragBounds, LIGHTGRAY );
    DrawText(name, dragBounds.x + (bounds.width - MeasureText(name, FONTSIZE))/2,
             dragBounds.y, FONTSIZE, DARKBLUE);



    DrawRectangleLinesEx(bounds, 1 / camera.zoom, DARKGRAY );

    if(maxPorts > 0) {
        for (Rectangle inRect: inBounds) {

            DrawCircle(
                    inRect.x,
                    inRect.y + inRect.height / 2,
                    6 + 1 / camera.zoom, DARKGRAY
            );
            DrawCircle(
                    inRect.x,
                    inRect.y + inRect.height / 2,
                    6, GOLD
            );
        }
    }
    if(maxPorts == -1) {

        Rectangle inRectangle;
        inRectangle.x = inBounds[0].x - 6;
        inRectangle.y = inBounds[0].y + inBounds[0].height/2 - 12;
        inRectangle.width = 12;
        inRectangle.height = 24;

        DrawRectangleRounded(inRectangle, 10, 10, GOLD);
        DrawRectangleRoundedLines(inRectangle, 10, 10, 1 / camera.zoom, DARKGRAY);

    }
    if(dragOut) {
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


    if(isDraggingNext){
        Vector2 startPoint;
        startPoint.x = outBounds.x + outBounds.width;
        startPoint.y = outBounds.y + outBounds.height / 2;
        DrawLineV(startPoint, GetScreenToWorld2D(GetMousePosition(), camera), DARKGRAY);

    }
    if(isDraggingPrev){
        Vector2 startPoint;
        startPoint.x = bounds.x;
        startPoint.y = bounds.y + bounds.height / 2;
        DrawLineEx(startPoint, GetScreenToWorld2D(GetMousePosition(), camera),4, CLITERAL(Color){255,0,0,100});

    }

}

bool part::drag(Camera2D camera){

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

                if (skip || !insideRect(part->bounds, GetScreenToWorld2D(GetMousePosition(), camera))) continue;
                int i = 0;
                for (Rectangle bound: part->inBounds) {
                    if (insideRect(bound, GetScreenToWorld2D(GetMousePosition(), camera))) {
                        this->next(part, i);
                        return true;
                    }else{
                        i++;
                    }
                }



            }


        }
        if (isDraggingPrev) {
            for (Port* port: portsList) {
                if(port->nextPart != this) continue;
                if (!insideRect(port->prevPart->bounds, GetScreenToWorld2D(GetMousePosition(), camera))) continue;


                auto it = std::find(portsList.begin(), portsList.end(), port);

                if (it != portsList.end()) {
                    // Erase the object from the vector
                    portsList.erase(it);
                }
                port->nextPart->currentPorts--;
                delete port;


            }
            isDraggingPrev = false;
        }
        return false;

    }


    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isDraggingNext && !isDraggingPrev && !mouseDragging){
        updateBounds();


        if(insideRect(bounds, GetScreenToWorld2D(GetMousePosition(), camera))){
            mouseDragging = true;

            partsList.erase(std::remove(partsList.begin(), partsList.end(), this), partsList.end());
            partsList.push_back(this);



        }


        Vector2 lastmousepos;
        lastmousepos.x = GetScreenToWorld2D(GetMousePosition(), camera).x - GetMouseDelta().x;
        lastmousepos.y = GetScreenToWorld2D(GetMousePosition(), camera).y - GetMouseDelta().y;

        if(insideRect(dragBounds, lastmousepos)){
            position.x += GetMouseDelta().x;
            position.y += GetMouseDelta().y;




        }
        if(insideRect(outBounds, GetScreenToWorld2D(GetMousePosition(), camera))&&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            isDraggingNext = true;

        }
        if(maxPorts > 0){
            for (int i = 0; i <= maxPorts;i++) {
                if (insideRect(inBounds[i], GetScreenToWorld2D(GetMousePosition(), camera)) &&
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    isDraggingPrev = true;

                }

            }
        }else if(maxPorts < 0){
            if (insideRect(inBounds[0], GetScreenToWorld2D(GetMousePosition(), camera)) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                isDraggingPrev = true;

            }
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

    dragBounds = bounds;
    dragBounds.height = 25;

    inBounds.clear();

    if(maxPorts > 0) {
        float step = (bounds.height - dragBounds.height) / (maxPorts);


        for (int i = 1; i <= maxPorts; ++i) {
            Rectangle P{bounds.x, bounds.y + (i-1) * step + dragBounds.height, bounds.width/8, step};
            inBounds.push_back(P);
        }

    }else if(maxPorts < 0){
        Rectangle P{bounds.x, bounds.y + dragBounds.height, bounds.width/8, bounds.height - dragBounds.height};
        inBounds.push_back(P);
    }



    outBounds = bounds;

    outBounds.width = bounds.width / 8;
    outBounds.height = bounds.height - dragBounds.height;
    outBounds.y = bounds.y + dragBounds.height;
    outBounds.x = bounds.x + bounds.width - outBounds.width;
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

    for (Port* p : portsList) {
        if (p->nextPart == part && p->_port == port && p->prevPart == this) return;
    }

    if (part->currentPorts >= part->maxPorts && part->maxPorts != -1) return;
    Port *_p = new Port(part, port, this);
    part->currentPorts++;
}




Port::Port(part *next, int port, part *prev) {
    Port::id = identifierPORT;
    identifierPORT++;
    nextPart = next;
    prevPart = prev;
    nextPort = port;

    portsList.push_back(this); // Store the pointer to the Port object
}





void Port::setValue(float value) {
    _value = value;
}
part::~part() {
    auto it = std::find(partsList.begin(), partsList.end(), this);
    if (it != partsList.end()) {
        partsList.erase(it);
    }
    auto it2 = std::find(partsProcess.begin(), partsProcess.end(), this);
    if (it2 != partsProcess.end()) {
        partsProcess.erase(it2);
    }
    for (Port* port : portsList) {
        if (port->prevPart == this || port->nextPart == this) delete port;
    }
}

void part::serialize(json* Data, json properties) {
    json partj;
    partj["id"] = id;
    partj["x"]  = position.x;
    partj["y"]  = position.y;
    partj["type"]  = name;
    partj["data"]  = properties;
    Data->push_back(partj);

}




Port::~Port() {
    // Remove the port from the portsList vector when deleted
    nextPart->currentPorts--;
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }
}

void Port::serialize(json *Data) {
    json portj;
    portj["id"] = id;
    portj["prev"]  = prevPart->id;
    portj["next"]  = nextPart->id;
    portj["value"]  = value();
    Data->push_back(portj);
}
