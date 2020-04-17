#include <iostream>
#include "declarations.h"
using namespace std;

void ZeroDeleting(double* buff, double* extrBuff, int w, int h, int wExtr, int hExtr)
{
	for (int i = 0; i < hExtr; i++)
	{
		for (int j = 0; j < wExtr; j++)
		{
			extrBuff[i * wExtr + j] = buff[i * w + j];
		}
	}
}