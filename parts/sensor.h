//
// Created by Thijme van Son on 12/07/2023.
//

#ifndef ANALOGSIM_SENSOR_H
#define ANALOGSIM_SENSOR_H


#include "../component.h"

class sensor : public part{
public:
    using part::part;
    sensor(int x, int y);
    void onUse() override;

    void draw(Camera2D camera) override;
};


#endif //ANALOGSIM_SENSOR_H
