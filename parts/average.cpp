//
// Created by Thijme van Son on 20/09/2023.
//

#include "average.h"

average::average(int x, int y, int id) : part(x, y, id) {
    name = "average";
    dragOut = true;

    this->maxPorts = -1;
    updateBounds();

}

void average::onUse() {

    packet p;
    float a = 0;
    float i = 0;

    for(Port* port : portsList){
        if(port->nextPart != this) continue;
        p.amperage += port->value().amperage;
        p.voltage += port->value().voltage;
        i += 1;
    }
    p.amperage = p.amperage/i;
    p.voltage = p.voltage/i;

    Output(p);
}