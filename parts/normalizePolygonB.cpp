//
// Created by thijm on 08/10/2023.
//


#include <iostream>
#include "normalizePolygonB.h"


normalizePolygonB::normalizePolygonB(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygonB";
    dragOut = true;


    this->Ports = std::vector<std::string>{
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


void normalizePolygonB::onUse() {

    packet output = {.voltage=NAN, 0};

    std::map<std::string, packet> inputB = getInputs();


//todo: this does the same as A somehow?
    double numeratorB = (inputB["Ya"].voltage - inputB["Yc"].voltage) *
                      (inputB["Ya"].voltage * inputB["Zb"].voltage - inputB["Za"].voltage * inputB["Yb"].voltage) -
                      (inputB["Ya"].voltage - inputB["Yb"].voltage) *
                      (inputB["Ya"].voltage * inputB["Zc"].voltage - inputB["Za"].voltage * inputB["Yc"].voltage);
    double denominatorB = (inputB["Ya"].voltage * inputB["Zb"].voltage - inputB["Za"].voltage * inputB["Yb"].voltage) *
                        (inputB["Ya"].voltage * inputB["Xc"].voltage - inputB["Xa"].voltage * inputB["Yc"].voltage) -
                        (inputB["Ya"].voltage * inputB["Xb"].voltage - inputB["Xa"].voltage * inputB["Yb"].voltage) *
                        (inputB["Ya"].voltage * inputB["Zc"].voltage - inputB["Za"].voltage * inputB["Yc"].voltage);


    double vol = NAN;
    if (denominatorB != 0) {
        vol = numeratorB / denominatorB;
        output.voltage = vol;
    }
    std::cout << "B: " << vol << std::endl;
    Output(output);


}

