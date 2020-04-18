#include <iostream>
#include "declarations.h"
using namespace std;

void NotchFiltering(double parameter, double* reBuff, double* imBuff ,int wFFT, int hFFT) {
	for (int i = 0; i < hFFT; i++) {
		for (int j = 0; j < wFFT; j++) {
			if ((i == (hFFT / 2 - 1)) && (j == (wFFT / 2 - 1))) {
				reBuff[i * wFFT + j] *= parameter;
				imBuff[i * wFFT + j] *= parameter;
			} else {
				reBuff[i * wFFT + j] *= (1 + parameter);
				imBuff[i * wFFT + j] *= (1 + parameter);
			}
		}
	}
}