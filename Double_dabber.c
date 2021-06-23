#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   This function takes an array of n unsigned integers,
   each holding a value in the range [0, 65535],
   representing a number in the range [0, 2**(16n)-1].
   arr[0] is the most significant "digit".
   This function returns a new array containing the given
   number as a string of decimal digits.

   For the sake of brevity, this example assumes that
   calloc and realloc will never fail.
*/
void double_dabble(int n, const unsigned int *arr, char **result)
{
    int nbits = 16*n;         /* length of arr in bits */
    int nscratch = nbits/3;   /* length of scratch in bytes */
    char *scratch = calloc(1 + nscratch, sizeof *scratch);
    int i, j, k;
    int smin = nscratch-2;    /* speed optimization */

    for (i=0; i < n; ++i) {
        for (j=0; j < 16; ++j) {
            /* This bit will be shifted in on the right. */
            int shifted_in = (arr[i] & (1 << (15-j)))? 1: 0;

            /* Add 3 everywhere that scratch[k] >= 5. */
            for (k=smin; k < nscratch; ++k)
              scratch[k] += (scratch[k] >= 5)? 3: 0;

            /* Shift scratch to the left by one position. */
            if (scratch[smin] >= 8)
              smin -= 1;
            for (k=smin; k < nscratch-1; ++k) {
                scratch[k] <<= 1;
                scratch[k] &= 0xF;
                scratch[k] |= (scratch[k+1] >= 8);
            }

            /* Shift in the new bit from arr. */
            scratch[nscratch-1] <<= 1;
            scratch[nscratch-1] &= 0xF;
            scratch[nscratch-1] |= shifted_in;
        }
    }

    /* Remove leading zeros from the scratch space. */
    for (k=0; k < nscratch-1; ++k)
      if (scratch[k] != 0) break;
    nscratch -= k;
    memmove(scratch, scratch+k, nscratch+1);

    /* Convert the scratch space from BCD digits to ASCII. */
    for (k=0; k < nscratch; ++k)
      scratch[k] += '0';

    /* Resize and return the resulting string. */
    *result = realloc(scratch, nscratch+1);
    return;
}

/*
   This test driver should print the following decimal values:
   246
   16170604
   1059756703745
*/
int main(void)
{
    unsigned int arr[] = { 246, 48748, 1 };
    char *text = NULL;
    int i;
    for (i=0; i < 3; ++i) {
        double_dabble(i+1, arr, &text);
        printf("%s\n", text);
        free(text);
    }
    return 0;
}
