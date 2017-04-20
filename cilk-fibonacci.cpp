/*
 * fib.cpp
 *
 * Time how long it takes to calculate a Fibonacci number. See
 * http://en.wikipedia.org/wiki/Fibonacci_number for information about the
 * Fibonacci sequence. This application demonstrates the use of the cilk_spawn
 * and cilk_sync keywords.
 *
 * This program takes a single parameter to specify the number of workers to
 * be used in the calculation. If not specified, Intel Cilk Plus will query
 * the operating system to determine the number of cores on the system and use
 * that many workers.
 */

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
    int n = 47;

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

    // Time how long it takes to calculate the nth Fibonacci number
    clock_t start = clock();
    unsigned long result = fib(n);
    clock_t end = clock();

    // Display our results
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci number #%d is %lu.\n", n, result);
    printf("Calculated in %.3f seconds using %d workers.\n",
           duration, __cilkrts_get_nworkers());

    return 0;
}