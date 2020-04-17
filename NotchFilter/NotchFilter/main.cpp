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
    unsigned char* tempYBuff = new unsigned char[w * h];
    unsigned char* tempYBuff_Re = new unsigned char[wFFT * hFFT];
    unsigned char* tempYBuff_Im = new unsigned char[wFFT * hFFT];

    /* Initialisation of U & V component (greyscale image) */
    memset(notchUBuff, 128, w * h);
    memset(notchVBuff, 128, w * h);

    /* Read Y component into the buffer, and make a backup */
    fread(oriYBuff, sizeof(unsigned char), w * h, oriImgPtr);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tempYBuff[i * w + j] = oriYBuff[i * w + j];
        }
    }

    /* Frequency spectrum centring */
    FreqSpecCentring(tempYBuff, w, h); 

    /* Fill image buffer with zeros in order to apply FFT correctly */
    ZeroFilling(tempYBuff, tempYBuff_Re, w, h, wFFT, hFFT);

    /* FFT */
    FFT_2D(tempYBuff_Re, tempYBuff_Re, wFFT, hFFT);

    /* Notch filtering */


    delete[]oriYBuff;
    delete[]notchYBuff;
    delete[]notchUBuff;
    delete[]notchVBuff;
    delete[]tempYBuff;
    delete[]tempYBuff_Re;
    delete[]tempYBuff_Im;
    fclose(oriImgPtr);
    fclose(notchImgPtr);
}