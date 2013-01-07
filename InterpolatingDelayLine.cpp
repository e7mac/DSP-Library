//
//  InterpolatingDelayLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "InterpolatingDelayLine.h"

void InterpolatingDelayLine::setLength(const float withLength, float withFs)
{
    length = withLength * withFs;
    circularBuffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    readHead = length*0.5;
    writeHead = 0;
    setRate(1.0);
}

void InterpolatingDelayLine::clearBuffer()
{
    for (int i = 0; i < length; i++) { // clear buffer
        circularBuffer[(i + length) % length] = 0;
    }
}

void InterpolatingDelayLine::advanceWriteHead()
{
    writeHead = fmodf((writeHead + rate),length);
}

void InterpolatingDelayLine::advanceReadHead()
{
    readHead = fmodf(readHead + rate,length);
}

void InterpolatingDelayLine::write(float withSample)
{
    float x2 = writeHead;
    int x2Floor = floor(x2);
    int x2Ceil = x2Floor + 1;
    
    float x0 = x2 - rate;
    int x0Floor = floor(x0);
    int x0Ceil = x0Floor + 1;
    
    float y0Floor = circularBuffer[(x0Floor + length) % length];
    float y0Ceil  = circularBuffer[(x0Ceil  + length) % length];
    
    float readSlope = (y0Ceil - y0Floor) / (x0Ceil - x0Floor);
    
    float y0 = y0Floor + (x0 - x0Floor) * readSlope;
    float y2 = withSample;
    
    float writeSlope = (y2 - y0) / (x2 - x0);
    
    // write into the buffer
    for (int i = x0Floor + 1; i < x2Ceil + 1; i++) {
        circularBuffer[(i + length) % length] = y0 + (i - x0) * writeSlope;
    }
}

float InterpolatingDelayLine::read()
{
    float x = readHead;
    int xFloor = floor(x);
    int xCeil = xFloor + 1;
    float yFloor = circularBuffer[(xFloor + length) % length];
    float yCeil  = circularBuffer[(xCeil  + length) % length];
    
    float slope = (yCeil - yFloor) / (xCeil - xFloor);
    float y = yFloor + (x - xFloor) * slope;
    
    return y;
}

void InterpolatingDelayLine::setRate(float withRate)
{
    rate = withRate;
}
