//
// Created by thijm on 13/11/2023.
//

#include "matrixKernel.h"
#include "../matrix.h"

matrixKernel::matrixKernel(int x, int y, int id) : part(x, y, id){
    name = "matrixKernel";
    this->portsInName = std::vector<std::string>{
            "m_a"
            "m_b"
    };
    this->portsOutName = std::vector<std::string>{
            "m_out"
    };
    postInitialize();
}

void matrixKernel::onUse() {
    std::map<std::string, packet> input = getInputs();


    Output({._matrix = input["m_a"]._matrix % input["m_b"]._matrix}, "m_out");

}