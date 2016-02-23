//
//  renderer.cpp
//  Image_Generator
//
//  Created by Kingo on 1/21/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#include "renderer.hpp"

using namespace std;

inline double clamp(double x) {
    return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline int toInt(double x) {
    return int(pow(clamp(x),1 / 2.2) * 255 + .5);
}

Renderer::Renderer(const Config &config) {
    w_ = config.pic_width;
    h_ = config.pic_height;
    subpix_num_ = config.subpix_num;
    sample_num_ = config.sample_num;
}

void Renderer::render(const Camera &camera, const Board &board, string filename) {
    Vec* data = new Vec[w_ * h_];
    
    for(int y = 0; y < h_; y++) {
        unsigned short Xi[3] = {0, 0, static_cast<unsigned short>(y * y * y)};
        for (int x = 0; x < w_; x++) {
            for (int sx = 0; sx < subpix_num_; sx++)
                for (int sy = 0; sy < subpix_num_; sy++) {
                    Vec color;
                    for (int samp = 0; samp < sample_num_; samp++) {
                        double t;
                        Ray ray = camera.get_ray(x, y, sx, sy, Xi);
                        Vec point = board.intersect(ray, t);
                        Vec add_color = board.get_color(point);
                        
                        color = color + add_color * (1.0 / sample_num_);
                    }
                    data[y * w_ + x] = data[y * w_ + x] + color * (1.0 / (subpix_num_ * subpix_num_));
                }
        }
        if(y % 10 == 0)
            cout << y << endl;
    }
    
    write(data, filename);
    delete [] data;
    
}

bool Renderer::write(Vec* content, std::string filename) {
    FILE* f = fopen(filename.c_str(), "w");
    fprintf(f, "P3\n%d %d\n%d\n", w_, h_, 255);
    
    for (int y = 0; y < h_; y++) {
        for(int x = 0; x < w_; x++)
            fprintf(f, "%d %d %d ", toInt(content[y * w_ + x].x), toInt(content[y * w_ + x].y), toInt(content[y * w_ + x].z));
        fprintf(f, "\n");
    }
    fclose(f);
    return true;
}