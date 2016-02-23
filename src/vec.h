//
//  vec.h
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef vec_h
#define vec_h

#include <cmath>
#include <algorithm>

class Vec {
public:
    double x, y, z;                  // position, also color (r,g,b)
    
    Vec(double x_ = 0, double y_ = 0, double z_ = 0) {
        x = x_;
        y = y_;
        z = z_;
    }
    
    Vec operator+(const Vec &b) const {
        return Vec(x + b.x, y + b.y, z + b.z);
    }
    
    Vec operator-(const Vec &b) const {
        return Vec(x - b.x, y - b.y, z - b.z);
    }
    
    Vec operator*(double b) const {
        return Vec(x * b, y * b, z * b);
    }
    
    inline double& operator [](int index) {
        switch (index) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                return z;
                break;
        }
    }
    
    inline const double& operator [](int index) const  {
        switch (index) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                return z;
                break;
        }
    }
    
    Vec mult(const Vec &b) const {
        return Vec(x * b.x, y * b.y, z * b.z);
    }
    
    Vec& norm() {
        return *this = *this * (1 / sqrt(x * x + y * y + z * z));
    }
    
    double dot(const Vec &b) const {
        return x * b.x + y * b.y + z * b.z;
    }
    
    // cross:
    Vec operator%(const Vec &b) const {
        return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    
    Vec& clamp(double clamp_val) {
        x = std::min(x, clamp_val);
        y = std::min(y, clamp_val);
        z = std::min(z, clamp_val);
        return *this;
    }
};

#endif /* vec_h */
