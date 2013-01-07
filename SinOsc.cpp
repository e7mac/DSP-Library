//
//  SinOsc.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "SinOsc.h"

SinOsc::SinOsc()
{
    reset();
}

void SinOsc::setSampleRate(double withSampleRate)
{
    sampleRate = withSampleRate;
}

void SinOsc::reset()
{
    phase = 0.0;
}

void SinOsc::setCenterFrequency(float newFrequency)
{
    centerFrequency = newFrequency;
}

void SinOsc::setFrequency(float input)
{ // set the instantaneous frequency based on an input
    frequency = centerFrequency * powf(2.0, input * range / 12.0);
}

void SinOsc::setAmplitude(float withAmplitude)
{
    amplitude = withAmplitude;
}

void SinOsc::setRange(double withRange)
{
    range = withRange;
}

void SinOsc::process (float& output)
{
    double phaseIncrement =  frequency / sampleRate;
    phase = fmod((phase + phaseIncrement), (1.0));
    output = sinf(phase * 2.0 * M_PI) * amplitude;
}
