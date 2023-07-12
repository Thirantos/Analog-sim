//
// Created by Thijme van Son on 12/07/2023.
//

#include "sensor.h"
#include "../settings.h"

sensor::sensor(int x, int y, int id) : part(x, y, id) {
    name = "sensor";

    this->_ports = 1;

}

void sensor::onUse() {

}

void sensor::draw(){
    part::draw();

    std::string str = "DISCONNECTED";
    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        str = std::to_string(port->value());
    }

    //std::cout << str << std::endl;
    //std::cout << value << std::endl;

    DrawText(str.c_str(), dragBounds.x + (bounds.width - MeasureText(str.c_str(), FONTSIZE*0.7))/2,
             dragBounds.y + dragBounds.height,  FONTSIZE*0.7, RED);
}

