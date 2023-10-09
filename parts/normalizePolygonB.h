//
// Created by thijm on 08/10/2023.
//

#ifndef ANALOGSIM_NORMALIZEPOLYGONB_H
#define ANALOGSIM_NORMALIZEPOLYGONB_H




#include "../component.h"


class normalizePolygonB : public part {
public:
        using part::part;


        normalizePolygonB(int x, int y, int id = identifierPART);

        void onUse() override;

};





#endif //ANALOGSIM_NORMALIZEPOLYGONB_H
