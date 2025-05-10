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
        cout << "\n1 - ����� ���� 1\n"
            << "2 - �������� ������� � 1\n"
            << "3 - ������� ������������ �� 1\n"
            << "4 - ������� ����������� �� 1\n"
            << "5 - ������� ������� �� ������� �� 1\n"
            << "6 - �������� ������� � 2\n"
            << "7 - ���������� 1 � 2\n"
            << "0 - �����\n"
            << "�������� ��������: ";
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
            cout << "������� ����: ";
            cin >> k;
            a->x = k;
            h1.insert(a);
            break;
        }

        case 3: {
            AAA* max = (AAA*)h1.extractMax();
            if (max) {
                cout << "�������� ��������: " << max->x << endl;
                delete max;
            }
            else {
                cout << "���� �����!" << endl;
            }
            break;
        }

        case 4: {
            AAA* min = (AAA*)h1.extractMin();
            if (min) {
                cout << "�������� �������: " << min->x << endl;
                delete min;
            }
            else {
                cout << "���� �����!" << endl;
            }
            break;
        }

        case 5: {
            cout << "������� ������: ";
            cin >> index;
            AAA* elem = (AAA*)h1.extractI(index);
            if (elem) {
                cout << "�������� �������: " << elem->x << endl;
                delete elem;
            }
            else {
                cout << "�������� ������!" << endl;
            }
            break;
        }

        case 6: {
            AAA* a = new AAA;
            cout << "������� ����: ";
            cin >> k;
            a->x = k;
            h2.insert(a);
            break;
        }

        case 7: {
            heap::Heap* united = heap::unionHeap(&h1, &h2);
            if (united) {
                cout << "������������ ����:\n";
                united->scan(0);
                delete united;
            }
            else {
                cout << "������ �����������!" << endl;
            }
            break;
        }

        default:
            cout << "�������� �����!" << endl;
        }
    }
}