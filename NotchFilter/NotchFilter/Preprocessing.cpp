#include <iostream>
#include "declarations.h"
using namespace std;

void Preprocessing(double* buff, double* reBuff, double* imBuff, int w, int h, int wFFT, int hFFT) {
    for (int i = 0; i < hFFT; i++) {
        for (int j = 0; j < wFFT; j++) {
            if ((i < h) && (j < w)) {
                reBuff[i * wFFT + j] = buff[i * w + j] * pow(-1, i + j); // Centre the frequency specturm
                imBuff[i * wFFT + j] = 0; // Create a buffer for imaginary part
            } else {
                /* Add a margin filled with zeros, in order to apply FFT correctly */
                reBuff[i * wFFT + j] = 0;
                imBuff[i * wFFT + j] = 0;
            }
        }
    }
}