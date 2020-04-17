#include <iostream>
#include "declarations.h"
using namespace std;

int main(int argc, char* argv[])
{
    FILE* oriImgPtr;
    FILE* notchImgPtr;
    const char* oriImgName = argv[1];
    const char* notchImgName = argv[2];
    int w = 464;
    int h = 538;
    int wFFT = 512;
    int hFFT = 1024;

    /* Open the files */
    if (fopen_s(&oriImgPtr, oriImgName, "rb") == 0)
    {
        cout << "Successfully opened \"" << oriImgName << "\".\n";
    }
    else
    {
        cout << "Failed to open \"" << oriImgName << "\".\n";
        exit(-1);
    }
    if (fopen_s(&notchImgPtr, notchImgName, "wb") == 0)
    {
        cout << "Successfully opened \"" << notchImgName << "\".\n";
    }
    else
    {
        cout << "Failed to open \"" << notchImgName << "\".\n";
        exit(-1);
    }

    /* Space allocation */
    unsigned char* oriYBuff = new unsigned char[w * h];
    unsigned char* notchYBuff = new unsigned char[w * h];
    unsigned char* notchUBuff = new unsigned char[w * h];
    unsigned char* notchVBuff = new unsigned char[w * h];
    unsigned char* tempYBuff_Re = new unsigned char[wFFT * hFFT];
    unsigned char* tempYBuff_Im = new unsigned char[wFFT * hFFT];

    /* Read Y component into the buffer, and make a backup */
    fread(oriYBuff, sizeof(unsigned char), w * h, oriImgPtr);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            notchYBuff[i * w + j] = oriYBuff[i * w + j];
        }
    }

    /* Frequency spectrum centring */
    FreqSpecCentring(notchYBuff, w, h); 

    /* Fill image buffer with zeros in order to apply FFT correctly */
    ZeroFilling(notchYBuff, tempYBuff_Re, w, h, wFFT, hFFT);

    /* 2-D FFT */
    FFT_2D(tempYBuff_Re, tempYBuff_Re, wFFT, hFFT);

    /* Notch filtering */
    //NotchFiltering(0.2, tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);

    /* 2-D IFFT */
    for (int i = 0; i < hFFT; i++)
    {
        for (int j = 0; j < wFFT; j++)
        {
            tempYBuff_Im[i * w + j] = -tempYBuff_Im[i * w + j];
        }
    }
    FFT_2D(tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);
    for (int i = 0; i < hFFT; i++)
    {
        for (int j = 0; j < wFFT; j++)
        {
            //printf("-4%d ", tempYBuff_Re[i * w + j]);
            tempYBuff_Re[i * w + j] = (tempYBuff_Re[i * w + j]) * (double(wFFT * hFFT));
            //printf("-4%d\n", tempYBuff_Im[i * w + j]);
        }
    }

    /* Extract the top-left chunk by original size */
    ZeroDeleting(tempYBuff_Re, notchYBuff, wFFT, hFFT, w, h);

    /* Decentring */
    FreqSpecCentring(notchYBuff, w, h);

    /* Test */
    for (int i = 100; i < 103; i++)
    {
        for (int j = 0; j < w; j++)
        {
            printf("%-4d\n", tempYBuff_Re[i * w + j]);
        }
    }


    /* Write filtered data into file */
    fwrite(notchYBuff, sizeof(unsigned char), w * h, notchImgPtr);
    memset(notchUBuff, 128, w * h);
    memset(notchVBuff, 128, w * h);
    fwrite(notchUBuff, sizeof(unsigned char), w * h, notchImgPtr);
    fwrite(notchVBuff, sizeof(unsigned char), w * h, notchImgPtr);

    /* Close file pointers and free the memory */
    delete[]oriYBuff;
    delete[]notchYBuff;
    delete[]notchUBuff;
    delete[]notchVBuff;
    delete[]tempYBuff_Re;
    delete[]tempYBuff_Im;
    fclose(oriImgPtr);
    fclose(notchImgPtr);
}