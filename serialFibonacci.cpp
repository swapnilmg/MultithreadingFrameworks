//
//  serialFibonacci.cpp
//  ParallelProcessing
//
//  Created by Swapnil Gaikwad on 4/23/17.
//  Copyright © 2017 Swapnil Gaikwad. All rights reserved.
//

#include <stdio.h>
#include <time.h>

unsigned long fib(unsigned long n)
{
    if (n < 2)
        return n;
    return fib(n-1) + fib(n-2);
}

int main()
{
    // Fibonacci number to be calculated.  39 is big enough to take a
    // reasonable amount of time
    unsigned long n = 47;

    unsigned long result = fib(n);

    printf("Fibonacci number #%d is %lu.\n", n, result);

    return 0;
}
