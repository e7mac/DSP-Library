//
//  GranularLine.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__GranularLine__
#define __DSPLibrary__GranularLine__

#include <iostream>
#include <math.h>

struct Grain
{
    int grainLength;
    int elapsed;
    int readHead;
    bool isActive;
    float currentNumGrainsAmplitude;
};

class GranularLine
{
private:
    int length; // size of the buffer in samples
    int writeHead, rate;
    int maxNumGrains = 50;
    int numGrains = maxNumGrains;
    Grain *grains;
    float *circularBuffer;
    float *cosValues;
    float avgDelay = 0.5; // in seconds
    float spread = 0.5; // in percentage of buffer length
    const float maxSpread = 0.5; // tweak this later
    int srate;
    
public:
    void resetGrain(int i);
    void setLength(const float withLength, float withFs);
    void clearBuffer();
    void advanceWriteHead();
    void write(float withSample);
    float readGrain(int i);
    float getWindow(float x);
    void populateWindow();
    void setRate(float withRate);
};


#endif /* defined(__DSPLibrary__GranularLine__) */
