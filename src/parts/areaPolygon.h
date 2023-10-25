//
// Created by thijm on 18/10/2023.
//

#ifndef ANALOGSIM_AREAPOLYGON_H
#define ANALOGSIM_AREAPOLYGON_H


#include "../component.h"


class areaPolygon : public part {
public:
    using part::part;


    areaPolygon(int x, int y, int id = identifierPART);

    void onUse() override;

};


#endif //ANALOGSIM_AREAPOLYGON_H
