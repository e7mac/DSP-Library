//
//  Noise.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Noise__
#define __DSPLibrary__Noise__

#include <iostream>

class Noise {
    
protected:
    float amplitude;
    
public:
    void setAmplitude(float withAmplitude);
    void process(float& output);
};


#endif /* defined(__DSPLibrary__Noise__) */
