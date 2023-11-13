//
// Created by thijm on 13/11/2023.
//

#ifndef ANALOGSIM_MATRIXKERNEL_H
#define ANALOGSIM_MATRIXKERNEL_H


#include "../component.h"

class matrixKernel : public part{
public:
    matrixKernel(int x, int y, int id = identifierPART);
    void onUse() override;
};


#endif //ANALOGSIM_MATRIXKERNEL_H
