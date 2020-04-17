#include <iostream>
#include <math.h>
#include "declarations.h"
using namespace std;

int main(int argc, char* argv[])
{
    double Overflow(double value, int thresholdLower, int thresholdUpper);

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
    double* tempYBuff = new double[w * h];
    double* tempYBuff_Re = new double[wFFT * hFFT];
    double* tempYBuff_Im = new double[wFFT * hFFT];

    /* Read Y component into the buffer, and make a backup */
    fread(oriYBuff, sizeof(unsigned char), w * h, oriImgPtr);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tempYBuff[i * w + j] = oriYBuff[i * w + j];
        }
    }

    /* (1) Centre the frequency spectrum & add a margin of zeros */
    //FreqSpecCentring(tempYBuff, w, h); 
    for (int i = 0; i < hFFT; i++)
    {
        for (int j = 0; j < wFFT; j++)
        {
            if ((i < h) && (j < w))
            {
                tempYBuff_Re[i * wFFT + j] = tempYBuff[i * w + j] * pow(-1, i + j);
                tempYBuff_Im[i * wFFT + j] = 0;
            }
            else
            {
                tempYBuff_Re[i * wFFT + j] = 0;
                tempYBuff_Im[i * wFFT + j] = 0;
            }
        }
    }

    /* (2) 2-D FFT */
    //ZeroFilling(tempYBuff, tempYBuff_Re, w, h, wFFT, hFFT); // Fill image buffer with zeros in order to apply FFT correctly
    //memset(tempYBuff_Im, 0, wFFT * hFFT);
    //FFT_2D(tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);
    fft_2d(wFFT, hFFT, tempYBuff_Re, tempYBuff_Im);
    /******************************************** Test ********************************************/
    for (int i = 100; i < 103; i++)
    {
        for (int j = 0; j < wFFT; j++)
        {
            printf("%-4.3lf\n", tempYBuff_Im[i * w + j]);
        }
    }
    /******************************************** Test ********************************************/



    /* (3) Notch filtering */
    //NotchFiltering(0, tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);

    /* (4) 2-D IFFT */
    for (int i = 0; i < hFFT * wFFT; i++)
    {
        tempYBuff_Im[i] = -tempYBuff_Im[i];
    }
    //FFT_2D(tempYBuff_Re, tempYBuff_Im, wFFT, hFFT);
    fft_2d(wFFT, hFFT, tempYBuff_Re, tempYBuff_Im);
    for (int i = 0; i < hFFT * wFFT; i++)
    {
        tempYBuff_Re[i] = tempYBuff_Re[i] / wFFT / hFFT;
    }
    //IFFT_2D(wFFT, hFFT, tempYBuff_Re, tempYBuff_Im);

    /* (5) Extract the top-left chunk by original size */
    ZeroDeleting(tempYBuff_Re, tempYBuff, wFFT, hFFT, w, h);

    /* (6) Decentring */
    FreqSpecCentring(tempYBuff, w, h);

    /* Convert to unsigned char */
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            Overflow(tempYBuff[i * w + j], 0, 255);
            notchYBuff[i * w + j] = (unsigned char)tempYBuff[i * w + j];
        }
    }


    /******************************************** Test ********************************************/
    for (int i = 100; i < 103; i++)
    {
        for (int j = 0; j < w; j++)
        {
            //printf("%-4d\n", notchYBuff[i * w + j]);
        }
    }
    /******************************************** Test ********************************************/


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


double Overflow(double value, int thresholdLower, int thresholdUpper)
{
    if (value > thresholdUpper)
    {
        return thresholdUpper;
    }

    if (value < thresholdLower)
    {
        return thresholdLower;
    }
}
