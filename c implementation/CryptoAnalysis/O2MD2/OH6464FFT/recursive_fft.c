#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common_defs.h"

/* recursive_fft - see common_defs.h for more details */
void recursive_fft(complex* a, complex* y, int n, int inv)
{
   complex w, wn, twiddle;
   complex* a0;
   complex* a1;
   complex* y0;
   complex* y1;
   int i, k;

   /* Base Case */
   if (n == 1)
   {
      y[0] = a[0];
      return;
   }

   /* Calculate principal nth root of unity (i.e. exp(2*PI*i/n)) */
   if (inv)
   {
      double angle = -2*PI/(double)n;
      wn.r_complex = cos(angle);
      wn.i_complex = sin(angle);
   }
   else
   {
      double angle = 2*PI/(double)n;
      wn.r_complex = cos(angle);
      wn.i_complex = sin(angle); 
   }
   w.r_complex = 1.0;
   w.i_complex = 0.0;
   
   int n_2 = n/2;
   /* allocate memory for even/odd coefficients and corresponding FFTs */
   a0 = (complex*)malloc((n_2) * sizeof(complex));
   a1 = (complex*)malloc((n_2) * sizeof(complex));
   y0 = (complex*)malloc((n_2) * sizeof(complex));
   y1 = (complex*)malloc((n_2) * sizeof(complex));
   
   /* Extract even and odd coefficients */
   for (i = 0; i < n_2; i++)
   {
      int x= 2*i;
      a0[i] = a[x];
      a1[i] = a[x+1];
   }

   /* Calculate 2 FFTs of size n/2 */
   recursive_fft(a0, y0, n_2, inv);
   recursive_fft(a1, y1, n_2, inv);
   
   /* Combine results from half-size FFTs */
   for (k = 0; k < n_2; k++)
   {
      twiddle  = complex_mul_neon(w, y1[k]);
      y[k]     = complex_add_neon(y0[k], twiddle);
      y[k+n_2] = complex_sub_neon(y0[k], twiddle);
      w = complex_mul_neon(w, wn);
   }
   
   free(a0);
   free(a1);
   free(y0);
   free(y1);
   
   return;
}