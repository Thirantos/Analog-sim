//
// Created by thijm on 01/11/2023.
//

#ifndef ANALOGSIM_VECTORBETWEENVECTORS_H
#define ANALOGSIM_VECTORBETWEENVECTORS_H


#include "../component.h"

class vectorBetweenVectors : public part{
public:
    vectorBetweenVectors(int x, int y, int id = identifierPART);
    void onUse() override;
};



#endif //ANALOGSIM_VECTORBETWEENVECTORS_H
