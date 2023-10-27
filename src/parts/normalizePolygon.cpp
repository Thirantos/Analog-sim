//
// Created by thijm on 08/10/2023.
//


#include <iostream>
#include "normalizePolygon.h"


normalizePolygon::normalizePolygon(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygon";
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
    this->portsOutName = std::vector<std::string>{
            "A",
            "B",
            "C",
    };


    postInitialize();

}


void normalizePolygon::onUse() {
    std::map<std::string, packet> input = getInputs();
    

    packet outputA = {.voltage=NAN, .amperage =0};
    packet outputC = {.voltage=NAN, .amperage = 0};
    packet outputB = {.voltage=NAN, .amperage =0};

    
    double numeratorA = (input["Za"].voltage - input["Zc"].voltage) *
                      (input["Za"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Zb"].voltage) -
                      (input["Za"].voltage - input["Zb"].voltage) *
                      (input["Za"].voltage * input["Yc"].voltage - input["Ya"].voltage * input["Zc"].voltage);
    double denominatorA = (input["Za"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Zb"].voltage) *
                        (input["Za"].voltage * input["Xc"].voltage - input["Xa"].voltage * input["Zc"].voltage) -
                        (input["Za"].voltage * input["Xb"].voltage - input["Xa"].voltage * input["Zb"].voltage) *
                        (input["Za"].voltage * input["Yc"].voltage - input["Zc"].voltage * input["Ya"].voltage);
    

    double numeratorB = (input["Za"].voltage - input["Zc"].voltage) *
                        (input["Za"].voltage * input["Xb"].voltage - input["Xa"].voltage * input["Zb"].voltage) -
                        (input["Za"].voltage - input["Zb"].voltage) *
                        (input["Za"].voltage * input["Xc"].voltage - input["Xa"].voltage * input["Zc"].voltage);
    double denominatorB = (input["Za"].voltage * input["Xb"].voltage - input["Xa"].voltage * input["Zb"].voltage) *
                          (input["Za"].voltage * input["Yc"].voltage - input["Ya"].voltage * input["Zc"].voltage) -
                          (input["Za"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Zb"].voltage) *
                          (input["Za"].voltage * input["Xc"].voltage - input["Xa"].voltage * input["Zc"].voltage);

    double numeratorC = (input["Xa"].voltage - input["Xc"].voltage) *
                        (input["Xa"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Xc"].voltage) -
                        (input["Xa"].voltage - input["Xb"].voltage) *
                        (input["Xa"].voltage * input["Yc"].voltage - input["Ya"].voltage * input["Xc"].voltage);
    double denominatorC = (input["Xa"].voltage * input["Yb"].voltage - input["Ya"].voltage * input["Xb"].voltage) *
                          (input["Xa"].voltage * input["Zc"].voltage - input["Za"].voltage * input["Xc"].voltage) -
                          (input["Xa"].voltage * input["Zb"].voltage - input["Za"].voltage * input["Xb"].voltage) *
                          (input["Xa"].voltage * input["Yc"].voltage - input["Xc"].voltage * input["Ya"].voltage);

    double volB = NAN;
    if (denominatorB != 0) {
        volB = numeratorB / denominatorB;
        outputB.voltage = volB;
    }




    double volC = NAN;
    if (denominatorC != 0) {
        volC = numeratorC / denominatorC;
        outputC.voltage = volC;
    }


    double volA = NAN;
    if (denominatorA != 0) {
        volA = numeratorA / denominatorA;
        outputA.voltage = volA;
    }

    Output(outputA, "A");
    Output(outputB, "B");
    Output(outputC, "C");

}

