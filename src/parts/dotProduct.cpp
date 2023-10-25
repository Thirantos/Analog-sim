//
// Created by Thijme van Son on 11/10/2023.
//

#include "dotProduct.h"
#include "raymath.h"

dotProduct::dotProduct(int x, int y, int id) : part(x, y, id) {
    name = "dotProduct";
    dragOut = true;


    this->Ports = std::vector<std::string>{
            "Xa",
            "Ya",
            "Za",
            "Xb",
            "Yb",
            "Zb",
    };


    postInitialize();

}


void dotProduct::onUse() {

    packet output = {.voltage=NAN, .amperage =0};

    std::map<std::string, packet> input = getInputs();

    double dot = Vector3DotProduct(
            {input["Xa"].voltage,input["Ya"].voltage,input["Za"].voltage },
            {input["Xb"].voltage,input["Yb"].voltage,input["Zb"].voltage });

    output.voltage = dot;
    Output(output);


}