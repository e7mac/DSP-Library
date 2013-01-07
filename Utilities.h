//
//  Utilities.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Utilities__
#define __DSPLibrary__Utilities__

#include <iostream>

void bilinearTransform(double acoefs[], double dcoefs[], double withFs);

void designParametric(double* dcoefs, double center, double gain, double qval, double withFs);

void designFirstOrderLowpass(double* dcoefs, double cutoff, double withFs);

void designFirstOrderHighpass(double* dcoefs, double cutoff, double withFs);
#endif /* defined(__DSPLibrary__Utilities__) */