#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void drawGraph(char symbol1, char symbol2, char symbol3, char symbol4, char symbol5, char background, int scale) {
    const int range = scale;  // диапазон осей от -scale до scale
    const double stepX = 0.25; // шаг для X
    const double stepY = 1;    // шаг для Y
    // цикл по оси Y, начиная с верхней границы
    for (double y = range; y >= -range; y -= stepY) {
        // вывод метки оси Y
        if (abs(y) < 0.1) {
            cout << "  0 "; // центр оси
        }
        else {
            cout << setw(3) << static_cast<int>(round(y)) << " ";
        }
        // Цикл по оси X
        for (double x = -range; x <= range; x += stepX) {
            // Значение функций
            double function1 = x * x;
            double function2 = -x * x;
            double function3 = x * x * x;
            double function4 = sin(x);
            double function5 = 3 * x;

            // отрисовка точки графика y = x^2
            if (abs(function1 - y) < stepY / 2) {
                cout << symbol1;
            }
            // отрисовка точки графика y = -x^2
            else if (abs(function2 - y) < stepY / 2) {
                cout << symbol2;
            }
            // отрисовка точки графика y = x^3 
            else if (abs(function3 - y) < stepY) {
                cout << symbol3;
            }
            // отрисовка точки графика y = sin(x)
            else if (abs(function4 - y) < stepY / 2) {
                cout << symbol4;
            }
            // отрисовка точки графика y = 3x
            else if (abs(function5 - y) < stepY / 2) {
                cout << symbol5;
            }
            // отрисовка оси Y
            else if (abs(x) < stepX / 2 && abs(y) > stepY / 2) {
                cout << "|";
            }
            // отрисовка оси X
            else if (abs(y) < stepY / 2 && abs(x) > stepX / 2) {
                cout << "-";
            }
            // пересечение осей
            else if (abs(x) < stepX / 2 && abs(y) < stepY / 2) {
                cout << "+";
            }
            // пустое пространство заполняется фоном
            else {
                cout << background;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    char symbol1, symbol2, symbol3, symbol4, symbol5, background;
    int scale;
    cout << "Введите символ для графика y = x^2: ";
    cin >> symbol1;
    cout << "Введите символ для графика y = -x^2: ";
    cin >> symbol2;
    cout << "Введите символ для графика y = x^3: ";
    cin >> symbol3;
    cout << "Введите символ для графика y = sin(x): ";
    cin >> symbol4;
    cout << "Введите символ для графика y = 3x: ";
    cin >> symbol5;
    cout << "Введите символ для фона графика: ";
    cin >> background;
    cout << "Введите масштаб графика (рекомендуется от 5 до 20): ";
    cin >> scale;
    cout << "\nГрафики функций y = x^2, y = -x^2, y = x^3, y = sin(x) и y = 3x с заполнением фона:\n";
    drawGraph(symbol1, symbol2, symbol3, symbol4, symbol5, background, scale);
    return 0;
}
