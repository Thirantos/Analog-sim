//
// Created by Thijme van Son on 12/07/2023.
//

#include "plus.h"

plus::plus(int x, int y) : part(x, y) {
    name = "Plus";
    dragOut = true;

    this->maxPorts = -1;
    updateBounds();

}

void plus::onUse() {

    float sumA = 0;
    float sumV = 0;

    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        sumA += port->value().amperage;
        sumV += port->value().voltage;

    }


    Output( Signal{sumA, sumV});


}
