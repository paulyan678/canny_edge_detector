#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

#define H 0.0
#define V 1.0
#define PD 2.0
#define ND 3.0
#define LOW_THRESHOLD_RATIO 0.005
#define HIGH_THRESHOLD_RATIO 0.09
#define WEAK 25
#define STRONG 255

using Matrix = std::vector<std::vector<double>>;

using Int_Matrix = std::vector<std::vector<int>>;

const Matrix SOBEL_X = {{-1, 0, 1},
                        {-2, 0, 2},
                        {-1, 0, 1}};

const Matrix SOBEL_Y = {{-1, -2, -1},
                        {0, 0, 0},
                        {1, 2, 1}};


Matrix correlate(const Matrix& img, const Matrix& kernel, const std::string& mode);
Matrix gen_gaussian_filter(int size, double sigma);

inline double abs_double(double x) {
    return (x < 0.0) ? -x : x;
}

