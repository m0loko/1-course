#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "\t\tПрограмма Угадайка\n";
    long n;
    cout << "Введите лимит: "; cin >> n;
    int low = 1, high = n;
    string zn;
    if (high >= low) {
        vector<int> steps;
        int count = 0;
        int left = low, right = high;
        cin.ignore();
        while (low <= high) {
            int middle;
            if (right - left > 25) {
                middle = (left + right) / 2;
            }
            else {
                middle = (left + right + 1) / 2;
            }
            cout << "Шаг: " << middle << endl;
            cout << "Введите 'мало', 'много', 'угадал': ";
            getline(cin, zn);
            if (zn == "много") {
                right = middle - 1;
                steps.push_back(middle);
                count++;
            }
            else if (zn == "мало") {
                left = middle + 1;
                steps.push_back(middle);
                count++;
            }
            else if (zn == "угадал") {
                steps.push_back(middle);
                int zagad = middle;
                count++;
                cout << "Максимальное количество шагов при бинарном поиске, log2(n), от числа " << n << " = " << ceil(log2(n)) << endl;
                cout << "Количество шагов, которое мы затратили: " << count << endl;
                cout << "От " << n << " до 1:" << endl;
                double bP1 = n;
                while (bP1 > 0.5) {
                    cout << ceil(bP1) << endl;
                    bP1 /= 2;
                }
                cout << "От " << n << " до " << zagad << ":" << endl;
                for (auto step : steps) {
                    cout << step << endl;
                }
                return 0;
            }
        }
    }
    else {
        cout << "ошибка";
    }
    return 0;
}