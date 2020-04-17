#pragma once
void FreqSpecCentring(double* imgBuff, int w, int h);
void ZeroFilling(double* oriBuff, double* newBuff, int wOri, int hOri, int wNew, int hNew);
void FFT_2D(double* reBuff, double* imBuff, int w, int h);
void fft_2d(int w, int h, double* A_re, double* A_im);
void IFFT_2D(int w, int h, double* A_re, double* A_im);
void NotchFiltering(double C, double* reBuff, double* imBuff, int wFFT, int hFFT);
void ZeroDeleting(double* buff, double* extrBuff, int w, int h, int wExtr, int hExtr);