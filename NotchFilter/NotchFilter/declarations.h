#pragma once
void FreqSpecCentring(unsigned char* imgBuff, int w, int h);
void ZeroFilling(unsigned char* oriBuff, unsigned char* newBuff, int wOri, int hOri, int wNew, int hNew);
void FFT_2D(unsigned char* reBuff, unsigned char* imBuff, int w, int h);
void NotchFiltering(double C, unsigned char* reBuff, unsigned char* imBuff, int wFFT, int hFFT);
void ZeroDeleting(unsigned char* buff, unsigned char* extrBuff, int w, int h, int wExtr, int hExtr);