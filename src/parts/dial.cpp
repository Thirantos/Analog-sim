//
// Created by Thijme van Son on 12/07/2023.
//

#include <cmath>
#include "dial.h"
#include "raymath.h"
#include <ImGui.h>


dial::dial(int x, int y, int id, float value) : part(x, y, id) {
    name = "dial";
    dragOut = true;

    val = value;

    partsInput.push_back(this);

    this->portsInName.clear();
    postInitialize();
}

void dial::onUse() {
    float v = float(val);

    packet p = {v, 1/v};
    Output(p);
}

void dial::draw(Camera2D camera) {
    part::draw(camera);

}


void dial::serialize(json *Data, json prop){
    json properties;
    properties["value"]  = val;
    part::serialize(Data, properties);
}

void dial::menu(){
    part::menu();
    ImGui::SliderFloat("Value", &val, 0, 100);

}


