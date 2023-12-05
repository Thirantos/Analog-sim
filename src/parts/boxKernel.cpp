//
// Created by Thijme van Son on 27/11/2023.
//

#include "boxKernel.h"
#include <imgui.h>
#include "../matrix.h"
#include <string>
#include <sstream>

matrix* boxBlur(int size){
    matrix matrix(size,size);
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            matrix.set(x,y, 1/(size*size));
        }
    }
    return &matrix;
}

boxKernel::boxKernel(int x, int y, int id, int size) : part(x, y, id) {
    name = "boxKernel";
    dragOut = true;
    this->portsOutName = std::vector<std::string>{
            "m_out"
    };
    size = size;
    kernel = boxBlur(size);
    partsInput.push_back(this);

    this->portsInName.clear();
    postInitialize();
}

void boxKernel::onUse() {
    int size = int(size);

    packet p = {._matrix = *kernel};
    Output(p);
}

void boxKernel::draw(Camera2D camera) {
    part::draw(camera);

}


void boxKernel::serialize(json *Data, json prop){
    json properties;
    properties["size"]  = size;
    part::serialize(Data, properties);
}

void boxKernel::menu(){
    if (ImGui::CollapsingHeader((std::string(name) + "##" + std::to_string(id)).c_str())) {

        std::stringstream value("Size##" + std::to_string(id));
        int newsize = size;
        ImGui::SliderInt(value.str().c_str(), &newsize, 0, 100);
        if(newsize != size){
            size = newsize;
            kernel = boxBlur(size);


        }

    }
}

