//
// Created by Thijme van Son on 12/07/2023.
//

#include "sensor.h"
#include "../settings.h"

sensor::sensor(int x, int y, int id) : part(x, y, id) {
    name = "sensor";

    this->Ports.push_back("input");

    postInitialize();
}

void sensor::onUse() {

}

void sensor::draw(Camera2D camera){
    part::draw(camera);

    std::string str = "DISCONNECTED";
    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        str = std::to_string(port->value().voltage);
    }

    //std::cout << str << std::endl;
    //std::cout << value << std::endl;

    DrawText(str.c_str(), bounds.x + (bounds.width - MeasureText(str.c_str(), FONTSIZE*0.7))/2,
             inBounds[0].y + inBounds[0].height/2 - FONTSIZE*0.7,  FONTSIZE*0.7, RED);
}

