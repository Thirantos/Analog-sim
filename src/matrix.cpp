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

    return &matrixValue[x % matrixValue.size()][y % matrixValue[x].size()];  // wrap edge handling
}

void matrix::set(int x, int y, float f) {

    matrixValue[x % matrixValue.size()][y % matrixValue[x].size()] = f;  // wrap edge handling
}

matrix matrix::operator%(matrix kernel) {
    matrix output(matrixValue.size(), matrixValue[0].size());

    for (int x = 0; x < matrixValue.size(); ++x) {
        for (int y = 0; y < matrixValue[x].size(); ++y) {


            float f = *this->at(x, y);
            int centerX = kernel.matrixValue.size()/2;
            int centerY = kernel.matrixValue[0].size()/2;

            for (int x2 = 0; x2 < kernel.matrixValue.size(); ++x2) {
                for (int y2 = 0; y2 < kernel.matrixValue[x2].size(); ++y2) {
                    f += *kernel.at(x2, y2) * *this->at(x - centerX + x2, y - centerY + y2);
                }
            }

            output.set(x, y, f);

        }
    }


    return output;
}

nlohmann::json matrix::to_json(nlohmann::json &j) {
    //matrix
    matrix *opt = this;

    std::vector<float> data;
    for (int x = 0; x < opt->sizeX; ++x) {
        for (int y = 0; y < opt->sizeY; ++y) {
            data.push_back(*opt->at(x, y));
        }
    }

    j["matrix"] = {
            {"sizeX", opt->sizeX},
            {"sizeY", opt->sizeY},
            {"data",  data},
    };
    return j;
}


matrix matrix::from_json(nlohmann::json &j) {
    const nlohmann::json &json = j.at("matrix");
    matrix opt = matrix(json.at("sizeX").get<int>(), json.at("sizeY").get<int>());


    std::vector<float> data = json.at("data").get<std::vector<float>>();


    int i = 0;
    for (int x = 0; x < opt.sizeX; ++x) {
        for (int y = 0; y < opt.sizeY; ++y) {
            opt.set(x, y, data[i]);
            i++;
        }
    }
    return opt;

}



