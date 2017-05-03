//
//  tbbFibonacci.cpp
//  ParallelProcessing
//
//  Created by Swapnil Gaikwad on 4/23/17.
//  Copyright © 2017 Swapnil Gaikwad. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "tbb/tbb.h"

using namespace tbb;

unsigned long SerialFib( unsigned long n ) {
    if(n < 2)
        return n;
    else
        return SerialFib(n-1)+SerialFib(n-2);
}

class FibTask: public task {
public:
    const unsigned long n;
    unsigned long* const sum;
    FibTask( unsigned long n_, unsigned long* sum_ ) :
        n(n_), sum(sum_)
    {}
    task* execute() {      // Overrides virtual function task::execute
        if(n < 30) {
            *sum = SerialFib(n);
        } else {
            unsigned long x, y;
            FibTask& a = *new( allocate_child() ) FibTask(n-1,&x);
            FibTask& b = *new( task::allocate_root() ) FibTask(n-2,&y);
            // Set ref_count to 'two children plus one for the wait".
            set_ref_count(2);
            // Start b running.
            spawn( a );
            // Start a running and wait for all children (a and b).
            task::spawn_and_wait_for_all(b);
            // Do the sum
            *sum = x+y;
        }
        return NULL;
    }
};

unsigned long fib (unsigned long n) {
    unsigned long sum;
    task_scheduler_init anonymous;
    FibTask& a = *new(task::allocate_root()) FibTask(n,&sum);
    task::spawn_root_and_wait(a);
    return sum;
}

int main()
{
    // Fibonacci number to be calculated.  39 is big enough to take a
    // reasonable amount of time
    unsigned long n = 42;

    unsigned long result = fib(n);

    // Display our results
    printf("Fibonacci number #%d is %lu.\n", n, result);

    return 0;
}