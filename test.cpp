#include <iostream>
#include <cmath>


int main() {
    // test the atan2 function
    double x = 1.0;
    double y = -1.0;
    double angle = atan2(y, x);
    std::cout << angle*180/M_PI << std::endl;


}