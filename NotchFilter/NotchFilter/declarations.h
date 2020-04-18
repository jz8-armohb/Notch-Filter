#pragma once
void FreqSpecCentring(double* imgBuff, int w, int h);
void ZeroFilling(double* oriBuff, double* newBuff, int wOri, int hOri, int wNew, int hNew);
void FFT_2D(int w, int h, double* A_Re, double* A_Im);
void NotchFiltering(double para, double* reBuff, double* imBuff, int wFFT, int hFFT);
void IFFT_2D(int w, int h, double* A_Re, double* A_Im);
void ZeroDeleting(double* buff, double* extrBuff, int w, int h, int wExtr, int hExtr);