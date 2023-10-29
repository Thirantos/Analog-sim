//
// Created by thijm on 29/10/2023.
//

#include "separateVector.h"
separateVector::separateVector(int x, int y, int id) : part(x, y, id){
    name = "separateVector";
    this->portsInName = std::vector<std::string>{
        "v3_in"
    };
    this->portsOutName = std::vector<std::string>{
            "f_X",
            "f_Y",
            "f_Z"
    };
    postInitialize();
}

void separateVector::onUse() {
    std::map<std::string, packet> input = getInputs();
    Output({._float = input["v3_in"]._vector3.x}, "f_X");
    Output({._float = input["v3_in"]._vector3.y}, "f_Y");
    Output({._float = input["v3_in"]._vector3.z}, "f_Z");

}