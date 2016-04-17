//
//  renderer.hpp
//  Image_Generator
//
//  Created by Kingo on 1/21/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "camera.hpp"
#include "board.hpp"

class Renderer {
public:
    Renderer(const Config &config);
    
    void worker(const Camera &camera, const Board &board, Vec *data);
    
    void render(const Camera &camera, const Board &board, std::string filename);
    
    bool write(Vec* content, std::string filename);
    
private:
    int w_, h_;
    int subpix_num_, sample_num_;
    
    double uniform_noise_amp_;
    
    static constexpr int worker_num_ = 4;
    
};

#endif /* renderer_hpp */
