//
// Created by Thijme van Son on 11/10/2023.
//

#include "dotProduct.h"
#include "raymath.h"

dotProduct::dotProduct(int x, int y, int id) : part(x, y, id) {
    name = "dotProduct";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
        "v3_A",
        "v3_B"
    };


    postInitialize();

}


void dotProduct::onUse() {

    packet output = {._float=NAN};

    std::map<std::string, packet> input = getInputs();

    double dot = Vector3DotProduct(
            input["v3_A"]._vector3 ,
            input["v3_A"]._vector3);

    output._float = dot;
    Output(output);


}