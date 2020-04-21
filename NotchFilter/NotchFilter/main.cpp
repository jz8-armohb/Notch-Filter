#include <iostream>
#include <math.h>
#include "declarations.h"
using namespace std;

int main(int argc, char* argv[]) {
    FILE* oriImgPtr;
    FILE* notchImgPtr;
    const char* oriImgName = argv[1];
    const char* notchImgName = argv[2];
    int w = 464;
    int h = 538;
    int wFFT = 512;
    int hFFT = 1024;

    /* Open the files */
    if (fopen_s(&oriImgPtr, oriImgName, "rb") == 0) {
        cout << "Successfully opened \"" << oriImgName << "\".\n";
    } else {
        cout << "Failed to open \"" << oriImgName << "\".\n";
        exit(-1);
    }
    if (fopen_s(&notchImgPtr, notchImgName, "wb") == 0) {
        cout << "Successfully opened \"" << notchImgName << "\".\n";
    } else {
        cout << "Failed to open \"" << notchImgName << "\".\n";
        exit(-1);
    }

    /* Space allocation */
    unsigned char* oriYBuff = new unsigned char[w * h];
    unsigned char* notchYBuff = new unsigned char[w * h];
    unsigned char* notchUBuff = new unsigned char[w * h];
    unsigned char* notchVBuff = new unsigned char[w * h];
    double* tempYBuff = new double[w * h];
    double* tempYBuff_Re = new double[wFFT * hFFT];
    double* tempYBuff_Im = new double[wFFT * hFFT];

    /* Read Y component into the buffer, and make a backup */
    fread(oriYBuff, sizeof(unsigned char), w * h, oriImgPtr);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            tempYBuff[i * w + j] = oriYBuff[i * w + j];
        }
    }

    /* (1) Pre-processing */
    Preprocessing(tempYBuff, tempYBuff_Re, tempYBuff_Im, w, h, wFFT, hFFT);

    /* (2) 2-D FFT */
    FFT_2D(wFFT, hFFT, tempYBuff_Re, tempYBuff_Im);
    /******************************************** Test ********************************************/
    //for (int i = 100; i < 103; i++) {
    //    for (int j = 0; j < wFFT; j++) {
    //        printf("%10.3lf%10.3lf\n", tempYBuff_Re[i * w + j], tempYBuff_Im[i * w + j]);
    //    }
    //}
    /******************************************** Test ********************************************/

    /* (3) Notch filtering */
    NotchFiltering(0.5, tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);

    /* (4) 2-D IFFT */
    IFFT_2D(wFFT, hFFT, tempYBuff_Re, tempYBuff_Im);

    /* (5) Post-processing */
    Postprocessing(tempYBuff, tempYBuff_Re, notchYBuff, w, h, wFFT, hFFT);

    /* Write filtered data into file */
    fwrite(notchYBuff, sizeof(unsigned char), w * h, notchImgPtr);
    memset(notchUBuff, 128, w * h);
    memset(notchVBuff, 128, w * h);
    fwrite(notchUBuff, sizeof(unsigned char), w * h, notchImgPtr);
    fwrite(notchVBuff, sizeof(unsigned char), w * h, notchImgPtr);

    /* Close file pointers and free the memory */
    delete[]oriYBuff;
    delete[]tempYBuff;
    delete[]notchYBuff;
    delete[]notchUBuff;
    delete[]notchVBuff;
    delete[]tempYBuff_Re;
    delete[]tempYBuff_Im;
    fclose(oriImgPtr);
    fclose(notchImgPtr);
}