//
//  Noise.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Noise.h"

void Noise::setAmplitude(float withAmplitude)
{
    amplitude = withAmplitude;
}

void Noise::process(float& output)
{
    output = (((float)rand() / (float)RAND_MAX) * 2.0 - 1.0) * amplitude;
}
