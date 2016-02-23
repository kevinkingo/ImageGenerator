//
//  board.hpp
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include "_config.h"
#include "vec.h"
#include "ray.h"

class Board {
public:
    Board(Config &config, const Vec &pos, const Vec &x_dir, const Vec &y_dir);
    
    Vec intersect(const Ray &ray, double &t) const;
    
    Vec get_color(const Vec &point) const;
    
    
private:
    Vec pos_, x_dir_, y_dir_, z_dir_;
    Vec row1_, row2_, row3_;
    
    double board_width_;
    double board_height_;
    double board_paddingx_;
    double board_paddingy_;
    
    int col_num_;
    int row_num_;
    double pattern_size_;
    
    BoardType type_;
    
    double ring_step_radius_;
    int ring_num_;
    
};

#endif /* board_hpp */
