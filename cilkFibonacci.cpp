//
//  cilkFibonacci.cpp
//  ParallelProcessing
//
//  Created by Swapnil Gaikwad on 4/23/17.
//  Copyright © 2017 Swapnil Gaikwad. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

unsigned long fib(unsigned long n)
{
	if (n < 2)
		return n;
	unsigned long x = cilk_spawn fib(n-1);
	unsigned long y = fib(n-2);
	cilk_sync;
	return x + y;
}

int main(int argc, char *argv[])
{
	// Fibonacci number to be calculated.  39 is big enough to take a
	// reasonable amount of time
	unsigned long n = 42;
	
	// If we've got a parameter, assume it's the number of workers to be used
	if (argc > 1)
	{
		// Values less than 1, or parameters that aren't numbers aren't allowed
		if (atoi(argv[1]) < 1)
		{
			printf("Usage: fib [workers]\n");
			return 1;
		}
		
		// Set the number of workers to be used
		__cilkrts_set_param("nworkers", argv[1]);
	}
	
	unsigned long result = fib(n);
	
	// Display our results
	printf("Fibonacci number #%d is %lu.\n", n, result);
	
	return 0;
}
