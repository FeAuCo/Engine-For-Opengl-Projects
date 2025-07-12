#include"math.h"

float math::isZero(const float& number, const int& acc, const int& coef){
        if (std::abs(number) < coef * pow(10.0, acc)){
            return 0;
        }

        else{
            return number;
        }
}

float math::degToRad(const float& w){
    return w * (M_PI / 180.0);
}

float math::radToDeg(const float& w){
    return w * (180.0 / M_PI);
}
