#include "canny.h"


Matrix gen_gaussian_filter(int size, double sigma) {
    Matrix res_filter(size, std::vector<double>(size, 0.0));
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        int x = i - size / 2;
        for (int j = 0; j < size; j++) {
            int y = j - size/2;
            res_filter[i][j] = (1.0/(2.0 * M_PI * sigma * sigma)) * exp(-(x*x + y*y)/(2.0 * sigma * sigma));
            sum += res_filter[i][j];

        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            res_filter[i][j] /= sum;
    }

    return res_filter;
}