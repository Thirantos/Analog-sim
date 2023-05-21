#include <iostream>
#include <vector>
#include "gui.hpp"
//#include "parts.hpp"
//#include "component.hpp"


int main()
{
    std::vector<Component*> Inputs;
    Component dial1(0, 5, new Dial(), 0);
    Component dial2(5, 10, new Dial(), 0);
    dial1.part->input.assign(0.5, 0);
    dial2.part->input.assign(0.2, 0);

    Component plus1(20,30, new Plus(), 2);

    Component sensor1(16, 4,  new Sensor(), 1);
    Component sensor2(70, 29, new Sensor(), 1);
    Component sensor3(64, 75, new Sensor(), 1);


    dial1.part->next(&sensor1, 0);
    dial2.part->next(&sensor2, 0);
    dial1.part->next(&plus1, 0);
    dial2.part->next(&plus1, 1);


    plus1.part->next(&sensor3, 0);

    Inputs.push_back(&dial1);
    Inputs.push_back(&dial2);


    for(Component* comp: Inputs){
        comp->part->onUse();
    }
    
    drawGui();

    return 0;
}
