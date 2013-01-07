//
//  Recorder.h
//  DSPLibrary
//
//  Created by Mayank on 11/4/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Recorder__
#define __DSPLibrary__Recorder__

#include <iostream>

class Recorder {
private:
    int length;
    int readHead, writeHead;
    float *buffer;
public:
    void setLength(const float withLength, float withFs);
    void clearBuffer();
    void advanceWriteHead();
    void advanceReadHead();
    void write(float withSample);
    float read();
};



#endif /* defined(__DSPLibrary__Recorder__) */
