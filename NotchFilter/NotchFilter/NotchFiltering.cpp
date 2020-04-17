#include <iostream>
#include "declarations.h"
using namespace std;

void NotchFiltering(double C, unsigned char* reBuff, unsigned char* imBuff ,int wFFT, int hFFT)
{
	for (int i = 0; i < hFFT; i++)
	{
		for (int j = 0; j < wFFT; j++)
		{
			reBuff[i * wFFT + j] *= (1 + C);
		}
	}
	reBuff[hFFT / 2 * wFFT + wFFT / 2] *= C;

	for (int i = 0; i < hFFT; i++)
	{
		for (int j = 0; j < wFFT; j++)
		{
			imBuff[i * wFFT + j] *= (1 + C);
		}
	}
	imBuff[hFFT / 2 * wFFT + wFFT / 2] *= C;
}