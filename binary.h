#ifndef BINARY_H
#define BINARY_H


#include <iostream>
#include <math.h>
#include <stdexcept>
using namespace std;

// *********************************************************
//  binary.h --- handling binary operations
// *********************************************************
// Included Functions
//      -dbltoBinary(double num, int binary[], int N)
//              -converts double into sign-magnitude binary
// *********************************************************


void dbltoBinary(double num, int binary[], int N);

void inttoBinary(int num, int binary[], int N);

int binarytoInt(int binary[], int N);

#endif

