//
//  SoftClip.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "SoftClip.h"

SoftClip::SoftClip()
{
    setN(2.5); // approximates hyperbolic tangent function
}

void SoftClip::setN(float withN)
{
    n = withN;
}

void SoftClip::process (float input, float& output)
{
    output = input / pow(1 + pow(fabs(input), n), 1/n);
    //optimized for pedipadproc
    //        output = input / 1 + fabsf(input);
}
