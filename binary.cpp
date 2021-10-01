#ifndef BINARY_CPP
#define BINARY_CPP


#include <iostream>
#include <math.h>
#include <stdexcept>
#include "binary.h"
using namespace std;

void dbltoBinary(double num, int binary[], int N)
{
        //Takes long integer type(32 bits) and converts
        //it to a binary number of size 'size'
        long int number;

        // shift num by size of output binary number
        // to get integer with necessary bitmap
        number = abs(round(num * pow(2,N-1)));

        if(number == pow(2,N-1))
        { // rewriting 10000000... as 011111111....
            number -= 1;
        }
        if(number > pow(2,N-1))
        {
            throw overflow_error("\nOverflow in dbltoBinary\n");
        }


        // convert new number into binary
        for(int i=0; number>0; i++)
        {
            binary[N-i-1] = number%2;
            number = number / 2;
        }

        // Sign bit
        if(num < 0)
        {binary[0] = 1;}
}
void inttoBinary(int num, int binary[], int N)
{
        //Takes integer and converts
        //it to a binary number of size 'N'

        if(num >= pow(2,N))
        {throw overflow_error("\nOverflow in inttoBinary\n");}

        // convert new number into binary
        for(int i=0; num>0; i++)
        {
            binary[N-i-1] = num%2;
            num = num / 2;
        }
}

int binarytoInt(int binary[], int N)
{
        // Takes a binary number of size 'N'
        // and converts it to integer

        int a = 0;

        // compute value of each bit
        for(int i=0; i<N; i++)
        {
            a += binary[i]*pow(2,N-1-i);
        }
        return a;
}

#endif
