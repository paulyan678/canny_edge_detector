#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "canny.h"


int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <path_to_input_image> <path_to_output_image> <low threashold ratio> <high threshold ratio>" << std::endl;
        return 1;
    }

    // Call Python script to process image
    std::string command = "python3 pre_process_img.py " + std::string(argv[1]);
    double low_thres_ratio = std::stod(argv[3]);
    double high_thres_ratio = std::stod(argv[4]);
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing Python script" << std::endl;
        return 1;
    }

    // Read the width and height first
    int width, height;
    char buffer[4096];  // Use for reading width, height, and garbage line.
    
    if (fgets(buffer, sizeof(buffer), pipe)) {
        std::istringstream iss1(buffer);
        iss1 >> width;
    }
    if (fgets(buffer, sizeof(buffer), pipe)) {
        std::istringstream iss2(buffer);
        iss2 >> height;
    }
    fgets(buffer, sizeof(buffer), pipe); // skip the line containing garbage

    // Calculate buffer size required for image data
    int maxCharsPerLine = width * 3 + width;  // max of 3 characters per pixel. And space for the sapce character.
    char* line = new char[maxCharsPerLine];

    // Then read the image data
    Matrix image(height, std::vector<double>(width, 0.0));

    for (int i = 0; i < height; ++i) {
        if (fgets(line, maxCharsPerLine, pipe)) {
            std::istringstream iss(line);
            for (int j = 0; j < width; ++j) {
                iss >> image[i][j];
            }
        }
    }

    delete[] line;  // Deallocate the dynamically allocated buffer

    pclose(pipe);


    // ... (use the 2D vector as required)

    // Call Canny edge detection
    Matrix blur_img = correlate(image, gen_gaussian_filter(5, 1.4), "same");
    Matrix grad_x = correlate(blur_img, SOBEL_X, "same");
    Matrix grad_y = correlate(blur_img, SOBEL_Y, "same");
    Matrix grad_mag = get_grad_mag(grad_x, grad_y);
    Matrix grad_angle = get_grad_angle(grad_x, grad_y);
    Matrix supressed = supress(grad_mag, grad_angle);
    Int_Matrix thresholded = threshold(supressed, high_thres_ratio, low_thres_ratio);
    Int_Matrix res = hysteresis(thresholded);

    // Write the result to a pipe
    command = "python3 post_process_img.py " + std::string(argv[2]);
    pipe = popen(command.c_str(), "w");
    if (!pipe) {
        std::cerr << "Error executing Python script" << std::endl;
        return 1;
    }
    for (const auto& row : res) {
        for (const int pixel : row) {
            fprintf(pipe, "%d ", pixel);
        }
        fprintf(pipe, "\n");
    }

    return 0;
}
