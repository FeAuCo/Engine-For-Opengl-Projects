#include "quaternion.h"
#include "../useful/math/math.h"

quaternions::Quaternion::Quaternion(){}

quaternions::Quaternion::Quaternion(const float& a, const float& b, const float&  c, const float& d){
    this->components[0] = a;
    this->components[1] = b;
    this->components[2] = c;
    this->components[3] = d;
}

void quaternions::Quaternion::setA(const float& new_a){
    this->components[0] = new_a;
}

void quaternions::Quaternion::setB(const float& new_b){
    this->components[1] = new_b;
}

void quaternions::Quaternion::setC(const float& new_c){
    this->components[2] = new_c;
}

void quaternions::Quaternion::setD(const float& new_d){
    this->components[3] = new_d;
}

float quaternions::Quaternion::getAbs() const{
    return sqrt(this->components[0] * this->components[0] + this->components[1] * this->components[1] + this->components[2] * this->components[2] + this->components[3] * this->components[3]);
}

float quaternions::Quaternion::operator[](const int& index) const{
    return this->components[index];
}

quaternions::Quaternion quaternions::Quaternion::conjugate() const{
    return quaternions::Quaternion(this->components[0], this->components[1] * (-1), this->components[2] * (-1), this->components[3] * (-1));
}

void quaternions::Quaternion::normalize(){
    if (this->getAbs() != 0){
        this->components[0] /= this->getAbs();
        this->components[1] /= this->getAbs();
        this->components[2] /= this->getAbs();
        this->components[3] /= this->getAbs();
    }
}

quaternions::Quaternion quaternions::Quaternion::operator*(const quaternions::Quaternion& other) const{
    return quaternions::Quaternion
                                (
                                    math::isZero(this->components[0] * other[0] - this->components[1] * other[1] - this->components[2] * other[2] - this->components[3] * other[3], -10, 1),
                                    math::isZero(this->components[0] * other[1] + this->components[1] * other[0] + this->components[2] * other[3] - this->components[3] * other[2], -10, 1),
                                    math::isZero(this->components[0] * other[2] + this->components[2] * other[0] - this->components[1] * other[3] + this->components[3] * other[1], -10, 1),
                                    math::isZero(this->components[0] * other[3] + this->components[3] * other[0] + this->components[1] * other[2] - this->components[2] * other[1], -10, 1)
                                );
}

quaternions::Quaternion quaternions::createQ(const float& x, const float& y, const float& z, const float& w){
    quaternions::Quaternion q = quaternions::Quaternion(cos(w/2), sin(w/2) * x, sin(w/2) * y, sin(w/2) * z);
    q.normalize();
    
    return q;
}

quaternions::Quaternion quaternions::createH(const float& x, const float& y, const float& z){
    return quaternions::Quaternion(0 , x, y, z);
}

quaternions::Quaternion quaternions::rotate(const quaternions::Quaternion& q, const quaternions::Quaternion& h){
    return q * h * q.conjugate();
}
