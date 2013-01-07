//
//  DelayLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "DelayLine.h"

void DelayLine::setLength(const float withLength, float withFs)
{
    length = withLength * withFs;
    circularBuffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    readHead = length*0.5;
    writeHead = 0;
}

void DelayLine::clearBuffer()
{
    for (int i = 0; i < length; i++) { // clear buffer
        circularBuffer[(i + length) % length] = 0;
    }
}

void DelayLine::advanceWriteHead()
{
    writeHead = (writeHead+1)%length;
}

void DelayLine::advanceReadHead()
{
    readHead = (readHead+1)%length;
}

void DelayLine::write(float withSample)
{
    int x = writeHead;
    circularBuffer[x] = withSample;
}

float DelayLine::read()
{
    int x = readHead;
    return circularBuffer[x];
}
