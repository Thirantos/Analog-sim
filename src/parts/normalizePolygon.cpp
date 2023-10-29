//
// Created by thijm on 08/10/2023.
//


#include <iostream>
#include "normalizePolygon.h"


normalizePolygon::normalizePolygon(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygon";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
        "v3_A",
        "v3_B",
        "v3_C",
    };
    this->portsOutName = std::vector<std::string>{
            "f_A",
            "f_B",
            "f_C",
    };


    postInitialize();

}


void normalizePolygon::onUse() {
    std::map<std::string, packet> input = getInputs();
    

    packet outputA = {._float=NAN};
    packet outputC = {._float=NAN};
    packet outputB = {._float=NAN};
    
    Vector3 A = input["v3_A"]._vector3;
    Vector3 B = input["v3_B"]._vector3;
    Vector3 C = input["v3_C"]._vector3;
    
    double numeratorA = (A.z - C.z) *
                        (A.z * B.y - A.y * B.z) -
                        (A.z - B.z) *
                        (A.z * C.y - A.y * C.z);
    double denominatorA = (A.z * B.y - A.y * B.z) *
                          (A.z * C.x - A.x * C.z) -
                          (A.z * B.x - A.x * B.z) *
                          (A.z * C.y - C.z * A.y);
    

    double numeratorB = (A.z - C.z) *
                        (A.z * B.x - A.x * B.z) -
                        (A.z - B.z) *
                        (A.z * C.x - A.x * C.z);
    double denominatorB = (A.z * B.x - A.x * B.z) *
                          (A.z * C.y - A.y * C.z) -
                          (A.z * B.y - A.y * B.z) *
                          (A.z * C.x - A.x * C.z);

    double numeratorC = (A.x - C.x) *
                        (A.x * B.y - A.y * C.x) -
                        (A.x - B.x) *
                        (A.x * C.y - A.y * C.x);
    double denominatorC = (A.x * B.y - A.y * B.x) *
                          (A.x * C.z - A.z * C.x) -
                          (A.x * B.z - A.z * B.x) *
                          (A.x * C.y - C.x * A.y);

    double volB = NAN;
    if (denominatorB != 0) {
        volB = numeratorB / denominatorB;
        outputB._float = volB;
    }




    double volC = NAN;
    if (denominatorC != 0) {
        volC = numeratorC / denominatorC;
        outputC._float = volC;
    }


    double volA = NAN;
    if (denominatorA != 0) {
        volA = numeratorA / denominatorA;
        outputA._float = volA;
    }

    Output(outputA, "f_A");
    Output(outputB, "f_B");
    Output(outputC, "f_C");

}

