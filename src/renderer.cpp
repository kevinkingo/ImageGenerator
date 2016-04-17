//
//  renderer.cpp
//  Image_Generator
//
//  Created by Kingo on 1/21/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#include "renderer.hpp"
#include <mutex>
#include <thread>

using namespace std;

inline double clamp(double x) {
    return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline int toInt(double x) {
    return int(pow(clamp(x),1 / 2.2) * 255 + .5);
}

int get_feed(int h = -1) {
    static int total_h;
    static int row;
    static mutex lock;
    
    lock.lock();
    int ret_val;
    
    if (h > 0) {
        total_h = h;
        row = 0;
        ret_val = row;
    }
    else {
        ret_val = row;
        if(row < total_h)
            row++;
        if(row % 10 == 0)
            cout << row << endl;
    }

    lock.unlock();
    return ret_val;
}

Renderer::Renderer(const Config &config) {
    w_ = config.pic_width;
    h_ = config.pic_height;
    subpix_num_ = config.subpix_num;
    sample_num_ = config.sample_num;
    uniform_noise_amp_ = config.uniform_noise_amp;
}

void Renderer::worker(const Camera &camera, const Board &board, Vec *data) {
    int y;
    while((y = get_feed()) != h_) {
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
    }
}

void Renderer::render(const Camera &camera, const Board &board, string filename) {
    Vec* data = new Vec[w_ * h_];
    get_feed(h_);
    
    thread threads[worker_num_];
    for (int th = 0; th < worker_num_; th++) {
        threads[th] = thread(&Renderer::worker, this, camera, board, data);
    }
    
    for (int th = 0; th < worker_num_; th++) {
        threads[th].join();
    }

    
    write(data, filename);
    delete [] data;
    
}

bool Renderer::write(Vec* content, std::string filename) {
    cout << filename << endl;
    FILE* f = fopen(filename.c_str(), "w");
    fprintf(f, "P3\n%d %d\n%d\n", w_, h_, 255);
    
    for (int y = 0; y < h_; y++) {
        unsigned short Xi[3] = {0, 0, static_cast<unsigned short>(y * y * y * y)};
        for(int x = 0; x < w_; x++) {
            double uniform_noise = (erand48(Xi) - 0.5) * 2 * uniform_noise_amp_;
            fprintf(f, "%d %d %d ", toInt(content[y * w_ + x].x + uniform_noise), toInt(content[y * w_ + x].y + uniform_noise), toInt(content[y * w_ + x].z + uniform_noise));
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return true;
}