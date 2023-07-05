//
// Created by thijm on 05/07/2023.
//

#include "component.h"

#ifndef RAYGUI_IMPLEMENTATION
#include "include/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#endif
#include <iostream>
#include <vector>
#include <string>

std::vector<Part*> partsList;
std::vector<Part*> partsInput;
std::vector<Port> portsList;


int Part::draw() {
    Rectangle inBounds = bounds;
    Rectangle outBounds = bounds;
    Rectangle dragBounds = bounds;
    dragBounds.height = 25;
    inBounds.width = outBounds.width = bounds.width / 2;
    inBounds.height = outBounds.height = bounds.height;
    outBounds.x = bounds.x + outBounds.width;

    if (!isDragging && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), dragBounds)) {
            isDragging = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(), outBounds)) {
            isDraggingNext = true;
        }
        if (CheckCollisionPointRec(GetMousePosition(), inBounds)) {
            isDraggingPrev = true;
        }
    }

    if (isDraggingPrev && !isDragging) {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            for (Port* port : portsIN) {

                if (port->next != this) {
                    if(port->prev != nullptr) {
                        if (CheckCollisionPointRec(GetMousePosition(), port->prev->outBounds)) {    //HERE IS AN ERROR

                            port->kill();

                        }
                    }}}
            isDraggingPrev = false;
        }
    }

    if (isDragging) {
        bounds.x += GetMouseDelta().x;
        bounds.y += GetMouseDelta().y;
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDragging = false;
        }
    }

    if (IsKeyDown(KEY_A)) {
        for (Part* part : partsList) {
            next(this, 0);
        }
    }

    if (isDraggingNext) {
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height / 2, GetMouseX(), GetMouseY(), BLACK);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            for (Part* part : partsList) {
                if (part != this && CheckCollisionPointRec(GetMousePosition(), part->inBounds)) {
                    next(part, 0);
                }
            }
            isDraggingNext = false;
        }
    }



    for (Port port : portsList) {
        if (port.prev != this) {
            continue;
        }
        DrawLine(bounds.x + bounds.width, bounds.y + bounds.height / 2, port.next->bounds.x, port.next->bounds.y + bounds.height / 2, BLACK);
    }

    GuiPanel(bounds, name);

    if (name == "Sensor") {
        if (input.empty()) {
            input.push_back(0.0f);
        }
        std::string str = std::to_string(input[0]);
        std::cout << str << std::endl;
        char* value = const_cast<char*>(str.c_str());
        std::cout << value << std::endl;
        //drawText(value, bounds, 1, BLACK);
        input.clear();
    }

    return 1;
}

void Part::Output(Part* self, float value) {
    std::vector<Port*> portsToProcess;  // New vector to store portsList to process

    // Find the portsList that need to be processed
    for (Port port : portsList) {
        if (port.prev == self) {
            portsToProcess.push_back(&port);
        }
    }

    // Process the portsList
    for (Port* port : portsToProcess) {
        port->next->input.insert(port->next->input.begin() + port->port, value);
        std::cout << port->prev->name << "-->" << value << "-->" << port->next->name << port->next->input[0] << std::endl;
        port->next->onUse();
    }
}

void Part::next(Part* part, int port){
    portsList.push_back(Port(part, port, this));
}

Dial::Dial(int x, int y, int ports) {
    name = "Dial";


    partsList.push_back(this);
    partsInput.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
}

void Dial::onUse() {
    Output(this, voltage);
}

void Dial::set(float voltage) {


    input.push_back(float(voltage));
}

Sensor::Sensor(int x, int y, int ports) {

    name = "Sensor";

    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
}

void Sensor::onUse() {
    std::string str = "";
    for (float val : input) {
        str += std::to_string(val) + " ";
    }
    /*
    str = "sensor: "+ str;
    name = const_cast<char*>(str.c_str());
    */
}

Plus::Plus(int x, int y, int ports) {

    name = "Plus";

    partsList.push_back(this);
    this->position.x = x;
    this->position.y = y;
    this->_ports = ports;
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 75;
}

void Plus::onUse() {

    float voltage = input[0] + input[1];
    Output(this, voltage);


}

Port::Port(Part *next, int port, Part *prev) {
    this->next = next;
    this->port = port;
    this->prev = prev;
    prev->portsOUT.push_back(this);
    next->portsIN.push_back(this);
}
