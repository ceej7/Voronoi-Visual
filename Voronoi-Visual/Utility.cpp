#include "stdafx.h"
#include <stdlib.h>
#include <ctime>
double randomf(double _min, double _max)
{
	double m1 = (double)(rand() % 2501) / 2501;
	_min++;
	double m2 = (double)((rand() % (int)(_max - _min + 1)) + _min);
	m2 = m2 - 1;
	return m1 + m2;
}