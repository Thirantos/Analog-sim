//
// Created by Thijme van Son on 30/10/2023.
//

#ifndef ANALOGSIM_SCALEVECTOR_H
#define ANALOGSIM_SCALEVECTOR_H
#include "../component.h"


class scaleVector : public part {
public:
    using part::part;


    scaleVector(int x, int y, int id = identifierPART);

    void onUse() override;
};


#endif //ANALOGSIM_SCALEVECTOR_H
