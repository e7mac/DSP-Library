//
//  LevelEstimator.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__LevelEstimator__
#define __DSPLibrary__LevelEstimator__

#include <iostream>
#include <math.h>

class LevelEstimator
{
private:
	double	b0, a1, levelEstimate;
public:
	LevelEstimator();
	void setTau(double tau, double fs);
	void reset();
	void process (double input, double& output);
	void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__LevelEstimator__) */
