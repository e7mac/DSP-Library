//
//  DeadZone.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "DeadZone.h"

DeadZone::DeadZone()
{
    alpha = 0;
    beta = 0;
}

void DeadZone::setAlpha(double withAlpha)
{
    alpha = withAlpha;
}
void DeadZone::setBeta (double withBeta )
{
    beta  = withBeta ;
}

void DeadZone::process (double input, double& output)
{
    if (input < -alpha) {
        output = -alpha * tan(beta) + (input + alpha) * ((1 - alpha * tan(beta)) / (1 - alpha));
    }
    if (input > alpha) {
        output = alpha * tan(beta) + (input - alpha) * ((1 - alpha * tan(beta)) / (1 - alpha));
    }
    if (fabs(input) <= alpha) {
        output = input * tan(beta);
    }
    //output = (input < -alpha) * (input + alpha)/(1.0 - alpha) + (input > alpha) * (input - alpha)/(1.0 - alpha);
}
