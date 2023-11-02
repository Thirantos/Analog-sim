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

    matrix operator*(matrix kernel); //matrix convolution of multiplication

};


#endif //ANALOGSIM_MATRIX_H
