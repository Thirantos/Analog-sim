//
// Created by thijm on 01/11/2023.
//

#include "projectVector.h"
#include <raymath.h>


projectVector::projectVector(int x, int y, int id) : part(x, y, id){
    name = "projectVector";
    this->portsInName = std::vector<std::string>{
            "v3_project"
            "v3_on"
    };
    this->portsOutName = std::vector<std::string>{
            "v3_out"
    };
    postInitialize();
}

void projectVector::onUse() {
    std::map<std::string, packet> input = getInputs();

    Vector3 vector = Vector3Project(input["v3_to"]._vector3, input["v3_from"]._vector3);

    Output({._vector3 = vector}, "v3_out");

}