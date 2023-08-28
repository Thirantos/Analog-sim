//
// Created by Thijme van Son on 12/07/2023.
//

#include <cmath>
#include "dial.h"
#include "raymath.h"


dial::dial(int x, int y) : part(x, y) {
    name = "dial";
    dragOut = true;

    val = 0;

    partsInput.push_back(this);

    this->maxPorts = 0;

}

void dial::onUse() {
    int v = val;
    Output(Signal{float(v), 1/float(v)});
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

    GuiSpinner(_spinner, "", &val, 0, INFINITY, false);
}


