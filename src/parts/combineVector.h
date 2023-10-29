//
// Created by thijm on 29/10/2023.
//

#ifndef ANALOGSIM_COMBINEVECTOR_H
#define ANALOGSIM_COMBINEVECTOR_H


#include "../component.h"

class combineVector : public part{
public:
    combineVector(int x, int y, int id = identifierPART);
    void onUse() override;

};


#endif //ANALOGSIM_COMBINEVECTOR_H
