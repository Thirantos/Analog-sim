//
// Created by thijm on 16/11/2023.
//

#ifndef ANALOGSIM_LIGHTBALANCE_H
#define ANALOGSIM_LIGHTBALANCE_H


#include "../component.h"

class lightBalance : public part{
public:
    lightBalance(int x, int y, int id = identifierPART);
    void onUse() override;
};


#endif //ANALOGSIM_LIGHTBALANCE_H
