//
// Created by Thijme van Son on 11/07/2023.
//

#include "serializer.h"
#include "component.h"
#include <fstream>


void serializer::serialize() {


        // Write the JSON string to a file or use as desired
        std::ofstream outputFile("SAVE.json");
        outputFile.close();

}