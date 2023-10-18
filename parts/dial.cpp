//
// Created by Thijme van Son on 12/07/2023.
//

#include <cmath>
#include "dial.h"
#include "raymath.h"


dial::dial(int x, int y, int id, float value) : part(x, y, id) {
    name = "dial";
    dragOut = true;

    val = value;

    partsInput.push_back(this);

    this->Ports.clear();
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


void dial::drawIgnoreCam(Camera2D camera) {
    part::drawIgnoreCam(camera);
    Rectangle _spinner = bounds;

    _spinner.height *= 0.5f;
    _spinner.width *= 0.7f;

    _spinner.y += _spinner.height * 0.7f;
    _spinner.x += bounds.width * 0.15f;
    _spinner = cameraDisplace(_spinner, camera);

    GuiSpinner(_spinner, "", &val, 0, 500, false);
}

void dial::serialize(json *Data, json prop){
    json properties;
    properties["value"]  = val;
    part::serialize(Data, properties);
}


