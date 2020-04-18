#include <iostream>
#include "declarations.h"
using namespace std;

void ZeroFilling(double* oriBuff, double* newBuff, int wOri, int hOri, int wNew, int hNew)
{
	memset(newBuff, 0, wNew * hNew);

	for (int i = 0; i < hOri; i++) {
		for (int j = 0; j < wOri; j++) {
			newBuff[i * wNew + j] = oriBuff[i * wOri + j];
		}
	}
}