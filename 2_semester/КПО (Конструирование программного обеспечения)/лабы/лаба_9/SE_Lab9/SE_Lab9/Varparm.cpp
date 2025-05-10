#include "Varparm.h"
using namespace std;
namespace Varparm {
	int ivarparm(int n, ...) {
		if (n == 0)
			return 0;
		int pr = 1;
		int* p = &n;
		for (int i = 1; i < n + 1; i++)
			pr *= *(p + i);
		return pr;
	}

	int svarparm(short length, ...) {
		int* p = (int*)(&length);
		int max = 0;
		for (int i = 1; i < length+1; i++) {
			if (p[i] > max) max = p[i];
		}
		return max;
	}
	double fvarparm(float f, ...) {
		double sum = (double)f;
		double* p = (double*)(&f+1);
		if (f == FLT_MAX)
			return 0;
		for (int i = 0; p[i] != (double)FLT_MAX; i++) {
			sum += p[i];
		}
		return sum;
	}
	double dvarparm(double d, ...) {
		double sum = 0;
		double* p = (&d+1);
		int k = 0;
		if (d == DBL_MAX)
			return 0;
		for (int i = 0; p[i] != DBL_MAX; i++) {
			sum += p[i];
		}
		return sum;
	}

}