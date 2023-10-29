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
        p._float += port->value()._float;
        i += 1;
    }
    p._float = p._float / i;

    Output(p);
}