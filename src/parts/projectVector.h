//
// Created by thijm on 01/11/2023.
//

#ifndef ANALOGSIM_PROJECTVECTOR_H
#define ANALOGSIM_PROJECTVECTOR_H


#include "../component.h"

class projectVector : public part{
public:
    projectVector(int x, int y, int id = identifierPART);
    void onUse() override;
};




#endif //ANALOGSIM_PROJECTVECTOR_H
