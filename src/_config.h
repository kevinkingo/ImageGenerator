//
//  _config.h
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef _config_h
#define _config_h

enum BoardType {CHESSBOARD, RING};

class Config {
public:
    double ratio = 1.0;
    /*** Picture ***/
    int pic_num = 1;
    int pic_width = 1920 * ratio;
    int pic_height = 1080 * ratio;
    
    /*** Board ***/
    BoardType type = RING;
    double board_width = 400; //in millimeter
    double board_height = 300; //in millimeter
    int pattern_col_num = 12;
    int pattern_row_num = 8;
    double pattern_size = 25;
    //padding_x and padding_y is calculated automatically
    
    double ring_step_radius = 2.5;
    int ring_num = 4;
    
    /*** Camera ***/
    double focus_x = 1600 * ratio; //in pixel
    double focus_y = 1600 * ratio; //in pixel
    double ux = pic_width / 2.0;
    double uy = pic_height / 2.0;
    double gamma = 0.0;
    
    double aperture = 600.0;
    
    double k1 = 0.0;
    double k2 = 0.0;
    double p1 = 0.0;
    double p2 = 0.0;
    double k3 = 0.0;
    
    /*** Noise ***/
    
    
    /*** Debug ***/
    int subpix_num = 3;
    int sample_num = 30;
    
};

#endif /* _config_h */
