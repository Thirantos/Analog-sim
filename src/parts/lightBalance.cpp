//
// Created by thijm on 16/11/2023.
//

#include "lightBalance.h"

lightBalance::lightBalance(int x, int y, int id) : part(x, y, id){
    name = "lightBalance";
    this->portsInName = std::vector<std::string>{
            "f_in",
            "f_max"

    };
    this->portsOutName = std::vector<std::string>{
            "f_out",
    };
    postInitialize();
}

void lightBalance::onUse() {
    std::map<std::string, packet> input = getInputs();

    Output({._float = (input["f_in"]._float * input["f_max"]._float)/(input["f_in"]._float + input["f_max"]._float)}, "f_out");


}