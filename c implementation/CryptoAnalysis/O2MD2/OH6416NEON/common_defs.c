#include <stdlib.h>
#include "common_defs.h"
#include <arm_neon.h>

/* complex_mul - see common_defs.h for more details */
complex complex_mul(complex a, complex b)
{
   complex ans;
   
   ans.r_complex = a.r_complex * b.r_complex - a.i_complex * b.i_complex;
   ans.i_complex = a.r_complex * b.i_complex + a.i_complex * b.r_complex;
   
   return ans;
}

complex complex_mul_neon(complex a, complex b)
{
    complex ans;
   
    float64x1_t a_vec = { a.r_complex };
    float64x1_t a_im = { a.i_complex };
    float64x1_t b_vec = { b.r_complex };
    float64x1_t b_im = { b.i_complex };

    // Real: a*r - b*i
    float64x1_t real = vsub_f64(vmul_f64(a_vec, b_vec), vmul_f64(a_im, b_im));

    // Imag: a*i + b*r
    float64x1_t imag = vadd_f64(vmul_f64(a_vec, b_im), vmul_f64(a_im, b_vec));

    ans.r_complex = vget_lane_f64(real, 0);
    ans.i_complex = vget_lane_f64(imag, 0);

    return ans;
}

#include <arm_neon.h>

complex complex_mul_neon_v2(complex a, complex b)
{
    complex ans;

    // Cargar [real, imag] de a y b en vectores de 2 dobles
    float64x2_t a_vec = { a.r_complex, a.i_complex };
    float64x2_t b_vec = { b.r_complex, b.i_complex };

    // Permutar b_vec para obtener [imag, real]
    float64x2_t b_swapped = vextq_f64(b_vec, b_vec, 1);  // b.i, b.r

    // Calcular los productos cruzados
    float64x2_t mult1 = vmulq_f64(a_vec, b_vec);        // a.r*b.r, a.i*b.i
    float64x2_t mult2 = vmulq_f64(a_vec, b_swapped);    // a.r*b.i, a.i*b.r

    // Real: a.r*b.r - a.i*b.i
    double real_part = vgetq_lane_f64(mult1, 0) - vgetq_lane_f64(mult1, 1);

    // Imag: a.r*b.i + a.i*b.r
    double imag_part = vgetq_lane_f64(mult2, 0) + vgetq_lane_f64(mult2, 1);

    ans.r_complex = real_part;
    ans.i_complex = imag_part;

    return ans;
}

/* complex_add - see common_defs.h for more details */
complex complex_add(complex a, complex b)
{
   complex ans;
   
   ans.r_complex = a.r_complex + b.r_complex;
   ans.i_complex = a.i_complex + b.i_complex;
   
   return ans;
}

complex complex_add_neon(complex a, complex b)
{
    complex ans;

    float64x1_t a_real = vdup_n_f64(a.r_complex);
    float64x1_t a_imag = vdup_n_f64(a.i_complex);
    float64x1_t b_real = vdup_n_f64(b.r_complex);
    float64x1_t b_imag = vdup_n_f64(b.i_complex);

    float64x1_t sum_real = vadd_f64(a_real, b_real);
    float64x1_t sum_imag = vadd_f64(a_imag, b_imag);

    ans.r_complex = vget_lane_f64(sum_real, 0);
    ans.i_complex = vget_lane_f64(sum_imag, 0);

    return ans;
}

complex complex_add_neon_v2(complex a, complex b)
{
    complex ans;

    // Cargar [real, imag] en un solo vector por cada complejo
    float64x2_t a_vec = { a.r_complex, a.i_complex };
    float64x2_t b_vec = { b.r_complex, b.i_complex };

    // Sumar ambos vectores
    float64x2_t result = vaddq_f64(a_vec, b_vec);

    // Guardar el resultado en la estructura complex
    ans.r_complex = vgetq_lane_f64(result, 0);
    ans.i_complex = vgetq_lane_f64(result, 1);

    return ans;
}

/* complex_sub - see common_defs.h for more details */
complex complex_sub(complex a, complex b)
{
   complex ans;
   
   ans.r_complex = a.r_complex - b.r_complex;
   ans.i_complex = a.i_complex - b.i_complex;
   
   return ans;
}

complex complex_sub_neon(complex a, complex b)
{
    complex ans;

    float64x1_t a_real = vdup_n_f64(a.r_complex);
    float64x1_t a_imag = vdup_n_f64(a.i_complex);
    float64x1_t b_real = vdup_n_f64(b.r_complex);
    float64x1_t b_imag = vdup_n_f64(b.i_complex);

    float64x1_t diff_real = vsub_f64(a_real, b_real);
    float64x1_t diff_imag = vsub_f64(a_imag, b_imag);

    ans.r_complex = vget_lane_f64(diff_real, 0);
    ans.i_complex = vget_lane_f64(diff_imag, 0);

    return ans;
}

complex complex_sub_neon_v2(complex a, complex b)
{
    complex ans;

    // Cargar [real, imag] en vectores de 128 bits
    float64x2_t a_vec = { a.r_complex, a.i_complex };
    float64x2_t b_vec = { b.r_complex, b.i_complex };

    // Resta de ambos componentes
    float64x2_t result = vsubq_f64(a_vec, b_vec);

    // Guardar el resultado
    ans.r_complex = vgetq_lane_f64(result, 0);
    ans.i_complex = vgetq_lane_f64(result, 1);

    return ans;
}

void bit_reverse_copy(complex* a, int n) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i < j) {
            complex tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
    }
}
#if 0
/* bit_reverse_copy - see common_defs.h for more details */
void bit_reverse_copy(complex* a, complex* a_rev_copy)
{
   a = 0;
}
#endif

void test(){
   
}

/* poly_mul - see common_defs.h for more details */
void poly_mul(complex* a, complex* b, int n)
{
   complex* ya;
   complex* yb;
   int j;
   
   /* Allocate storage for fft results */
   ya = (complex*)malloc(n * sizeof(complex));
   yb = (complex*)malloc(n * sizeof(complex));
   
   /* DFT of A and B */
   recursive_fft(a, ya, n, 0);
   recursive_fft(b, yb, n, 0);
   
   /* Pointwise Multiplication */
   for (j = 0; j < n; j++)
      ya[j] = complex_mul_neon(ya[j], yb[j]);
      
   /* Inverse DFT (swapped input and output arrays) */
   recursive_fft(ya, a, n, 1);
   
   /* Divide real part by n */
   for (j = 0; j < (n-1); j++)
      a[j].r_complex = a[j].r_complex/n;
    //normalize_neon(a, n);

   free(ya);
   free(yb);
}
void precompute_twiddles(complex* twiddles, int n, int inv) {
    double sign = inv ? -1.0 : 1.0;
    for (int k = 0; k < n/2; k++) {
        double angle = sign * 2.0 * PI * k / n;
        twiddles[k].r_complex = cos(angle);
        twiddles[k].i_complex = sin(angle);
    }
}
