//
// Created by thijm on 01/11/2023.
//

#include "vectorBetweenVectors.h"
#include <raymath.h>


vectorBetweenVectors::vectorBetweenVectors(int x, int y, int id) : part(x, y, id){
    name = "vectorBetweenVectors";
    this->portsInName = std::vector<std::string>{
            "v3_from"
            "v3_to"
    };
    this->portsOutName = std::vector<std::string>{
            "v3_out"
    };
    postInitialize();
}

void vectorBetweenVectors::onUse() {
    std::map<std::string, packet> input = getInputs();

    Vector3 vector = Vector3Subtract(input["v3_to"]._vector3, input["v3_from"]._vector3);

    Output({._vector3 = vector}, "v3_out");

}