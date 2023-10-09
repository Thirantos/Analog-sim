//
// Created by Thijme van Son on 20/09/2023.
//

#include "average.h"

average::average(int x, int y, int id) : part(x, y, id) {
    name = "average";
    dragOut = true;

    noMaxPorts = true;
    postInitialize();

}

void average::onUse() {

    packet p;
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