#include <stdio.h>
#include <time.h>
 
int main()
{
   clock_t begin = clock();
   int n = 100 , first = 0, second = 1, c;
   unsigned long next;

   for ( c = 0 ; c < n ; c++ )
   {
      if ( c <= 1 )
         next = c;
      else
      {
         next = first + second;
         first = second;
         second = next;
      }
   }
   printf("%lu\n",next);
   clock_t end = clock();
   double time_spent = (double)(end - begin);
   printf("Time spent: %f\n", time_spent);
   
   return 0;
}