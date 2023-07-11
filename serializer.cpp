//
// Created by Thijme van Son on 11/07/2023.
//

#include "serializer.h"
#include "component.h"
#include <fstream>
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include <cstdio>

using namespace rapidjson;

void serializer::serialize() {

        rapidjson::Value parts(rapidjson::kObjectType);

        for (Part* part : partsList) {
            rapidjson::Value partObject(rapidjson::kObjectType);

            partObject.AddMember("type", PART_PLUS, serialized.GetAllocator());
            partObject.AddMember("value", part->val, serialized.GetAllocator());

            parts.AddMember(std::to_string(part->id), partObject, serialized.GetAllocator());
        }

        serialized.SetObject();
        serialized.AddMember("parts", parts, serialized.GetAllocator());

        // Convert the serialized JSON to a string
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        serialized.Accept(writer);
        std::string jsonStr = buffer.GetString();

        // Write the JSON string to a file or use as desired
        std::ofstream outputFile("SAVE.json");
        outputFile << jsonStr;
        outputFile.close();

}