#include <iostream>
#include "declarations.h"
using namespace std;

void Postprocessing(double* buff, double* reBuff, unsigned char* ucBuff, int w, int h, int wFFT, int hFFT) {
    for (int i = 0; i < hFFT; i++) {
        for (int j = 0; j < wFFT; j++) {
            if ((i < h) && (j < w)) {
                /* Extract the top-left chunk by original size */
                buff[i * w + j] = reBuff[i * wFFT + j] * pow(-1, i + j); // Decentring
                ucBuff[i * w + j] = (unsigned char)buff[i * w + j];    // Convert to unsigned char
            }
        }
    }
}