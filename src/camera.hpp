//
//  camera.hpp
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include "_config.h"
#include "vec.h"
#include "ray.h"

class Camera {
public:
    Camera(const Vec &pos, const Vec &see_dir, const Vec &up_dir, Config &config);
    
    void set_focal_dist(double focal_dist);
    
    Ray get_ray(int x, int y, int sx, int sy, unsigned short *Xi) const;
    
    void add_distortion(Vec &direc) const;
    
private:
    Vec pos_;
    Vec see_dir_;
    Vec up_dir_;
    Vec right_dir_;
    
    int w_, h_;
    int subpix_num_;
    double focus_x_, focus_y_;
    double ux_, uy_;
    double gamma_;
    
    double aperture_r_;
    double focal_dist_;
    
    double k1_, k2_;
};

#endif /* camera_hpp */
