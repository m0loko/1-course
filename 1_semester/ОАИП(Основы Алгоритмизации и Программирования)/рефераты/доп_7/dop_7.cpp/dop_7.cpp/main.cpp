#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void drawGraph(char symbol1, char symbol2, char symbol3, char symbol4, char symbol5, char background, int scale) {
    const int range = scale;  // �������� ���� �� -scale �� scale
    const double stepX = 0.25; // ��� ��� X
    const double stepY = 1;    // ��� ��� Y
    // ���� �� ��� Y, ������� � ������� �������
    for (double y = range; y >= -range; y -= stepY) {
        // ����� ����� ��� Y
        if (abs(y) < 0.1) {
            cout << "  0 "; // ����� ���
        }
        else {
            cout << setw(3) << static_cast<int>(round(y)) << " ";
        }
        // ���� �� ��� X
        for (double x = -range; x <= range; x += stepX) {
            // �������� �������
            double function1 = x * x;
            double function2 = -x * x;
            double function3 = x * x * x;
            double function4 = sin(x);
            double function5 = 3 * x;

            // ��������� ����� ������� y = x^2
            if (abs(function1 - y) < stepY / 2) {
                cout << symbol1;
            }
            // ��������� ����� ������� y = -x^2
            else if (abs(function2 - y) < stepY / 2) {
                cout << symbol2;
            }
            // ��������� ����� ������� y = x^3 
            else if (abs(function3 - y) < stepY) {
                cout << symbol3;
            }
            // ��������� ����� ������� y = sin(x)
            else if (abs(function4 - y) < stepY / 2) {
                cout << symbol4;
            }
            // ��������� ����� ������� y = 3x
            else if (abs(function5 - y) < stepY / 2) {
                cout << symbol5;
            }
            // ��������� ��� Y
            else if (abs(x) < stepX / 2 && abs(y) > stepY / 2) {
                cout << "|";
            }
            // ��������� ��� X
            else if (abs(y) < stepY / 2 && abs(x) > stepX / 2) {
                cout << "-";
            }
            // ����������� ����
            else if (abs(x) < stepX / 2 && abs(y) < stepY / 2) {
                cout << "+";
            }
            // ������ ������������ ����������� �����
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
    cout << "������� ������ ��� ������� y = x^2: ";
    cin >> symbol1;
    cout << "������� ������ ��� ������� y = -x^2: ";
    cin >> symbol2;
    cout << "������� ������ ��� ������� y = x^3: ";
    cin >> symbol3;
    cout << "������� ������ ��� ������� y = sin(x): ";
    cin >> symbol4;
    cout << "������� ������ ��� ������� y = 3x: ";
    cin >> symbol5;
    cout << "������� ������ ��� ���� �������: ";
    cin >> background;
    cout << "������� ������� ������� (������������� �� 5 �� 20): ";
    cin >> scale;
    cout << "\n������� ������� y = x^2, y = -x^2, y = x^3, y = sin(x) � y = 3x � ����������� ����:\n";
    drawGraph(symbol1, symbol2, symbol3, symbol4, symbol5, background, scale);
    return 0;
}
