#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common_defs.h"

void iterative_fft(complex* a, int n, int inv)
{
    bit_reverse_copy(a, n);

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inv ? -1 : 1);
        complex wn = { cos(angle), sin(angle) };

        for (int i = 0; i < n; i += len) {
            complex w = { 1.0, 0.0 };
            for (int j = 0; j < len / 2; j++) {
                complex u = a[i + j];
                complex v = complex_mul(w, a[i + j + len / 2]);

                a[i + j] = complex_add(u, v);
                a[i + j + len / 2] = complex_sub(u, v);

                w = complex_mul(w, wn);
            }
        }
    }

    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i].r_complex /= n;
            a[i].i_complex /= n;
        }
    }
}
