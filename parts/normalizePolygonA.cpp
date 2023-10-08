//
// Created by thijm on 08/10/2023.
//


#include "normalizePolygonA.h"

normalizePolygonA::normalizePolygonA(int x, int y, int id) : part(x, y, id) {
    name = "normalizePolygonA";
    dragOut = true;

    this->Ports.push_back("a"); //todo: yes
    updateBounds();

}

void normalizePolygonA::onUse() {
/*
    packet sum = {0,0};

    float za =

    double numerator = (za - zc) * (za * yb - ya * zb) - (za - zb) * (za * ya - ya * zc);
    double denominator = (za * yb - ya * zb) * (za * xc - xa * zc) - (za * xb - xa * zb) * (za * yc - zc * ya);

    if (denominator == 0) {
        std::cerr << "Division by zero is not allowed." << std::endl;
        return 0; // You can handle this case as needed
    }

    return numerator / denominator;

    Output( sum);

*/

}

