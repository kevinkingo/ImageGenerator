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
    Config() {
        ratio = 1.0;
        
        /*** Picture ***/
        pic_num = 1;
        pic_width = 1920 * ratio;
        pic_height = 1080 * ratio;
        
        /*** Board ***/
        type = RING;
        board_width = 400.0; //in millimeter
        board_height = 300.0; //in millimeter
        pattern_col_num = 12;
        pattern_row_num = 8;
        pattern_size = 25.0;
        //padding_x and padding_y is calculated automatically
        
        ring_step_radius = 2.5;
        ring_num = 4;
        
        /*** Camera ***/
        focus_x = 1600 * ratio; //in pixel
        focus_y = 1600 * ratio; //in pixel
        ux = pic_width / 2.0;
        uy = pic_height / 2.0;
        gamma = 0.0;
        
        aperture = 600.0;
        
        k1 = 0.0;
        k2 = 0.0;
        p1 = 0.0;
        p2 = 0.0;
        k3 = 0.0;
        
        /*** Noise ***/
        
        
        /*** Debug ***/
        subpix_num = 3;
        sample_num = 30;
    }
    
    double ratio;
    /*** Picture ***/
    int pic_num;
    int pic_width;
    int pic_height;
    
    /*** Board ***/
    BoardType type;
    double board_width; //in millimeter
    double board_height; //in millimeter
    int pattern_col_num;
    int pattern_row_num;
    double pattern_size;
    //padding_x and padding_y is calculated automatically
    
    double ring_step_radius;
    int ring_num;
    
    /*** Camera ***/
    double focus_x, focus_y; //in pixel
    double ux, uy;
    double gamma;
    
    double aperture;
    
    double k1, k2, p1, p2, k3;
    
    /*** Noise ***/
    
    
    /*** Debug ***/
    int subpix_num;
    int sample_num;
    
};

#endif /* _config_h */
