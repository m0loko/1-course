#include "Heap.h"
#include <iostream>
using namespace std;

heap::CMP cmpAAA(void* a1, void* a2)
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
    heap::CMP rc = heap::EQUAL;
    if (A1->x > A2->x)
        rc = heap::GREAT;
    else if (A2->x > A1->x)
        rc = heap::LESS;
    return rc;
#undef A2
#undef A1 
}

int main()
{
    setlocale(LC_ALL, "rus");
    int k, choice, index;
    heap::Heap h1 = heap::create(30, cmpAAA);
    heap::Heap h2 = heap::create(30, cmpAAA);

    for (;;)
    {
        cout << "\n1 - вывод кучи 1\n"
            << "2 - добавить элемент в 1\n"
            << "3 - удалить максимальный из 1\n"
            << "4 - удалить минимальный из 1\n"
            << "5 - удалить элемент по индексу из 1\n"
            << "6 - добавить элемент в 2\n"
            << "7 - объединить 1 и 2\n"
            << "0 - выход\n"
            << "Выберите действие: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            return 0;

        case 1:
            h1.scan(0);
            break;

        case 2: {
            AAA* a = new AAA;
            cout << "Введите ключ: ";
            cin >> k;
            a->x = k;
            h1.insert(a);
            break;
        }

        case 3: {
            AAA* max = (AAA*)h1.extractMax();
            if (max) {
                cout << "Извлечен максимум: " << max->x << endl;
                delete max;
            }
            else {
                cout << "Куча пуста!" << endl;
            }
            break;
        }

        case 4: {
            AAA* min = (AAA*)h1.extractMin();
            if (min) {
                cout << "Извлечен минимум: " << min->x << endl;
                delete min;
            }
            else {
                cout << "Куча пуста!" << endl;
            }
            break;
        }

        case 5: {
            cout << "Введите индекс: ";
            cin >> index;
            AAA* elem = (AAA*)h1.extractI(index);
            if (elem) {
                cout << "Извлечен элемент: " << elem->x << endl;
                delete elem;
            }
            else {
                cout << "Неверный индекс!" << endl;
            }
            break;
        }

        case 6: {
            AAA* a = new AAA;
            cout << "Введите ключ: ";
            cin >> k;
            a->x = k;
            h2.insert(a);
            break;
        }

        case 7: {
            heap::Heap* united = heap::unionHeap(&h1, &h2);
            if (united) {
                cout << "Объединенная куча:\n";
                united->scan(0);
                delete united;
            }
            else {
                cout << "Ошибка объединения!" << endl;
            }
            break;
        }

        default:
            cout << "Неверный выбор!" << endl;
        }
    }
}