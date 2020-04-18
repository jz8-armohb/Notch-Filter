#include <iostream>
#include <math.h>
#include "declarations.h"
using namespace std;

void FreqSpecCentring(double* imgBuff, int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			imgBuff[i * w + j] = imgBuff[i * w + j] * pow(-1, i + j);
		}
	}
}