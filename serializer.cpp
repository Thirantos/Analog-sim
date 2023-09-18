//
// Created by Thijme van Son on 11/07/2023.
//

#include "serializer.h"
#include "component.h"
#include <fstream>
#include "include/json.hpp"
using json = nlohmann::json;

void serializer::serialize() {

    json parts;
    json ports;
    json Json;

    for (part* part : partsList) {
        part->serialize(&parts);
    }
    for (Port* port : portsList) {
        port->serialize(&ports);
    }
    Json["parts"] = parts;
    Json["ports"] = ports;

    // Write the JSON string to a file or use as desired
    std::ofstream outputFile("SAVE.json");

    outputFile << Json;

    outputFile.close();

}

serializer::serializer() = default;

