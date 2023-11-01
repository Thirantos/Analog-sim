//
// Created by thijm on 01/11/2023.
//

#include "c24.h"
#include <raymath.h>

c24::c24(int x, int y, int id) : part(x, y, id){
    name = "c24";
    this->portsInName = std::vector<std::string>{
            "v3_u"
            "v3_v"
    };
    this->portsOutName = std::vector<std::string>{
            "v3_w"
    };
    postInitialize();
}

void c24::onUse() {
    std::map<std::string, packet> input = getInputs();

    Vector3 u = input["v3_u"]._vector3;
    Vector3 v = input["v3_v"]._vector3;


    Vector3 vector = Vector3Subtract(u, Vector3Scale(v, (Vector3DotProduct(u, v) / (Vector3Length(v) * Vector3Length(v)))));

    Output({._vector3 = vector}, "v3_w");

}