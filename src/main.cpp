//
//  main.cpp
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#include <random>
#include <iostream>
#include "_config.h"
#include "camera.hpp"
#include "board.hpp"
#include "renderer.hpp"

std::string path = "../output/"; //"/Users/kingo/Desktop/SRT/workspace/ImageGenerator/output/";

std::default_random_engine generator;
std::uniform_real_distribution<double> distr(0.0,1.0);
double erand48(unsigned short int xsubi[3]){
    return distr(generator);
}

void get_random_pos(Config &config, Vec &pos);
void get_random_direc(Vec &x_dir, Vec &y_dir);

int main(int argc, const char * argv[]) {
    Config config;
    
    Camera camera(Vec(), Vec(0, 0, 1), Vec(0, -1, 0), config);
    
    Renderer renderer(config);
    for(int i = 0; i < config.pic_num; i++) {
        Vec pos, x_dir, y_dir;
        get_random_pos(config, pos);
        get_random_direc(x_dir, y_dir);
        
        Board board(config, pos, x_dir, y_dir);
        
        camera.set_focal_dist((pos + x_dir * (config.board_width * 0.5) + y_dir * (config.board_height * 0.5)).z);
        renderer.render(camera, board, path + "test.ppm");
    }
    
    return 0;
}

void get_random_pos(Config &config, Vec &pos) {
    unsigned short Xi[3] = {0, 0, static_cast<unsigned short>(time(NULL))};
    pos = Vec(-config.board_width / 2 * (1 + (erand48(Xi) - 0.5) * 0.2), -config.board_height / 2 * (1 + (erand48(Xi) - 0.5) * 0.2), 600 * (1 + (erand48(Xi) - 0.5) * 0.2));
}

void get_random_direc(Vec &x_dir, Vec &y_dir) {
    unsigned short Xi[3] = {0, 0, static_cast<unsigned short>(time(NULL) * time(NULL))};
    x_dir = Vec(1, (erand48(Xi) - 0.5) * 0.5, (erand48(Xi) - 0.5) * 0.5).norm();
    y_dir = ((x_dir % Vec(0, 0, -1)) + Vec(0, 0, (erand48(Xi) - 0.5) * 0.4)).norm();
}

