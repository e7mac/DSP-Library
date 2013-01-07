//
//  LevelEstimator.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "LevelEstimator.h"

LevelEstimator::LevelEstimator()
{
    // default to pass-through
    this->a1 = 0; // relese coeffs
    this->b0 = 1;
    reset();
}

void LevelEstimator::setTau(double tau, double fs)
{
    a1 = exp( -1.0 / ( tau * fs ) );
    b0 = 1 - a1;
}

void LevelEstimator::reset()
{ // reset filter state
    levelEstimate = 0;
}

void LevelEstimator::process (double input, double& output)
{
    levelEstimate += b0 * ( fabs( input ) - levelEstimate );
    output = levelEstimate;
}

void LevelEstimator::process (float input, float& output)
{
    levelEstimate += b0 * ( fabs( input ) - levelEstimate );
    output = levelEstimate;
}
