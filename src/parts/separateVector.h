//
// Created by thijm on 29/10/2023.
//

#ifndef ANALOGSIM_SEPARATEVECTOR_H
#define ANALOGSIM_SEPARATEVECTOR_H

#include "../component.h"

class separateVector : public part{
public:
    separateVector(int x, int y, int id = identifierPART);
    void onUse() override;
};


#endif //ANALOGSIM_SEPERATEVECTOR_H
