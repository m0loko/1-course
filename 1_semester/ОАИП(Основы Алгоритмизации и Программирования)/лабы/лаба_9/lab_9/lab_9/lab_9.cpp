#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return 5 * x - 1 + x * x * x;
}
double dichom(double a, double b, double e) {
    double x;
    do
    {
        x = (a + b) / 2;
        if ((f(x) * f(a)) <= 0)
            b = x;
        else
            a = x;

    } while (abs(a - b) >= 2 * e);
    return x;
}
int main() {
    setlocale(LC_ALL, "ru");
    double a = 0, b = 1, e = 0.0001;
    double area = dichom(a, b, e);
    cout << "X = " << area << endl;
    return 0;
}
