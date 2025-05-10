#include <iostream>
#include "myStack.h"
using namespace std;
int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    int x;
    Stack* myStk = nullptr; 
    for (;;) {
        cout << "�������� �������:" << endl;
        cout << "1 - ���������� �������� � ����" << endl;
        cout << "2 - ������ � ����" << endl;
        cout << "3 - ������ �� �����" << endl;
        cout << "4 - ����� �����" << endl;
        cout << "5 - ������� �����" << endl;
        cout << "6 - ������� Stack1 �� ������ ��������� � Stack2 �� ��������" << endl;
        cout << "7 - �����" << endl;
        cout << ">";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������: " << endl;
            cin >> x;
            push(x, myStk);
            break;
        case 2:
            toFile(myStk);
            break;
        case 3:
            fromFile(myStk);
            break;
        case 4:
            printS(myStk);
            break;
        case 5:
            clear(myStk);
            break;
        case 6:
            Var(myStk);
            break;
        case 7:
            return 0;
        default:
            cout << "�������� �����" << endl;
        }
    }
}