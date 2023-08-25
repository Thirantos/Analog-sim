//
// Created by Thijme van Son on 11/07/2023.
//

#ifndef ANALOGSIM_SERIALIZER_H
#define ANALOGSIM_SERIALIZER_H
#include "include/json.hpp"
using json = nlohmann::json;

class serializer {
public:
    static void serialize();
    json data;

    serializer();
};


#endif //ANALOGSIM_SERIALIZER_H
