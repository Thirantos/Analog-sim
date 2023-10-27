//
// Created by thijm on 08/10/2023.
//


#include <iostream>
#include "normalizePolygonC.h"


normalizePolygonC::normalizePolygonC(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygonC";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
            "Xa",
            "Ya",
            "Za",
            "Xb",
            "Yb",
            "Zb",
            "Xc",
            "Yc",
            "Zc",
    };


    postInitialize();

}


void normalizePolygonC::onUse() {

    packet output = {.voltage=NAN, .amperage = 0};

    std::map<std::string, packet> input = getInputs();

    double numeratorC = (input["Xa"].voltage - input["Xc"].voltage) *
                      (input["Xa"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Xc"].voltage) -
                      (input["Xa"].voltage - input["Xb"].voltage) *
                      (input["Xa"].voltage * input["Yc"].voltage - input["Ya"].voltage * input["Xc"].voltage);
    double denominatorC = (input["Xa"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Xb"].voltage) *
                        (input["Xa"].voltage * input["Zc"].voltage - input["Za"].voltage * input["Xc"].voltage) -
                        (input["Xa"].voltage * input["Zb"].voltage - input["Za"].voltage * input["Xb"].voltage) *
                        (input["Xa"].voltage * input["Yc"].voltage - input["Xc"].voltage * input["Ya"].voltage);

    double vol = NAN;
    if (denominatorC != 0) {
        vol = numeratorC / denominatorC;
        output.voltage = vol;
    }
    Output(output);


}

