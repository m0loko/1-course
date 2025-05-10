#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    int choice;
    int x;
    Stack* myStk = nullptr;
    for (;;) {
        cout << "Выберите команду:" << endl;
        cout << "1 - Добавление элемента в стек" << endl;
        cout << "2 - Удалить первый отрицательный элемент" << endl;
        cout << "3 - Вывод стека" << endl;
        cout << "4 - Очистка стека" << endl;
        cout << "5 - Выход" << endl;
        cout << ">";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите элемент: " << endl;
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
            cout << "Неверный выбор" << endl;
        }
    }
}