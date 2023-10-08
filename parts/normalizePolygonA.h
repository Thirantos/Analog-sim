//
// Created by thijm on 08/10/2023.
//

#ifndef ANALOGSIM_NORMALIZEPOLYGONA_H
#define ANALOGSIM_NORMALIZEPOLYGONA_H




#include "../component.h"


class normalizePolygonA : public part {
public:
        using part::part;


        normalizePolygonA(int x, int y, int id = identifierPART);

        void onUse() override;

};





#endif //ANALOGSIM_NORMALIZEPOLYGONA_H
