#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <omp.h>
#include <iostream>

#define H 0.0
#define V 1.0
#define PD 2.0
#define ND 3.0
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
Int_Matrix threshold(Matrix grad_mag, double high_thres_ratio, double low_thres_ratio);
Matrix get_grad_mag(const Matrix& grad_x, const Matrix& grad_y);
Matrix get_grad_angle(const Matrix& grad_x, const Matrix& grad_y);
Int_Matrix hysteresis(const Int_Matrix& grad_mag);
Matrix supress(const Matrix& grad_mag, const Matrix& grad_angle);


inline double abs_double(double x) {
    return (x < 0.0) ? -x : x;
}






