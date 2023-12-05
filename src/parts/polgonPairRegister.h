//
// Created by Thijme van Son on 27/11/2023.
//

#ifndef ANALOGSIM_POLGONPAIRREGISTER_H
#define ANALOGSIM_POLGONPAIRREGISTER_H

#include "../component.h"

class polgonPairRegister : public part{
public:
    float val;
    using part::part;

    polgonPairRegister(int x, int y, int id = identifierPART);

    //void onUse() override;


    //void deserialize(); //todo: deserialize
    //void serialize(json* Data, json properties = nullptr) override;
    //void menu() override;

};


#endif //ANALOGSIM_POLGONPAIRREGISTER_H
