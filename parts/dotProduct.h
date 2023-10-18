//
// Created by Thijme van Son on 11/10/2023.
//



#ifndef ANALOGSIM_DOTPRODUCT_H
#define ANALOGSIM_DOTPRODUCT_H

#include "../component.h"


class dotProduct : public part {
public:
    using part::part;


    dotProduct(int x, int y, int id = identifierPART);

    void onUse() override;

};



#endif //ANALOGSIM_DOTPRODUCT_H
