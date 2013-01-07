//
//  Compressor.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Compressor.h"

Compressor::Compressor(float wthreshold,float wratio, int srate)
{
    threshold = wthreshold;
    ratio = wratio;
    raisedTo = 1/(ratio-1);
    levelEstimator.setTau(0.05, srate);
    logThreshold = dB(threshold);
}

void Compressor::setupCompressor(float wthreshold,float wratio, int srate)
{
    threshold = wthreshold;
    ratio = wratio;
    raisedTo = 1/(ratio-1);
    levelEstimator.setTau(0.05, srate);
    logThreshold = dB(threshold);
}

void Compressor::process(float input, float&output)
{
    float levelEstimate,gain;
    levelEstimator.process(input, levelEstimate);
    float logLevel = dB(levelEstimate);
    if (logLevel < logThreshold)
    {
        output = input;
    }
    else
    {
        float dbGain = (logLevel - logThreshold) / (1/ratio -1);
        output = input * dB2lin(dbGain);
    }
    
}

