#include "List.h"
#include <iostream>
#include <cstring>
using namespace std;

void print(void* b) {
    Country* c = (Country*)b;
    cout << "�����������: " << c->name
        << ", �������: " << c->capital
        << ", ���������: " << c->population
        << ", �������: " << c->area
        << ", ������� ����������: " << c->president << endl;
}

void displayMenu() {
    cout << "\n����:\n";
    cout << "1. �������� ����������� � ������\n";
    cout << "2. �������� ����������� � �����\n";
    cout << "3. ������� ����������� �� ��������\n";
    cout << "4. ����� ����������� �� ��������\n";
    cout << "5. ������� ������ ����������\n";
    cout << "6. ������� ���������� ����������\n";
    cout << "7. �������� ������\n";
    cout << "8. �����\n";
    cout << "�������� ��������: ";
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
            cout << "������� �������� �����������: ";
            cin.getline(c->name, 50);
            cout << "������� �������: ";
            cin.getline(c->capital, 50);
            cout << "������� ����������� ���������: ";
            cin >> c->population;
            cout << "������� ������� (��. ��): ";
            cin >> c->area;
            cin.ignore();
            cout << "������� ������� ����������: ";
            cin.getline(c->president, 50);
            L1.Insert(c);
            cout << "����������� ��������� � ������\n";
            break;
        }
        case 2: {
            Country* c = new Country;
            cout << "������� �������� �����������: ";
            cin.getline(c->name, 50);
            cout << "������� �������: ";
            cin.getline(c->capital, 50);
            cout << "������� ����������� ���������: ";
            cin >> c->population;
            cout << "������� ������� (��. ��): ";
            cin >> c->area;
            cin.ignore();
            cout << "������� ������� ����������: ";
            cin.getline(c->president, 50);
            L1.InsertEnd(c);
            cout << "����������� ��������� � �����\n";
            break;
        }
        case 3: {
            char name[50];
            cout << "������� �������� ����������� ��� ��������: ";
            cin.getline(name, 50);
            Element* e = L1.SearchByName(name);
            if (e && L1.Delete(e)) {
                cout << "����������� �������.\n";
            }
            else {
                cout << "����������� �� �������\n";
            }
            break;
        }
        case 4: {
            char name[50];
            cout << "������� �������� ����������� ��� ������: ";
            cin.getline(name, 50);
            Element* e = L1.SearchByName(name);
            if (e) {
                Country* found = (Country*)e->Data;
                cout << "������� �����������: ";
                print(found);
            }
            else {
                cout << "����������� �� �������\n";
            }
            break;
        }
        case 5: {
            cout << "������ ����������:\n";
            L1.PrintList(print);
            break;
        }
        case 6: {
            int count = L1.CountList();
            cout << "���������� ���������� � ������: " << count << endl;
            break;
        }
        case 7: {
            if (L1.DeleteList()) {
                cout << "������ ������\n";
            }
            else {
                cout << "������ ��� ����\n";
            }
            break;
        }
        case 8: {
            running = false;
            cout << "��������� ���������\n";
            break;
        }
        default: {
            cout << "�������� �����\n";
            break;
        }
        }
    }

    L1.DeleteList();
    return 0;
}