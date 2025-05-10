#include "date.h"
#include "input.h"
#include<iostream>
#include<string>
#include <cctype>
using namespace std;

void getValidBirthday(int& bDay, int& bMonth, int year) {
    string input;
    while (true) {
        cout << "������� ���� ��� �������� � ������� ����: ";
        getline(cin, input);

        if (input.size() == 4 && input.find_first_not_of("0123456789") == string::npos) {
            bDay = stoi(input.substr(0, 2));
            bMonth = stoi(input.substr(2, 2));

            // �������� 29 �������
            if (bDay == 29 && bMonth == 2) {
                if (!isLeapYear(year)) {
                    cout << "��������� ���������� ���: " << nextLeapYear(year) << endl;
                    break;
                }
                else if (dayOfYear(bDay, bMonth, year) != -1) {
                    break;
                }
            }
            else if (dayOfYear(bDay, bMonth, year) != -1) {
                break;
            }
        }
        cout << "! ������������ ����. !" << endl;
    }
}