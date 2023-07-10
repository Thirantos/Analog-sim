//
// Created by thijm on 05/07/2023.
//

#include "component.h"

#define FONTSIZE 20


#include "include/raylib.h"
#include <nlohmann/json.hpp>
#define RAYLIB_H
#include "include/raygui.h"
#include "gui.h"

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
using json = nlohmann::json;
json savefile;

std::vector<Part*> partsList;
std::vector<Part*> partsInput;
std::vector<Port*> portsList;
bool mouseDragging;
int identifierPART = 0;
int identifierPORT = 0;


bool insideRect(Rectangle rect, Vector2 point){
    return point.x > rect.x && point.y > rect.y && point.x < rect.x + rect.width && point.y < rect.y + rect.height;

}


int Part::drawPorts(){
    for (Port* port : portsList) {
        if (port->prevPart != this) {
            continue;
        }
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height / 2, port->nextPart->bounds.x, port->nextPart->bounds.y + bounds.height / 2, BLACK);
    }
    return 1;
}
int Part::draw() {



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

    if (dynamic_cast<Sensor*>(this) != nullptr) {

        std::string str = "DISCONNECTED";
        for (Port* port : portsList) {
            if(port->nextPart != this) continue;
            str = std::to_string(port->value());
        }

        //std::cout << str << std::endl;
        char* value = const_cast<char*>(str.c_str());
        //std::cout << value << std::endl;

        DrawText(str.c_str(), dragBounds.x + (bounds.width - MeasureText(str.c_str(), FONTSIZE*0.7))/2,
                 dragBounds.y + dragBounds.height,  FONTSIZE*0.7, RED);
    }




    return 1;
}

bool Part::drag(){


    #ifdef ANASIMDEBUG

        DrawRectangleRec(dragBounds, CLITERAL(Color){255,0,0,128});
        DrawRectangleRec(outBounds, CLITERAL(Color){0,255,0,128});
        DrawRectangleRec(inBounds, CLITERAL(Color){0,0,255,128});

    #endif
        if(this == nullptr){return false;}


    if(IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
        mouseDragging = false;
        if (isDraggingNext) {
            bool skip = false;
            for (Part *part: partsList) {
                if (part == this) { continue; }


                if (insideRect(part->bounds, GetMousePosition()) && !skip) {
                    std::cout << "connecting to " << part->name << std::endl;

                    new Port(part, 0, this);




                }
            }
            isDraggingNext = false;

        }
        if (isDraggingPrev) {
            bool skip = false;
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

void Part::Output(float value) {
    //std::vector<Port*> portsToProcess;

    for (Port* port : portsList) {
        if(port->prevPart != this) continue;
        port->setValue(value);
        /*
        if(port->prevPart == nullptr || port->nextPart == nullptr) { continue; }
        if(port->prevPart->id > identifierPART || port->nextPart->id > identifierPART) { continue; }*/

        std::cout << port->prevPart->name << "(id: " << port->prevPart->id << ") --> " << value << " --> " << port->nextPart->name << "(id: " << port->nextPart->id << ")" << std::endl;
        port->nextPart->onUse();
    }
}

void Part::next(Part* part, int port){
    Port* _p = new Port(part, port, this);
}

int Part::kill() {
    delete this;
    return 0;
}

Dial::Dial(int x, int y, int ports) {
    name = "Dial";

    id = identifierPART;
    identifierPART++;
    val = 0;


    partsList.push_back(this);
    partsInput.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
    updateBounds();
}

void Dial::onUse() {
    int v = val;
    Output(float(v));
}

void Dial::set(int volt) {


    val = volt;
}

int Dial::draw() {
    Part::draw();
    Rectangle Spinner = bounds;
    Spinner.height *= 0.5;
    Spinner.width *= 0.7;

    Spinner.y += Spinner.height * 0.6;
    Spinner.x += bounds.width * 0.15;
    GuiSpinner(Spinner, "", &val, 0, INFINITY, false);
    return 0;
}

void Dial::serialize() {
    savefile["parts"][id]["position"]["x"] = position.x;
    savefile["parts"][id]["position"]["y"] = position.y;
    savefile["parts"][id]["type"] = PART_PLUS;
    savefile["parts"][id]["value"] = val;

}

Sensor::Sensor(int x, int y, int ports) {

    name = "Sensor";

    id = identifierPART;
    identifierPART++;

    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
    updateBounds();
}

void Sensor::onUse() {
/*
    for (Port port : portsList) {
        if(port.nextPart != this) continue;
        std::cout << port.value() << std::endl;
    }
*/


    /*
    std::string str = "";
    for (float val : input) {
        str += std::to_string(val) + " ";
    }

    str = "sensor: "+ str;
    name = const_cast<char*>(str.c_str());
    */
    return;
}

Plus::Plus(int x, int y, int ports) {
    name = "Plus";


    id = identifierPART;
    identifierPART++;

    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
    updateBounds();
}

void Plus::onUse() {

    float sum = 0;

    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        sum += port->value();
    }


    float voltage = sum;
    Output( voltage);


}

void Plus::serialize() {
    savefile["parts"][id]["position"]["x"] = position.x;
    savefile["parts"][id]["position"]["y"] = position.y;
    savefile["parts"][id]["type"] = PART_PLUS;
}


Port::Port(Part* next, int port, Part* prev) {
    nextPart = next;
    prevPart = prev;
    id = identifierPORT;
    identifierPORT++;
    portsList.push_back(this); // Store the pointer to the Port object
}


void Port::kill() {
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }
}

void Port::setValue(float value) {
    _value = value;
}
Part::~Part() {
    // Delete the ports associated with this part
    for (Port* port : portsList) {
        if (port->prevPart == this || port->nextPart == this) {
            delete port;
        }
    }
}

Port::~Port() {
    // Remove the port from the portsList vector when deleted
    auto it = std::find(portsList.begin(), portsList.end(), this);
    if (it != portsList.end()) {
        portsList.erase(it);
    }
}