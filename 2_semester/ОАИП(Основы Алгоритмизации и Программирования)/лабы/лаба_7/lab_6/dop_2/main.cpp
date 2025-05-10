#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    int choice;
    int x;

    Stack* myStk = nullptr;
    Stack* Stack1 = nullptr;
    Stack* Stack2 = nullptr;

    for (;;) {
        cout << "Выберите команду:" << endl;
        cout << "1 - Добавление элемента в стек" << endl;
        cout << "2 - Запись в файл" << endl;
        cout << "3 - Чтение из файла" << endl;
        cout << "4 - Вывод стека" << endl;
        cout << "5 - Очистка стека" << endl;
        cout << "6 - Сделать Stack1 из положительных элементов и Stack2 из отрицательных" << endl;
        cout << "7 - Выход" << endl;
        cout << ">";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите элемент: " << endl;
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
            Var(myStk, Stack1, Stack2);
            cout << "------------\nStack1 (>0):\n";
            printS(Stack1);
            cout << "------------\nStack2 (<0):\n";
            printS(Stack2);
            cout << "------------\n";
            break;
        case 7:
            clear(myStk);
            clear(Stack1);
            clear(Stack2);
            return 0;
        default:
            cout << "Неверный выбор" << endl;
        }
    }
}