#include <iostream>
#include <vector>
#include "gui.hpp"
//#include "parts.hpp"
//#include "component.hpp"

int main(){
    Dial dial1(0, 5, 0);
    Dial dial2(50, 10, 0);
    Plus plus1(200, 300, 2);
    Sensor sensor1(106, 4, 1);
    Sensor sensor2(70, 29, 1);
    Sensor sensor3(64, 705, 1);

    for (Part* part : partsInput){
        std::cout << part->name << std::endl;
    }

    dial1.voltage = 0.2f;
    dial2.voltage = 0.5f;
    


    dial1.next(&sensor1, 0);
    dial2.next(&sensor2, 0);
    dial1.next(&plus1, 0);
    dial2.next(&plus1, 1);


    plus1.next(&sensor3, 0);


        
    DrawGui();
    return 0;
    
}

