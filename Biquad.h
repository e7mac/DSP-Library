//
//  Biquad.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Biquad__
#define __DSPLibrary__Biquad__

#include <iostream>

class Biquad {
protected:
    double	b0, b1, b2, a1, a2, z1, z2;
public:
    Biquad();
    void setCoefs(double* coefs);
    void reset();
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__Biquad__) */
