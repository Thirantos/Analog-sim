//
// Created by Thijme van Son on 02/11/2023.
//

#ifndef ANALOGSIM_MATRIX_H
#define ANALOGSIM_MATRIX_H
#include <json.hpp>
#include <vector>


class matrix {
    std::vector<std::vector<float>>matrixValue;

public:
    int sizeX;
    int sizeY;
    matrix(int xsize, int ysize);
    float* at(int x, int y);
    void set(int x, int y, float f);


    matrix operator%(matrix kernel); //matrix convolution
    matrix operator*(matrix other);  //matrix multiplication
    nlohmann::json to_json(nlohmann::json &j);
    static matrix from_json(nlohmann::json &j);


};


#endif //ANALOGSIM_MATRIX_H
