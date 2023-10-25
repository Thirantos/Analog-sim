//
// Created by Thijme van Son on 11/07/2023.
//

#ifndef ANALOGSIM_SERIALIZER_H
#define ANALOGSIM_SERIALIZER_H
#include "json.hpp"
using json = nlohmann::json;

class serializer {
public:
    static void serialize(std::string filePath);
    json data;

    serializer();
    static void deserialize(std::string filePath);
};


#endif //ANALOGSIM_SERIALIZER_H
