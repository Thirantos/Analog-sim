//
// Created by Thijme van Son on 02/11/2023.
//

#ifndef ANALOGSIM_MATRIX_H
#define ANALOGSIM_MATRIX_H

#include <vector>


class matrix {
    std::vector<std::vector<float>>matrixValue;

public:
    matrix(int xsize, int ysize);
    float* at(int x, int y);
    void set(int x, int y, float f);


    matrix operator%(matrix kernel); //matrix convolution
    matrix operator*(matrix other);  //matrix multiplication


};


#endif //ANALOGSIM_MATRIX_H