#include"math.h"

double math::isZero(const double& number, const int& acc, const int& coef){
        if (std::abs(number) < coef * pow(10.0, acc)){
            return 0;
        }

        else{
            return number;
        }
    }