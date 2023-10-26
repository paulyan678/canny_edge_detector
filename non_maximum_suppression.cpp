#include "canny.h"

Matrix supress(const Matrix& grad_mag, const Matrix& grad_angle) {
    int rows = grad_mag.size();
    int cols = grad_mag[0].size();
    Matrix res(rows, std::vector<double>(cols, 0.0));

    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            double mag = grad_mag[i][j];
            double angle = grad_angle[i][j];
            if (j - 1 < 0 || j + 1 >= cols || i - 1 < 0 || i + 1 >= rows)
                continue;

            if (angle == H) {
                if (mag >= grad_mag[i][j-1] && mag >= grad_mag[i][j+1])
                    res[i][j] = mag;
            }

            else if (angle == V) {
                if (mag >= grad_mag[i-1][j] && mag >= grad_mag[i+1][j])
                    res[i][j] = mag;
            }

            else if (angle == PD) {
                if (mag >= grad_mag[i-1][j-1] && mag >= grad_mag[i+1][j+1])
                    res[i][j] = mag;
            }

            else if (angle == ND) {
                if (mag >= grad_mag[i-1][j+1] && mag >= grad_mag[i+1][j-1])
                    res[i][j] = mag;
            }

            else {
                throw std::runtime_error("Invalid angle during supression");
            }
        }
    }
    return res;


}