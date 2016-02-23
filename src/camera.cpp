//
//  camera.cpp
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#include <cstdlib>
#include <cmath>
#include "camera.hpp"

Camera::Camera(const Vec &pos, const Vec &see_dir, const Vec &up_dir, Config &config) {
    pos_ = pos;
    see_dir_ = see_dir;
    up_dir_ = up_dir;
    right_dir_ = (see_dir % up_dir).norm();
    
    w_ = config.pic_width;
    h_ = config.pic_height;
    subpix_num_ = config.subpix_num;
    focus_x_ = config.focus_x;
    focus_y_ = config.focus_y;
    ux_ = config.ux;
    uy_ = config.uy;
    gamma_ = config.gamma;
    aperture_r_ = (focus_x_ + focus_y_) / config.aperture * 0.25;
    
    k1_ = config.k1;
    k2_ = config.k2;
    
    focal_dist_ = 100.0;
}

void Camera::set_focal_dist(double focal_dist) {
    focal_dist_ = focal_dist;
}

Ray Camera::get_ray(int x, int y, int sx, int sy, unsigned short *Xi) const {
    static Vec row1 = Vec(1, -gamma_ / focus_y_, gamma_ * uy_ / focus_y_ - ux_) * (1.0 / focus_x_);
    static Vec row2 = Vec(0, 1, -uy_) * (1.0 / focus_y_);
    
    double r1 = 2 * erand48(Xi), dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
    double r2 = 2 * erand48(Xi), dy = r2 < 1 ? sqrt(r2) - 1 : 1 - sqrt(2 - r2);
    Vec pixel((sx + .5 + dx) * (1.0 / subpix_num_) + x, (sy + .5 + dy) * (1.0 / subpix_num_) + y, 1);
    Vec direc(row1.dot(pixel), row2.dot(pixel), 1);
    add_distortion(direc);
    
    double r = aperture_r_ * sqrt(erand48(Xi)), theta = 2 * M_PI * erand48(Xi);
    Vec aper_vec = (up_dir_ * cos(theta) + right_dir_ * sin(theta)) * r;
    
    return Ray(pos_ + aper_vec, (direc * focal_dist_ - aper_vec).norm());
}

void Camera::add_distortion(Vec &direc) const {
    double r2 = direc.x * direc.x + direc.y * direc.y;
    double coeff1 = (1 + k1_ * r2 + k2_ * r2 * r2);
    
    direc.x = direc.x * coeff1;
    direc.y = direc.y * coeff1;
}