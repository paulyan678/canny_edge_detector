#include "canny.h"


Matrix correlate(const Matrix& img, const Matrix& kernel, const std::string& mode) {
    int img_rows = img.size();
    int img_cols = img[0].size();
    int kernel_rows = kernel.size();
    int kernel_cols = kernel[0].size();

    int output_rows, output_cols, start_row, start_col;
    if (mode == "valid"){
        output_rows = img_rows - kernel_rows + 1;
        output_cols = img_cols - kernel_cols + 1;
        start_col = 0;
        start_row = 0;
    }

    else if (mode == "same"){
        output_rows = img_rows;
        output_cols = img_cols;
        start_row = kernel_rows / 2;
        start_col = kernel_cols / 2;
    }

    else if (mode == "full"){
        output_rows = img_rows + kernel_rows - 1;
        output_cols = img_cols + kernel_cols - 1;
        start_row = kernel_rows - 1;
        start_col = kernel_cols - 1;
    }

    else {
        throw std::runtime_error("Invalid mode");

    }

    Matrix output(output_rows, std::vector<double>(output_cols, 0.0));

    #pragma omp parallel for collapse(2)
    for (int out_row = 0; out_row < output_rows; out_row++) {
        for (int out_col = 0; out_col < output_cols; out_col++) {
            for (int k_row = 0; k_row < kernel_rows; k_row++) {
                for (int k_col = 0; k_col < kernel_cols; k_col++) {
                    int img_row = out_row + k_row - start_row;
                    int img_col = out_col + k_col - start_col;
                    if (img_row >= 0 && img_row < img_rows && img_col >= 0 && img_col < img_cols) {
                        output[out_row][out_col] += img[img_row][img_col] * kernel[k_row][k_col];
                    }
                }
            }
        }
    }
    return output;
}

