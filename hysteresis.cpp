#include "canny.h"

Int_Matrix hysteresis(const Int_Matrix& grad_mag) {
    int rows = grad_mag.size();
    int cols = grad_mag[0].size();

    Int_Matrix res(rows, std::vector<int>(cols, 0));
    
    #pragma omp parallel for collapse(2)
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (col - 1 < 0 || col + 1 >= cols || row - 1 < 0 || row + 1 >= rows || grad_mag[row][col] == 0)
                continue;

            if (grad_mag[row][col] == STRONG || grad_mag[row + 1][col] == STRONG || grad_mag[row - 1][col] == STRONG || grad_mag[row][col + 1] == STRONG || grad_mag[row][col - 1] == STRONG || grad_mag[row + 1][col + 1] == STRONG || grad_mag[row - 1][col - 1] == STRONG || grad_mag[row + 1][col - 1] == STRONG || grad_mag[row - 1][col + 1] == STRONG)
                res[row][col] = STRONG;
        }
    }
    return res;
}