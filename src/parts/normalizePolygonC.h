//
// Created by thijm on 08/10/2023.
//

#ifndef ANALOGSIM_NORMALIZEPOLYGONC_H
#define ANALOGSIM_NORMALIZEPOLYGONC_H




#include "../component.h"


class normalizePolygonC : public part {
public:
        using part::part;


        normalizePolygonC(int x, int y, int id = identifierPART);

        void onUse() override;

};





#endif //ANALOGSIM_NORMALIZEPOLYGONC_H
