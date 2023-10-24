//
// Created by Thijme van Son on 12/07/2023.
//

#ifndef ANALOGSIM_DIAL_H
#define ANALOGSIM_DIAL_H


#include "../component.h"

class dial : public part{
public:
    int val;
    using part::part;

    dial(int x, int y, int id = identifierPART, float value = 0);

    void onUse() override;


    //void draw(camera camera) override;
    void drawIgnoreCam(camera camera) override;
    void serialize(json* Data, json properties = nullptr) override;

};


#endif //ANALOGSIM_DIAL_H
