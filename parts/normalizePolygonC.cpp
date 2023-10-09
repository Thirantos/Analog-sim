//
// Created by thijm on 08/10/2023.
//


#include "normalizePolygonC.h"


normalizePolygonC::normalizePolygonC(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygonC";
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


void normalizePolygonC::onUse() {

    packet output = {.voltage=NAN, 0};

    std::map<std::string, packet> input = getInputs();

    double numeratorA = (input["Za"].voltage - input["Zc"].voltage) *
                      (input["Za"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Zb"].voltage) -
                      (input["Za"].voltage - input["Zb"].voltage) *
                      (input["Za"].voltage * input["Yc"].voltage - input["Ya"].voltage * input["Zc"].voltage);
    double denominatorA = (input["Za"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Zb"].voltage) *
                        (input["Za"].voltage * input["Xc"].voltage - input["Xa"].voltage * input["Zc"].voltage) -
                        (input["Za"].voltage * input["Xb"].voltage - input["Xa"].voltage * input["Zb"].voltage) *
                        (input["Za"].voltage * input["Yc"].voltage - input["Zc"].voltage * input["Ya"].voltage);

    if (denominatorA != 0) {
        output.voltage = numeratorA / denominatorA;
    }

    Output(output);


}

