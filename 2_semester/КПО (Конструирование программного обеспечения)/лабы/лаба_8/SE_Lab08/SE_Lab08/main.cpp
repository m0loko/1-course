#include <iostream>

using namespace std;

int defaultparm(int a, int b, int c, int d, int e, int f = 2, int g = 3)
{
	return (a + b + c + d + e + f + g) / 7;
};


int main()
{
	int a = defaultparm(1, 2, 3, 4, 5);
	int b = defaultparm(1, 2, 3, 4, 5, 6, 7);
}