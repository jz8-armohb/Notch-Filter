#pragma once
void Preprocessing(double* buff, double* reBuff, double* imBuff, int w, int h, int wFFT, int hFFT);
void FFT_2D(int w, int h, double* A_Re, double* A_Im);
void NotchFiltering(double para, double* reBuff, double* imBuff, int wFFT, int hFFT);
void IFFT_2D(int w, int h, double* A_Re, double* A_Im);
void Postprocessing(double* buff, double* reBuff, unsigned char* ucBuff, int w, int h, int wFFT, int hFFT);