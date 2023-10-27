//
// Created by thijm on 08/10/2023.
//

#ifndef ANALOGSIM_NORMALIZEPOLYGON_H
#define ANALOGSIM_NORMALIZEPOLYGON_H




#include "../component.h"


class normalizePolygon : public part {
public:
        using part::part;


        normalizePolygon(int x, int y, int id = identifierPART);

        void onUse() override;

};





#endif //ANALOGSIM_NORMALIZEPOLYGON_H
