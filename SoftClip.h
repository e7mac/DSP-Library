//
//  SoftClip.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__SoftClip__
#define __DSPLibrary__SoftClip__

#include <iostream>
#include <math.h>

class SoftClip
{
protected:
    float n;
    
public:
    SoftClip();
    void setN(float withN);
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__SoftClip__) */
