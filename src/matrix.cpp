//
// Created by Thijme van Son on 02/11/2023.
//

#include "matrix.h"

matrix::matrix(int xsize, int ysize) {
    std::vector<std::vector<float>> xvec;
    for (int x = 0; x < xsize; ++x) {
        std::vector<float> yvec;
        for (int y = 0; y < ysize; ++y) {
            yvec.push_back(0);
        }
        xvec.push_back(yvec);
    }
    matrixValue = xvec;
}
float *matrix::at(int x, int y) {
    return &matrixValue[x][y];
}
