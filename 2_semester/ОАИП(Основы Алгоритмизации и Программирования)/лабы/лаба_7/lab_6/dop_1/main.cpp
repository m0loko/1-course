#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    Stack* myStk = nullptr; 

    for (;;) {
        cout << "Выберите команду:" << endl;
        cout << "1 - Запись в файл" << endl;
        cout << "2 - Чтение из файла" << endl;
        cout << "3 - Вывод Stack" << endl;
        cout << "4 - Очистка Stack" << endl;
        cout << "5 - Делаем Stack из повторяющихся элементов стеков Stack1 и Stack2" << endl;
        cout << "6 - Выход" << endl;
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
            cout << "Неверный выбор" << endl;
        }
    }
}