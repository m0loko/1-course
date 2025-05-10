#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int choice;
    int x;
    Stack* myStk = nullptr;
    for (;;) {
        cout << "�������� �������:" << endl;
        cout << "1 - ���������� �������� � ����" << endl;
        cout << "2 - ������� ������ ������������� �������" << endl;
        cout << "3 - ����� �����" << endl;
        cout << "4 - ������� �����" << endl;
        cout << "5 - �����" << endl;
        cout << ">";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������: " << endl;
            cin >> x;
            push(x, myStk);
            break;
        case 2:
            removeOtr(myStk);
            break;
        case 3:
            printS(myStk);
            break;
        case 4:
            clear(myStk);
            break;
        case 5:
            clear(myStk);
            return 0;
        default:
            cout << "�������� �����" << endl;
        }
    }
}