#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "\t\t��������� ��������\n";
    long n;
    cout << "������� �����: "; cin >> n;
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
            cout << "���: " << middle << endl;
            cout << "������� '����', '�����', '������': ";
            getline(cin, zn);
            if (zn == "�����") {
                right = middle - 1;
                steps.push_back(middle);
                count++;
            }
            else if (zn == "����") {
                left = middle + 1;
                steps.push_back(middle);
                count++;
            }
            else if (zn == "������") {
                steps.push_back(middle);
                int zagad = middle;
                count++;
                cout << "������������ ���������� ����� ��� �������� ������, log2(n), �� ����� " << n << " = " << ceil(log2(n)) << endl;
                cout << "���������� �����, ������� �� ���������: " << count << endl;
                cout << "�� " << n << " �� 1:" << endl;
                double bP1 = n;
                while (bP1 > 0.5) {
                    cout << ceil(bP1) << endl;
                    bP1 /= 2;
                }
                cout << "�� " << n << " �� " << zagad << ":" << endl;
                for (auto step : steps) {
                    cout << step << endl;
                }
                return 0;
            }
        }
    }
    else {
        cout << "������";
    }
    return 0;
}