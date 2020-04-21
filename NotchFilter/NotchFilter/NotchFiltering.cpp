#include <iostream>
#include "declarations.h"
using namespace std;

void NotchFiltering(double parameter, double* reBuff, double* imBuff ,int wFFT, int hFFT) {
	for (int i = 0; i < hFFT; i++) {
		for (int j = 0; j < wFFT; j++) {
			if ((i == (hFFT / 2)) && (j == (wFFT / 2))) {
				reBuff[i * wFFT + j] *= parameter;
				imBuff[i * wFFT + j] *= parameter;
			} else {
				reBuff[i * wFFT + j] = reBuff[i * wFFT + j] * (1 + parameter);
				imBuff[i * wFFT + j] = imBuff[i * wFFT + j] * (1 + parameter);
			}
		}
	}

	//for (int i = 0; i < hFFT; i++) {
	//	for (int j = 0; j < wFFT; j++) {
	//		reBuff[i * wFFT + j] *= (1 + parameter);
	//		imBuff[i * wFFT + j] *= (1 + parameter);
	//	}
	//}

	//reBuff[wFFT * hFFT / 2 - 1] *= parameter;
	//imBuff[wFFT * hFFT / 2 - 1] *= parameter;

}