#include <iostream>
#include <vector>
#include "include/raylib.h"
#include "gui.hpp"
#include "parts.hpp"
#include "component.hpp"

int main()
{
    std::vector<Part*> Inputs;
    Dial dial1;
    Dial dial2;
    dial1.voltage = 0.5f;
    dial2.voltage = 0.2f;

    Plus plus1;

    Sensor sensor1;
    Sensor sensor2;
    Sensor sensor3;

    dial1.next(&sensor1, 0);
    dial2.next(&sensor2, 0);

    dial1.next(&plus1, 0);
    dial2.next(&plus1, 1);


    plus1.next(&sensor3, 0);

    Inputs.push_back(&dial1);
    Inputs.push_back(&dial2);

    component comp = component(0,0, dial1, 0);

    for(Part* part: Inputs){
        part->onUse();
    }
    
    drawGui();

    return 0;
}
