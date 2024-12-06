#include <iostream>
#include <string>
using namespace std;

// ������� ��� ��������� ��������
void process(string&& temp) {
    cout << "��������� ��������� ������: " << temp << '\n';
}

// ������� ��� ���������� ��������
void process(const string& ref) {
    cout << "���������� ���������� ������: " << ref << '\n';
}

int main() {
    setlocale(LC_ALL, "ru");
    string str = "������";

    process(str);              // ���������� ���������� ������
    process("��������� ������"); // ���������� ��������� ������

    return 0;
}
