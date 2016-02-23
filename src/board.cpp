//
//  board.cpp
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#include <iostream>
#include "board.hpp"

using namespace std;

Board::Board(Config &config, const Vec &pos, const Vec &x_dir, const Vec &y_dir) {
    pos_ = pos;
    x_dir_ = x_dir;
    y_dir_ = y_dir;
    z_dir_ = x_dir % y_dir;
    
    row1_ = Vec(x_dir_.x, y_dir_.x, z_dir_.x);
    row2_ = Vec(x_dir_.y, y_dir_.y, z_dir_.y);
    row3_ = Vec(x_dir_.z, y_dir_.z, z_dir_.z);
    
    type_ = config.type;
    board_width_ = config.board_width;
    board_height_ = config.board_height;
    col_num_ = config.pattern_col_num;
    row_num_ = config.pattern_row_num;
    pattern_size_ = config.pattern_size;
    
    board_paddingx_ = (board_width_ - col_num_ * pattern_size_) * 0.5;
    board_paddingy_ = (board_height_ - row_num_ * pattern_size_) * 0.5;
    
    ring_step_radius_ = config.ring_step_radius;
    ring_num_ = config.ring_num;
}

Vec Board::intersect(const Ray &ray, double &t) const {
    Vec OT = ray.origin - pos_;
    Vec R_inv_OT(row1_.dot(OT), row2_.dot(OT), row3_.dot(OT));
    Vec R_inv_D(row1_.dot(ray.direc), row2_.dot(ray.direc), row3_.dot(ray.direc));
    t = - R_inv_OT.z / R_inv_D.z;
    return Vec(R_inv_OT.x + t * R_inv_D.x, R_inv_OT.y + t * R_inv_D.y);
}

Vec Board::get_color(const Vec &point) const {
    Vec color;
    if (point.x >= board_paddingx_ && point.x < board_width_ - board_paddingx_
        && point.y >= board_paddingy_ && point.y < board_height_ - board_paddingy_) {
        int a = (point.x - board_paddingx_) / pattern_size_;
        int b = (point.y - board_paddingy_) / pattern_size_;
        if(type_ == CHESSBOARD) {
            color = Vec(1, 1, 1) * ((a + b) % 2);
        }
        else {
            Vec r = point - Vec(board_paddingx_ + pattern_size_ * a + pattern_size_ * 0.5, board_paddingy_ + pattern_size_ * b + pattern_size_ * 0.5);
            double dist = sqrt(r.dot(r));
            int num = dist / ring_step_radius_;
            if(num < ring_num_)
                color = Vec(1, 1, 1) * ((1 + ring_num_ + num) % 2);
            else
                color = Vec(1, 1, 1);
        }
    }
    else if (point.x >= 0 && point.x < board_width_ && point.y >= 0 && point.y < board_height_)
        color = Vec(1, 1, 1);
    else
        color = Vec();

    
    return color;
}