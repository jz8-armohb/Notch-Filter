#include <iostream>
#include "declarations.h"
using namespace std;

void IFFT_2D(int w, int h, double* A_re, double* A_im) {
	for (int i = 0; i < w * h; i++) {
		A_im[i] = -A_im[i];
	}

	FFT_2D(w, h, A_re, A_im);

	for (int i = 0; i < w * h; i++) {
		A_re[i] = A_re[i] / w / h;
		A_im[i] = -A_im[i];
	}
}