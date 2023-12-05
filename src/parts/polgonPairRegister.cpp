//
// Created by Thijme van Son on 27/11/2023.
//

#include "polgonPairRegister.h"

polgonPairRegister::polgonPairRegister(int x, int y, int id) : part(x, y, id) {
    name = "polgonPairRegister";
    dragOut = true;
    partsInput.push_back(this);


    this->portsInName = std::vector<std::string>{
        "v_vector",
        "b_visible",
        "v_coordinatesPolygonA",
        "v_coordinatesPointA1",
        "v_coordinatesPointA2",
        "v_coordinatesPointA3",
        "b_normalA",
        "v_coordinatesPolygonB",
        "v_coordinatesPointB1",
        "v_coordinatesPointB2",
        "v_coordinatesPointB3",
        "b_normalB",
        "b_save",
    };
    this->portsOutName = std::vector<std::string>{
            "v_vector",
            "b_visible",
            "v_coordinatesPolygonA",
            "v_coordinatesPointA1",
            "v_coordinatesPointA2",
            "v_coordinatesPointA3",
            "b_normalA",
            "v_coordinatesPolygonB",
            "v_coordinatesPointB1",
            "v_coordinatesPointB2",
            "v_coordinatesPointB3",
            "b_normalB",
    };

    postInitialize();
}