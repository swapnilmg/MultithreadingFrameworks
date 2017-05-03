//
//  openFibonacci.cpp
//  ParallelProcessing
//
//  Created by Swapnil Gaikwad on 4/23/17.
//  Copyright © 2017 Swapnil Gaikwad. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <omp.h>

unsigned long fib(unsigned long n)
{
	if (n < 2)
		return n;

	unsigned long x, y;
	#pragma omp task shared(x) firstprivate(n)
	x = fib(n-1);

	#pragma omp task shared(y) firstprivate(n)
	y = fib(n-2);

	#pragma omp taskwait
	return x + y;
}

int main()
{
    // Fibonacci number to be calculated.  39 is big enough to take a
    // reasonable amount of time
    unsigned long n = 42;

    // Time how long it takes to calculate the nth Fibonacci number
    unsigned long result;

	result = fib(n);

    printf("Fibonacci number #%d is %lu.\n", n, result);

    return 0;
}
