//
// Created by Thijme van Son on 30/10/2023.
//

#ifndef ANALOGSIM_MIDDLEPOLYGON_H
#define ANALOGSIM_MIDDLEPOLYGON_H

#include "../component.h"

class middlePolygon : public part {
public:
    using part::part;


    middlePolygon(int x, int y, int id = identifierPART);

    void onUse() override;

};


#endif //ANALOGSIM_MIDDLEPOLYGON_H
