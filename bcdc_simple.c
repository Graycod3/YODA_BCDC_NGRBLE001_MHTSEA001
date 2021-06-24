#include <stdio.h>
#include <time.h>
#include <stdio.h>
void BCDConversion(long long n)
{
   long long binaryInput = n;
   long long bcdResult = 0;
   long long shift = 0;


   while (binaryInput > 0) {
      bcdResult |= (binaryInput % 10) << (shift++ << 2); //shifts the remainder to the corresponding 4 bit postion in the bcdResult
      binaryInput /= 10;
   }

    printf(" value of BinaryInput; %x\n",bcdResult);
}

int main(void) {
    clock_t start, end;
     double cpu_time_used;

     start = clock();//start timing

  long N = 0;
  long q=4;
  long long random=0;
   for ( random = 100000; random <900000 ; random=random + 2 ){//for loop that gives the needed samples for each set

   BCDConversion(q);//converting function call
   N=N+1;//sample counter
   }
   end = clock(); // end timing
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("The implementation took %f seconds to execute \n", cpu_time_used);
     printf("You entered: %d", N);//samples confirmation
   return 0;
}
