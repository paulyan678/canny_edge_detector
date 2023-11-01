#include "canny.h"

static double find_max(Matrix A) {
    double max = A[0][0];
    for (uint i = 0; i < A.size(); i++) {
        for (uint j = 0; j < A[0].size(); j++) {
            if (A[i][j] > max)
                max = A[i][j];
        }
    }
    return max;
}



Int_Matrix threshold(Matrix grad_mag, double high_thres_ratio, double low_thres_ratio) {
    double max_grad_mag = find_max(grad_mag);
    double high_threshold = high_thres_ratio * max_grad_mag;
    double low_threshold = low_thres_ratio * max_grad_mag;

    uint rows = grad_mag.size();
    uint cols = grad_mag[0].size();
    Int_Matrix res(rows, std::vector<int>(cols, 0));

    for (uint i = 0; i < rows; i++) {
        for (uint j = 0; j < cols; j++) {
            if (grad_mag[i][j] >= high_threshold)
                res[i][j] = STRONG;
            else if (grad_mag[i][j] >= low_threshold)
                res[i][j] = WEAK;
        }
    }

    return res;

}