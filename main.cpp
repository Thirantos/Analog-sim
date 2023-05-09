#include <iostream>
#include <vector>
#include "include/raylib.h"
#include "gui.hpp"
// #include "parts.hpp"
#include "component.hpp"

int main()
{
    std::vector<Part*> Inputs;
    component dial1 = component(0, 0, Dial(), 0);
    component dial2 = component(0, 0, Dial(), 0);
    dial1.part.input[0] = 0.5f;
    dial2.part.input[0] = 0.2f;

    component plus1 = component(0, 0, Plus(), 2);

    component sensor1 = component(0, 0, Sensor(), 1);
    component sensor2 = component(0, 0, Sensor(), 1);
    component sensor3 = component(0, 0, Sensor(), 1);


    dial1.part.next(&sensor1.part, 0);
    dial2.part.next(&sensor2.part, 0);

    dial1.part.next(&plus1.part, 0);
    dial2.part.next(&plus1.part, 1);


    plus1.part.next(&sensor3.part, 0);

    Inputs.push_back(&dial1.part);
    Inputs.push_back(&dial2.part);


    for(Part* part: Inputs){
        part->onUse();
    }
    
    drawGui();

    return 0;
}
