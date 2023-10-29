//
// Created by thijm on 29/10/2023.
//

#include "combineVector.h"

combineVector::combineVector(int x, int y, int id) : part(x, y, id){
    name = "combineVector";
    this->portsInName = std::vector<std::string>{
        "f_X",
        "f_Y",
        "f_Z"
    };
    this->portsOutName = std::vector<std::string>{
            "v3_out"
    };
    postInitialize();
}

void combineVector::onUse() {
    std::map<std::string, packet> input = getInputs();
    Output({._vector3 = {input["f_X"]._float, input["f_Y"]._float, input["f_Z"]._float}}, "v3_out");
}
