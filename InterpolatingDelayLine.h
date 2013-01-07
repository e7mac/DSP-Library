//
//  InterpolatingDelayLine.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__InterpolatingDelayLine__
#define __DSPLibrary__InterpolatingDelayLine__

#include <iostream>
#include <math.h>

class InterpolatingDelayLine {
private:
    int length;
    float readHead, writeHead, rate;
    float *circularBuffer; // this is a hack... fix it
public:
    void setLength(const float withLength, float withFs);
    void clearBuffer();
    void advanceWriteHead();
    void advanceReadHead();
    void write(float withSample);
    float read();
    void setRate(float withRate);
};


#endif /* defined(__DSPLibrary__InterpolatingDelayLine__) */
