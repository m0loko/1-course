#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

struct list
{
    float number;
    list* next;
};


void insert(list*& p, float value) {
    list* newP = new list;
    if (newP != NULL)
    {
        newP->number = value;
        newP->next = p;
        p = newP;
    }
    else
    {
        cout << "Операция добавления не выполнена\n";
    }
}

float del(list*& p, float value)  
{
    list* previous, *current, * temp;
    if (value == p->number)
    {
        temp = p;
        p = p->next;    
        delete temp;     
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value)
        {
            previous = current;
            current = current->next; 
        }
        if (current != NULL)
        {
            temp = current;
            previous->next = current->next;
            delete(temp);
            return value;
        }
    }
    return 0;
}

void printList(list* p)
{
    if (p == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (p != NULL)
        {
            cout << "-->" << p->number;
            p = p->next;
        }
        cout << "-->NULL" << endl;
    }
}

void toFile(list* p)
{
    ofstream frm("list.txt");
    if (frm.fail())
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    while (p)
    {
        frm << p->number << endl;
        p = p->next;
    }
    frm.close();
    cout << "Список записан в файл list.txt\n";
}

void fromFile(list*& p)
{
    ifstream frm("list.txt");
    if (frm.fail())
    {
        cout << "\n Ошибка открытия файла";
        exit(1);
    }
    float value;
    p = nullptr;
    while (frm >> value)
    {
        insert(p, value);
    }
    frm.close();
    cout << "\nСписок считан из файла list.txt\n";
}

void myVar(list* p) {
    float sm = 0;
    int count = 0;
    if (p == NULL) {
        cout << "Список пуст" << endl;
    }
    else {
        while (p != NULL) {
            if (p->number > 0) {
                sm += p->number;  
                count++;
            }
            p = p->next;
        }
        if (count > 0) {
            cout << "Среднее значение = " << sm / count << endl;
        }
        else {
            cout << "Нет положительных элементов" << endl;
        }
    }
}

bool isEmpty(list* p) {
    return p == NULL;
}

void search(list* p, float value) {
    while (p != NULL) {
        if (p->number == value) {
            cout << "Элемент " << value << " найден в списке." << endl;
            return;
        }
        p = p->next;
    }
    cout << "Элемент " << value << " не найден в списке." << endl;
}

void menu(void)
{
    cout << "Сделайте выбор:" << endl;
    cout << " 1 - Добавление элемента" << endl;
    cout << " 2 - Удаление элемента" << endl;
    cout << " 3 - Поиск элемента" << endl;
    cout << " 4 - Вывод списка в консольное окно" << endl;
    cout << " 5 - Записать список в файл" << endl;
    cout << " 6 - Считать список из файла" << endl;
    cout << " 7 - Найти среднее значение положительных элементов" << endl;
    cout << " 8 - Выход" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    list* first = NULL;
    int choice;
    float value;
    menu();    
    cout << "> ";
    cin >> choice;
    while (choice != 8)
    {
        switch (choice)
        {
        case 1:  
            cout << "Введите число ";
            cin >> value;
            insert(first, value);
            printList(first);
            break;
        case 2:  
            if (!isEmpty(first))
            {
                cout << "Введите удаляемое число: ";
                cin >> value;
                if (del(first, value))
                {
                    cout << "Удалено число: " << value << endl;
                    printList(first);
                }
                else
                    cout << "Число не найдено" << endl;
            }
            else
                cout << "Список пуст" << endl;
            break;
        case 3: 
            cout << "Введите число для поиска: ";
            cin >> value;
            search(first, value);
            break;
        case 4:
            printList(first);
            break;
        case 5: 
            toFile(first);
            break;
        case 6: 
            fromFile(first);
            break;
        case 7: 
            myVar(first);
            break;
        default: 
            cout << "Неправильный выбор" << endl;
            menu();
            break;
        }
        cout << ">  ";
        cin >> choice;
    }
    cout << "Конец" << endl;
    return 0;
}