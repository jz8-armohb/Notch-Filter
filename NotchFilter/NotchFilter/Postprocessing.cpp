#include <iostream>
#include <algorithm>
#include "declarations.h"
using namespace std;

double Overflow(double value, int thresholdLower, int thresholdUpper) {
    if (value > thresholdUpper) {
        return thresholdUpper;
    }

    if (value < thresholdLower) {
        return thresholdLower;
    }
}

void Postprocessing(double* buff, double* reBuff, unsigned char* ucBuff, int w, int h, int wFFT, int hFFT) {
    for (int i = 0; i < hFFT; i++) {
        for (int j = 0; j < wFFT; j++) {
            if ((i < h) && (j < w)) {
                /* Extract the top-left chunk by original size */
                buff[i * w + j] = reBuff[i * wFFT + j] * pow(-1, i + j); // Decentring
                //buff[i * w + j] = abs(buff[i * w + j]);
                //Overflow(buff[i * w + j], 0, 255);
                //ucBuff[i * w + j] = (unsigned char)buff[i * w + j];    // Convert to unsigned char
            }
        }
    }

    double m = *min_element(buff, buff + w * h);    // Minimum
    double M = *max_element(buff, buff + w * h);    // Maximum
    //cout << m << " " << M << endl;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            buff[i * w + j] = 255 / (M - m) * (buff[i * w + j] - m);    // Remapping to 0-255
            //Overflow(buff[i * w + j], 0, 255);
            ucBuff[i * w + j] = (unsigned char)buff[i * w + j];    // Convert to unsigned char
        }
    }
}