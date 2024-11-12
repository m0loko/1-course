#include<iostream>
using namespace std;
int main()
{
	double a, b, c;
	cin >> a; cin >> b; cin >> c;
	double min=a;
	if (b<min)
	{
		min = b;
	}
	if (c<min)
	{
		min = c;
	}
	cout << "минимум=" << min;
	return 0;
}	