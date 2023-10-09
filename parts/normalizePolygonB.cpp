//
// Created by thijm on 08/10/2023.
//


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

    std::map<std::string, packet> input = getInputs();


//todo: this does the same as A somehow?
    double numeratorB = (input["Ya"].voltage - input["Yc"].voltage) *
                      (input["Ya"].voltage * input["Zb"].voltage - input["Za"].voltage * input["Yb"].voltage) -
                      (input["Ya"].voltage - input["Yb"].voltage) *
                      (input["Ya"].voltage * input["Zc"].voltage - input["Za"].voltage * input["Yc"].voltage);
    double denominatorB = (input["Ya"].voltage * input["Zb"].voltage - input["Za"].voltage * input["Yb"].voltage) *
                        (input["Ya"].voltage * input["Xc"].voltage - input["Xa"].voltage * input["Yc"].voltage) -
                        (input["Ya"].voltage * input["Xb"].voltage - input["Xa"].voltage * input["Yb"].voltage) *
                        (input["Ya"].voltage * input["Zc"].voltage - input["Za"].voltage * input["Yc"].voltage);

    if (denominatorB != 0) {
        output.voltage = numeratorB / denominatorB;
    }

    Output(output);


}

