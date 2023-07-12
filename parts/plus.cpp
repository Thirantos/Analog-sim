//
// Created by Thijme van Son on 12/07/2023.
//

#include "plus.h"

plus::plus(int x, int y, int id) : part(x,y,id) {
    name = "Plus";


    this->_ports = -1;

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
