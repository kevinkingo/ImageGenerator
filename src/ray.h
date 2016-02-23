//
//  ray.h
//  Image_Generator
//
//  Created by Kingo on 1/20/16.
//  Copyright © 2016 Kingo. All rights reserved.
//

#ifndef ray_h
#define ray_h

class Ray {
public:
    Vec origin, direc;
    
    Ray(Vec origin_, Vec direc_) : origin(origin_), direc(direc_) {
        
    }
    
};

#endif /* ray_h */
