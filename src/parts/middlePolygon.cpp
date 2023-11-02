//
// Created by Thijme van Son on 30/10/2023.
//

#include "middlePolygon.h"
#include <raymath.h>

middlePolygon::middlePolygon(int x, int y, int id) : part(x, y, id) {
    name = "middlePolygon";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
            "v3_A",
            "v3_B",
            "v3_C",
    };

    this->portsOutName = std::vector<std::string>{
            "v3_out"
    };


    postInitialize();

}


void middlePolygon::onUse() {

    std::map<std::string, packet> input = getInputs();

    Vector3 a = Vector3Scale(Vector3Add(Vector3Add(input["v3_A"]._vector3, input["v3_B"]._vector3), input["v3_C"]._vector3), 1/3);


    Output({._vector3 = a}, "v3_out");

}