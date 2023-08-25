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

    float sum = 0;

    for (Port* port : portsList) {
        if(port->nextPart != this) continue;
        sum += port->value();
    }


    float voltage = sum;
    Output( voltage);


}
