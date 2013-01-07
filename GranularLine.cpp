//
//  GranularLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "GranularLine.h"


void GranularLine::resetGrain(int i)
{
    float lowerBound = fmaxf((avgDelay - 2 * spread * maxSpread * 0.5), 0);// + 0.01 * srate / length);
    float upperBound = fminf((avgDelay + 2 * spread * maxSpread * 0.5), 1);
    
    int delay;
    if (upperBound == lowerBound)
        delay = avgDelay * length;
    else
        delay = (lowerBound + fmodf((float)rand()/RAND_MAX, upperBound-lowerBound)) * length;
    
    grains[i].readHead = (writeHead - delay + length)%length;
    grains[i].grainLength = (int)((50 + rand()%100) * srate * 0.001);
    
    grains[i].elapsed = 0;
    if (i <= numGrains)
        grains[i].isActive = 1;
    else
        grains[i].isActive = 0;
    grains[i].currentNumGrainsAmplitude = 1/sqrtf(numGrains) * grains[i].isActive;
}

void GranularLine::setLength(const float withLength, float withFs) {
    length = withLength * withFs;
    circularBuffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    grains = new Grain[numGrains];
    for (int i=0;i<numGrains;i++)
    {
        resetGrain(i);
    }
    writeHead = 0;
    setRate(1.0);
    
    populateWindow(); // create window buffer
}

void GranularLine::clearBuffer() {
    for (int i = 0; i < length; i++) { // clear buffer
        circularBuffer[(i + length) % length] = 0;
    }
}

void GranularLine::advanceWriteHead() {
    writeHead = (writeHead + rate)%length;
}


void GranularLine::write(float withSample) {
    circularBuffer[writeHead] = withSample;
}

float GranularLine::readGrain(int i) {
    float window = getWindow((float)grains[i].elapsed/grains[i].grainLength);
    
    float sample = window * circularBuffer[(grains[i].readHead+grains[i].elapsed++)%length];
    if (grains[i].elapsed>=grains[i].grainLength)
    {
        resetGrain(i);
    }
    return sample*grains[i].currentNumGrainsAmplitude;
}

float GranularLine::getWindow(float x)
{
    int index = x*length;
    return cosValues[index];
}

void GranularLine::populateWindow()
{
    cosValues = new float[length];
    for (int i=0;i<length;i++)
        cosValues[i] = 0.5-0.5*cosf(2*M_PI*i/length);
}


void GranularLine::setRate(float withRate) {
    rate = withRate;
}
