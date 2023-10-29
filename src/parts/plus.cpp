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

    packet sum = {0};

    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        sum._float += port->value()._float;
    }

    Output( sum);


}
