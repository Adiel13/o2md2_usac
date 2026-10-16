#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arm_neon.h>

#define PI 3.14159265358979323846

typedef struct {
    float r_complex;
    float i_complex;
} complex;

void recursive_fft(complex* a, complex* y, int n, int inv) {
    if (n == 1) {
        y[0] = a[0];
        return;
    }

    float angle = (inv ? -2.0f : 2.0f) * PI / n;
    float32x4_t wn_re = vdupq_n_f32(cosf(angle));
    float32x4_t wn_im = vdupq_n_f32(sinf(angle));
    float32x4_t w_re = vdupq_n_f32(1.0f);
    float32x4_t w_im = vdupq_n_f32(0.0f);

    complex* a0 = (complex*)malloc((n / 2) * sizeof(complex));
    complex* a1 = (complex*)malloc((n / 2) * sizeof(complex));
    complex* y0 = (complex*)malloc((n / 2) * sizeof(complex));
    complex* y1 = (complex*)malloc((n / 2) * sizeof(complex));

    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    recursive_fft(a0, y0, n / 2, inv);
    recursive_fft(a1, y1, n / 2, inv);

    for (int k = 0; k < n / 2; k++) {
        float32x4_t y1_re = vdupq_n_f32(y1[k].r_complex);
        float32x4_t y1_im = vdupq_n_f32(y1[k].i_complex);

        float32x4_t t_re = vsubq_f32(vmulq_f32(w_re, y1_re), vmulq_f32(w_im, y1_im));
        float32x4_t t_im = vaddq_f32(vmulq_f32(w_re, y1_im), vmulq_f32(w_im, y1_re));

        float32x4_t y0_re = vdupq_n_f32(y0[k].r_complex);
        float32x4_t y0_im = vdupq_n_f32(y0[k].i_complex);

        y[k].r_complex     = vgetq_lane_f32(vaddq_f32(y0_re, t_re), 0);
        y[k].i_complex     = vgetq_lane_f32(vaddq_f32(y0_im, t_im), 0);
        y[k + n / 2].r_complex = vgetq_lane_f32(vsubq_f32(y0_re, t_re), 0);
        y[k + n / 2].i_complex = vgetq_lane_f32(vsubq_f32(y0_im, t_im), 0);

        float32x4_t temp_re = vsubq_f32(vmulq_f32(w_re, wn_re), vmulq_f32(w_im, wn_im));
        float32x4_t temp_im = vaddq_f32(vmulq_f32(w_re, wn_im), vmulq_f32(w_im, wn_re));
        w_re = temp_re;
        w_im = temp_im;
    }

    // Normalización solo si es inversa

    free(a0);
    free(a1);
    free(y0);
    free(y1);
}

int main() {
    int n = 4;

    // Entrada original
    complex x[] = {
        {1.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f},
        {0.0f, 0.0f}
    };

    // FFT directa
    complex y[n];
    recursive_fft(x, y, n, 0);
    printf("FFT directa:\n");
    for (int i = 0; i < n; i++)
        printf("y[%d] = (%f, %f)\n", i, y[i].r_complex, y[i].i_complex);

    // FFT inversa
    complex x_rec[n];
    recursive_fft(y, x_rec, n, 1);

    // 🔽 Normalización afuera de la función 🔽
    for (int i = 0; i < n; i++) {
        x_rec[i].r_complex /= n;
        x_rec[i].i_complex /= n;
    }

    printf("\nResultado de la inversa:\n");
    for (int i = 0; i < n; i++)
        printf("x[%d] = (%f, %f)\n", i, x_rec[i].r_complex, x_rec[i].i_complex);

    return 0;
}