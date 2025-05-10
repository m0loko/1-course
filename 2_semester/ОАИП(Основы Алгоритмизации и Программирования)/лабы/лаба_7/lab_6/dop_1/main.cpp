#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    Stack* myStk = nullptr; 

    for (;;) {
        cout << "�������� �������:" << endl;
        cout << "1 - ������ � ����" << endl;
        cout << "2 - ������ �� �����" << endl;
        cout << "3 - ����� Stack" << endl;
        cout << "4 - ������� Stack" << endl;
        cout << "5 - ������ Stack �� ������������� ��������� ������ Stack1 � Stack2" << endl;
        cout << "6 - �����" << endl;
        cout << ">";
        cin >> choice;

        switch (choice) {
        case 1:
            toFile(myStk);
            break;
        case 2:
            fromFile(myStk);
            break;
        case 3:
            printS(myStk);
            break;
        case 4:
            clear(myStk);
            break;
        case 5:
            myStk = Var(); 
            break;
        case 6:
            return 0;
        default:
            cout << "�������� �����" << endl;
        }
    }
}