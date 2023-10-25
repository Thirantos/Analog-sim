//
// Created by Thijme van Son on 12/07/2023.
//

#ifndef ANALOGSIM_PLUS_H
#define ANALOGSIM_PLUS_H


#include "../component.h"


class plus : public part {
public:
    using part::part;


    plus(int x, int y, int id = identifierPART);

    void onUse() override;

};



#endif //ANALOGSIM_PLUS_H
