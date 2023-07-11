//
// Created by Thijme van Son on 11/07/2023.
//

#ifndef ANALOGSIM_SERIALIZER_H
#define ANALOGSIM_SERIALIZER_H
#include "rapidjson/document.h"

class serializer {
public:
    rapidjson::Document serialized;
    void serialize();
};


#endif //ANALOGSIM_SERIALIZER_H
