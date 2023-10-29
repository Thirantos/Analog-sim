//
// Created by thijm on 18/10/2023.
//


#include <iostream>
#include "areaPolygon.h"
#include "raymath.h"


areaPolygon::areaPolygon(int x, int y, int id) : part(x, y, id) {
    name = "areaPolygon";
    dragOut = true;


    this->portsInName = std::vector<std::string>{
        "v3_A",
        "v3_B",
        "v3_C",
    };


    postInitialize();

}


void areaPolygon::onUse() {

    packet output = {._float=NAN};

    std::map<std::string, packet> input = getInputs();

    //    $1/2 * len(A-B) * len(C-B - (A-B)*((C-B * B-A)/len(A-B)^2))$

    Vector3 A = input["v3_A"]._vector3;
    Vector3 B = input["v3_B"]._vector3;
    Vector3 C = input["v3_C"]._vector3;

    double out = 0.5 * Vector3Length(Vector3Min(A, B))
                 * Vector3Length(Vector3Min(Vector3Min(C, B),
                                            Vector3Scale(Vector3Min(A, B),
                                                         (Vector3DotProduct(Vector3Min(C,B),
                                                                            Vector3Min(B,A))) / pow(Vector3Length(Vector3Min(A,B)), 2))));

    output._float = out;
    Output(output);


}

