//
//  Recorder.cpp
//  DSPLibrary
//
//  Created by Mayank on 11/4/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Recorder.h"


void Recorder::setLength(const float withLength, float withFs)
{
    length = withLength * withFs;
    buffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    readHead = 0;
    writeHead = 0;
}

void Recorder::clearBuffer()
{
    for (int i = 0; i < length; i++) { // clear buffer
        buffer[i] = 0;
    }
}

void Recorder::advanceWriteHead()
{
    writeHead = writeHead++;
    if (writeHead==length)
    {
        float *oldBuffer = buffer;
        length*=2;
        buffer = new float[length];
        clearBuffer();
        for (int i=0;i<length/2;i++)
        {
            buffer[i]=oldBuffer[i];
        }
        delete oldBuffer;
    }
}

void Recorder::advanceReadHead()
{
    readHead++;
}

void Recorder::write(float withSample)
{
    buffer[writeHead] = withSample;
}

float Recorder::read()
{
    return buffer[readHead];
}
