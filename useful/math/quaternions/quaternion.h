#pragma once

#include <cmath>

namespace quaternions{
    class Quaternion{
        private:
            float components[4];

        public:
            Quaternion();

            Quaternion(const float& a, const float& b, const float& c, const float& d);

            void setA(const float& new_a);

            void setB(const float& new_b);

            void setC(const float& new_c);

            void setD(const float& new_d);

            float getAbs() const;

            float operator[](const int& index) const;
            
            void normalize();

            Quaternion conjugate() const;

            Quaternion operator*(const Quaternion& other) const;
    };

    Quaternion createQ(const float& x, const float& y, const float& z, const float& w);

    Quaternion createH(const float& x, const float& y, const float& z);

    Quaternion rotate(const Quaternion& q, const Quaternion& h);
}
