//
// Created by Thijme van Son on 27/11/2023.
//

#ifndef ANALOGSIM_BOXKERNEL_H
#define ANALOGSIM_BOXKERNEL_H

#include "../component.h"


class boxKernel : public part{
public:
    float size;
    using part::part;
    matrix* kernel;
    boxKernel(int x, int y, int id = identifierPART, int size = 3);
    void onUse() override;

    void draw(Camera2D camera) override;

    void serialize(json* Data, json properties = nullptr) override;
    void menu() override;

};


#endif //ANALOGSIM_BOXKERNEL_H
