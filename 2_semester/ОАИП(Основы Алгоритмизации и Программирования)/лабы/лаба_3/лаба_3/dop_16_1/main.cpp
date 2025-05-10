#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");

    ifstream first("FILE1.txt");
    if (!first.is_open()) {
        cout << "������ �������� ����� FILE1!" << endl;
        return 1;
    }

    ofstream second("FILE2.txt");
    if (!second.is_open()) {
        cout << "������ �������� ����� FILE2!" << endl;
        first.close();
        return 1;
    }

    string firstWord, secondWord, line, lastLine;

    if (!(first >> firstWord) || !(first >> secondWord)) {
        cout << "������: � ����� ������������ ����" << endl;
        first.close();
        second.close();
        return 1;
    }

    getline(first, line);
    cout << "������ �����: " << secondWord << endl;
    while (getline(first, line)) { 
        size_t found = line.find(secondWord);
        if (found != string::npos) {
            second << line << endl;
            lastLine = line;
        }
    }
    first.close();
    second.close();
    int digitCount = 0;
    for (char ch : lastLine) {
        if (isdigit(ch)) digitCount++;
    }
    cout << "���������� ���� � ��������� ������ FILE2: " << digitCount << endl;
    return 0;
}
