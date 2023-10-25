//
// Created by Thijme van Son on 20/09/2023.
//

#ifndef ANALOGSIM_AVERAGE_H
#define ANALOGSIM_AVERAGE_H


#include "../component.h"

class average : public part {
public:
    using part::part;

    average(int x, int y, int id = identifierPART);

    void onUse() override;

};


#endif //ANALOGSIM_AVERAGE_H
