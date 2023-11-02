//
// Created by Thijme van Son on 12/07/2023.
//

#include <cmath>
#include "dial.h"
#include "raymath.h"
#include <ImGui.h>
#include <string>
#include <sstream>


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
    if (ImGui::CollapsingHeader((std::string(name) + "##" + std::to_string(id)).c_str())) {

        std::stringstream value("Value##" + std::to_string(id));

        ImGui::SliderFloat(value.str().c_str(), &val, 0, 100);
    }
}


