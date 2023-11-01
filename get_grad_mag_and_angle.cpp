#include "canny.h"

Matrix get_grad_mag(const Matrix& grad_x, const Matrix& grad_y) {
    int rows = grad_x.size();
    int cols = grad_x[0].size();
    Matrix grad_mag(rows, std::vector<double>(cols, 0.0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            grad_mag[i][j] = sqrt(grad_x[i][j] * grad_x[i][j] + grad_y[i][j] * grad_y[i][j]);
    }

    return grad_mag;
}

Matrix get_grad_angle(const Matrix& grad_x, const Matrix& grad_y) {
    int rows = grad_x.size();
    int cols = grad_x[0].size();
    Matrix grad_angle(rows, std::vector<double>(cols, 0.0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double angle_deg = atan2(grad_y[i][j], grad_x[i][j]) * 180 / M_PI;
        
            if (abs_double(angle_deg) <= 22.5 || abs_double(angle_deg) >= 157.5)
                grad_angle[i][j] = H;

            else if (abs_double(angle_deg) >= 67.5 && abs_double(angle_deg) <= 112.5)
                grad_angle[i][j] = V;


            else if ((angle_deg > 22.5 && angle_deg < 67.5) || (angle_deg < -112.5 && angle_deg > -157.5))
                grad_angle[i][j] = PD;


            else if ((angle_deg < -22.5 && angle_deg > -67.5) || (angle_deg > 112.5 && angle_deg < 157.5))
                grad_angle[i][j] = ND;
            
            else {
                throw std::runtime_error("Invalid angle");
            }
        }
    }

    return grad_angle;
}

