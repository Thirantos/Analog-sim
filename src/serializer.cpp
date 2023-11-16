//
// Created by Thijme van Son on 11/07/2023.
//

#include "serializer.h"
#include "component.h"
#include <fstream>
#include "json.hpp"
#include <iostream>
#include "matrix.h"
#include <RaylibSerialize.hpp>

using json = nlohmann::json;


#define SERIALIZEPART(part) new part(pos.x, pos.y);

void serializer::serialize(std::string filePath) {

    json parts;
    json ports;
    json Json;

    for (part *part: partsList) {
        part->serialize(&parts);
    }
    for (Port *port: portsList) {
        port->serialize(&ports);
    }
    Json["parts"] = parts;
    Json["ports"] = ports;

    // Write the JSON string to a file or use as desired
    std::ofstream outputFile(filePath);

    outputFile << Json;

    outputFile.close();

}

void serializer::deserialize(std::string filePath) {
    partsList.clear();
    partsProcess.clear();
    partsInput.clear();
    portsList.clear();

    std::ifstream inputFile(filePath);
    json data = json::parse(inputFile);
    if(!data["parts"].is_null()) {
        std::vector<json> partsinjson = data["parts"].template get<std::vector<json>>();
        for (json Part: partsinjson) {

            part *p = constructorFromName(Part["type"].template get<std::string>(),
                                          Part["x"].template get<float>(), Part["y"].template get<float>(),
                                          Part["id"].template get<int>(), Part["data"].is_null() ? nullptr : Part["data"]);
            //std::cout << Part["property"] << std::endl;
        }
    }

    if(!data["ports"].is_null()) {
        std::vector<json> portsinjson = data["ports"].template get<std::vector<json>>();

        for (json port: portsinjson) {
            Port *p = new Port(partFromId(port["next"].template get<int>()), port["port"].template get<int>(),
                               partFromId(port["prev"].template get<int>()), port["id"].template get<int>());


            float valueF = port["valueF"];;
            Vector3 valueV3 = port["valueV3"];


            matrix valueM = matrix::from_json(port["valueM"]);


            p->setValue(
                    {._float = valueF, ._vector3 = valueV3, ._matrix = valueM});
        }
    }
}




serializer::serializer() = default;

