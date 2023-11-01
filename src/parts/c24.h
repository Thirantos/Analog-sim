//
// Created by thijm on 01/11/2023.
//

#ifndef ANALOGSIM_C24_H
#define ANALOGSIM_C24_H


#include "../component.h"

class c24 : public part{
public:
    c24(int x, int y, int id = identifierPART);
    void onUse() override;
};

#endif //ANALOGSIM_C24_H
