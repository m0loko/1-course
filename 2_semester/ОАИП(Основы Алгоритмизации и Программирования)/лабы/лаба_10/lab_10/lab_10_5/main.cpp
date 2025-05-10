#include <iostream>
using namespace std;

double f(double x, int n) {
    if (n == 0)
        return 1;
    else if (n == 1)
        return x;
    else
        return x * x / (n * (n - 1)) * f(x, n - 2);
}

int main() {
    setlocale(LC_ALL, "ru");
    double x;
    int n;
    cout << "¬ведите значение x: ";
    cin >> x;
    cout << "¬ведите значение n (целое неотрицательное): ";
    cin >> n;
    if (n < 0) {
        cout << "ќшибка: n должно быть неотрицательным целым числом" << endl;
        return 1;
    }
    double result = f(x, n);
    cout << "–езультат f(x, n) = " << result << endl;
    return 0;
}
