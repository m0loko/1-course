#include <iostream>
#include <numbers>
using namespace std;

double cosinus(double x, int n) {
    if (n == 0) {
        return 0.0; 
    }
    else {
        double x_grad = x * numbers::pi / 180.0;
        return cos(n * x_grad) + cosinus(x, n - 1);
    }
}
int main() {
    setlocale(LC_ALL, "ru");
    double x;
    int n;
    cout << "������� �������� x (�������): ";
    cin >> x;
    cout << "������� ���������� n: ";
    cin >> n;
    double result = cosinus(x, n);
    cout << "����� cos(x) + cos(2x) + ... + cos(nx) = " << result << endl;
    return 0;
}