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
            "Xa",
            "Ya",
            "Za",
            "Xb",
            "Yb",
            "Zb",
            "Xc",
            "Yc",
            "Zc",
    };


    postInitialize();

}


void areaPolygon::onUse() {

    packet output = {.voltage=NAN, .amperage =0};

    std::map<std::string, packet> input = getInputs();

    //    $1/2 * len(A-B) * len(C-B - (A-B)*((C-B * B-A)/len(A-B)^2))$

    Vector3 A = Vector3{
            .x = input["Xa"].voltage,
            .y = input["Ya"].voltage,
            .z = input["Za"].voltage
    };
    Vector3 B = Vector3{
            .x = input["Xb"].voltage,
            .y = input["Yb"].voltage,
            .z = input["Zb"].voltage
    };
    Vector3 C = Vector3{
            .x = input["Xc"].voltage,
            .y = input["Yc"].voltage,
            .z = input["Zc"].voltage
    };

    double out = 0.5 * Vector3Length(Vector3Min(A, B))
                 * Vector3Length(Vector3Min(Vector3Min(C, B),
                                            Vector3Scale(Vector3Min(A, B),
                                                         (Vector3DotProduct(Vector3Min(C,B),
                                                                            Vector3Min(B,A))) / pow(Vector3Length(Vector3Min(A,B)), 2))));

    output.voltage = out;
    Output(output);


}

