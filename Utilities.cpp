//
//  Utilities.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Utilities.h"

#include <math.h>

void bilinearTransform(double acoefs[], double dcoefs[], double withFs)
{
	float b0, b1, b2, a0, a1, a2;		//storage for continuous-time filter coefs
	float bz0, bz1, bz2, az0, az1, az2;	// coefs for discrete-time filter.
	
	b0 = acoefs[0]; b1 = acoefs[1]; b2 = acoefs[2]; // unpack coefficients
    a0 = acoefs[3]; a1 = acoefs[4]; a2 = acoefs[5];
    
    // H(s) = 1
    //        -------------------------------
    //        s^2*(1/wc^2) + s*(1/(Q*wc)) + 1
    
    // Bilinear transform, H(z) = H(s(z))
    // s = 2 * 1 - z^-1
    //     -   --------
    //     T   1 + z^-1
    
    double T = 1.0 / withFs; // the period
    
    bz2 = 4 * b2 - 2 * b1 * T + b0 * T * T;
    bz1 = -8 * b2 + 2 * b0 * T * T;
    bz0 = 4 * b2 + 2 * b1 * T + b0 * T * T;
    
    az2 =  4.0 * a2 - 2.0 * T * a1 + T * T * a0;
    az1 = -8.0 * a2 + 2.0 * T * T * a0;
    az0 =  4.0 * a2 + 2.0 * T * a1 + T * T* a0;
    
    bz2 = bz2 / az0; // normalizing by az0
    bz1 = bz1 / az0;
    bz0 = bz0 / az0;
    
    az2 = az2 / az0;
    az1 = az1 / az0;
    az0 = az0 / az0;
    
	dcoefs[0] = bz0; dcoefs[1] = bz1; dcoefs[2] = bz2; 	// return coefficients to the output
    dcoefs[3] = az1; dcoefs[4] = az2;
    
}

//------------------------------------------------------------------------------
void designParametric(double* dcoefs, double center, double gain, double qval, double withFs)
// design parametric filter based on input center frequency, gain, Q and sampling rate
{
	double b0, b1, b2, a0, a1, a2;		//storage for continuous-time filter coefs
	double acoefs[6];
    
	//Design parametric filter here. Filter should be of the form
	//
	//    2
	// b2s  + b1s + b0
	// ---------------
	//    2
	// a2s  + a1s + a0
	//
	// Parameters are center frequency in Hz, gain in dB, and Q.
    
	// design analog filter based on input gain, center frequency and Q
    if (gain > 0.0) { // boost case
        b0 = 1;
        b1 = gain / (qval * center * 2 * M_PI);
        b2 = 1 / (center * center * 4 * M_PI * M_PI);
        a0 = 1;
        a1 = 1 / (qval * center * 2 * M_PI);
        a2 = 1 / (center * center * 4 * M_PI * M_PI);
    } else { // cut case
        b0 = 1;
        b1 = 1 / (qval * center * 2 * M_PI);
        b2 = 1 / (center * center * 4 * M_PI * M_PI);
        a0 = 1;
        a1 = 1 / (qval * gain * center * 2 * M_PI);
        a2 = 1 / (center * center * 4 * M_PI * M_PI);
    }
	
	acoefs[0] = b0; acoefs[1] = b1; acoefs[2] = b2; // pack the analog coeffs into an array
    acoefs[3] = a0; acoefs[4] = a1; acoefs[5] = a2;
	
    // and apply the bilinear tranform
	bilinearTransform(acoefs, dcoefs, withFs); // inputs the 6 analog coeffs, output the 5 digital coeffs
}

//------------------------------------------------------------------------------
void designFirstOrderLowpass(double* dcoefs, double cutoff, double withFs)
// design parametric filter based on input center frequency, gain, Q and sampling rate
{
	double b0, b1, b2, a0, a1, a2;		//storage for continuous-time filter coefs
	double acoefs[6];
    
	//Design lowpass filter here. Filter should be of the form
	//
	//    2
	// b2s  + b1s + b0
	// ---------------
	//    2
	// a2s  + a1s + a0
	//
    // where b2 and a2 are zero (1st order, just keeM_PIng them so the same BLT function can be used)
    //
	// Parameters are cutoff frequency in Hz
    
    b0 = 1;	// design analog filter based on cutoff frequency
    b1 = 0;
    b2 = 0;
    a0 = 1;
    a1 = 1 / cutoff;
    a2 = 0;
	
	acoefs[0] = b0; acoefs[1] = b1; acoefs[2] = b2; // pack the analog coeffs into an array
    acoefs[3] = a0; acoefs[4] = a1; acoefs[5] = a2;
	
    // and apply the bilinear tranform
	bilinearTransform(acoefs, dcoefs, withFs); // inputs the 6 analog coeffs, output the 5 digital coeffs
}


//------------------------------------------------------------------------------
void designFirstOrderHighpass(double* dcoefs, double cutoff, double withFs)
// design parametric filter based on input center frequency, gain, Q and sampling rate
{
	double b0, b1, b2, a0, a1, a2;		//storage for continuous-time filter coefs
	double acoefs[6];
    
	//Design highpass filter here. Filter should be of the form
	//
	//    2
	// b2s  + b1s + b0
	// ---------------
	//    2
	// a2s  + a1s + a0
	//
    // where b2 and a2 are zero (1st order, just keeM_PIng them so the same BLT function can be used)
    //
	// Parameters are cutoff frequency in Hz
    
    b0 = 0;	// design analog filter based on cutoff frequency
    b1 = 1 / cutoff;
    b2 = 0;
    a0 = 1;
    a1 = 1 / cutoff;
    a2 = 0;
	
	acoefs[0] = b0; acoefs[1] = b1; acoefs[2] = b2; // pack the analog coeffs into an array
    acoefs[3] = a0; acoefs[4] = a1; acoefs[5] = a2;
	
    // and apply the bilinear tranform
	bilinearTransform(acoefs, dcoefs, withFs); // inputs the 6 analog coeffs, output the 5 digital coeffs
}