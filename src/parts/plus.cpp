//
// Created by Thijme van Son on 12/07/2023.
//

#include "plus.h"

plus::plus(int x, int y, int id) : part(x, y, id) {
    name = "plus";
    dragOut = true;

    noMaxPorts = true;
    postInitialize();

}

void plus::onUse() {

    packet sum = {0,0};

    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        sum.voltage += port->value().voltage;
        sum.amperage += port->value().amperage;
    }

    Output( sum);


}
