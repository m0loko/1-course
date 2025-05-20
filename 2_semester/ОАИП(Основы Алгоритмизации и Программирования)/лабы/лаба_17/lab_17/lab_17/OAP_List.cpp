#include "List.h"
#include <iostream>
#include <cstring>
using namespace std;

void print(void* b) {
    Country* c = (Country*)b;
    cout << "Государство: " << c->name
        << ", Столица: " << c->capital
        << ", Население: " << c->population
        << ", Площадь: " << c->area
        << ", Фамилия президента: " << c->president << endl;
}

void displayMenu() {
    cout << "\nМеню:\n";
    cout << "1. Добавить государство в начало\n";
    cout << "2. Добавить государство в конец\n";
    cout << "3. Удалить государство по названию\n";
    cout << "4. Найти государство по названию\n";
    cout << "5. Вывести список государств\n";
    cout << "6. Подсчет количества государств\n";
    cout << "7. Очистить список\n";
    cout << "8. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    Object L1 = Create();
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            Country* c = new Country;
            cout << "Введите название государства: ";
            cin.getline(c->name, 50);
            cout << "Введите столицу: ";
            cin.getline(c->capital, 50);
            cout << "Введите численность населения: ";
            cin >> c->population;
            cout << "Введите площадь (кв. км): ";
            cin >> c->area;
            cin.ignore();
            cout << "Введите фамилию президента: ";
            cin.getline(c->president, 50);
            L1.Insert(c);
            cout << "Государство добавлено в начало\n";
            break;
        }
        case 2: {
            Country* c = new Country;
            cout << "Введите название государства: ";
            cin.getline(c->name, 50);
            cout << "Введите столицу: ";
            cin.getline(c->capital, 50);
            cout << "Введите численность населения: ";
            cin >> c->population;
            cout << "Введите площадь (кв. км): ";
            cin >> c->area;
            cin.ignore();
            cout << "Введите фамилию президента: ";
            cin.getline(c->president, 50);
            L1.InsertEnd(c);
            cout << "Государство добавлено в конец\n";
            break;
        }
        case 3: {
            char name[50];
            cout << "Введите название государства для удаления: ";
            cin.getline(name, 50);
            Element* e = L1.SearchByName(name);
            if (e && L1.Delete(e)) {
                cout << "Государство удалено.\n";
            }
            else {
                cout << "Государство не найдено\n";
            }
            break;
        }
        case 4: {
            char name[50];
            cout << "Введите название государства для поиска: ";
            cin.getline(name, 50);
            Element* e = L1.SearchByName(name);
            if (e) {
                Country* found = (Country*)e->Data;
                cout << "Найдено государство: ";
                print(found);
            }
            else {
                cout << "Государство не найдено\n";
            }
            break;
        }
        case 5: {
            cout << "Список государств:\n";
            L1.PrintList(print);
            break;
        }
        case 6: {
            int count = L1.CountList();
            cout << "Количество государств в списке: " << count << endl;
            break;
        }
        case 7: {
            if (L1.DeleteList()) {
                cout << "Список очищен\n";
            }
            else {
                cout << "Список уже пуст\n";
            }
            break;
        }
        case 8: {
            running = false;
            cout << "Программа завершена\n";
            break;
        }
        default: {
            cout << "Неверный выбор\n";
            break;
        }
        }
    }

    L1.DeleteList();
    return 0;
}