//
// Created by Thijme van Son on 30/10/2023.
//

#include "scaleVector.h"
#include <raymath.h>

scaleVector::scaleVector(int x, int y, int id) : part(x, y, id) {
    name = "scaleVector";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
            "v3_Vector",
            "f_Scalar",
    };

    this->portsOutName = std::vector<std::string>{
        "v3_out"
    };


    postInitialize();

}


void scaleVector::onUse() {

    packet output = {._float=NAN};

    std::map<std::string, packet> input = getInputs();

    //    $1/2 * len(A-B) * len(C-B - (A-B)*((C-B * B-A)/len(A-B)^2))$


    Output({._vector3 = Vector3Scale(input["v3_Vector"]._vector3, input["f_Scalar"]._float)}, "v3_out");


}