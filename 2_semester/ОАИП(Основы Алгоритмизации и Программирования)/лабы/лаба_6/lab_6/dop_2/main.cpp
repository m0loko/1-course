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
        cout << "�������� ���������� �� ���������\n";
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
        cout << "������ ����" << endl;
    else
    {
        cout << "������:" << endl;
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
        cout << "\n ������ �������� �����";
        exit(1);
    }
    while (p)
    {
        frm << p->number << endl;
        p = p->next;
    }
    frm.close();
    cout << "������ ������� � ���� list.txt\n";
}

void fromFile(list*& p)
{
    ifstream frm("list.txt");
    if (frm.fail())
    {
        cout << "\n ������ �������� �����";
        exit(1);
    }
    float value;
    p = nullptr;
    while (frm >> value)
    {
        insert(p, value);
    }
    frm.close();
    cout << "\n������ ������ �� ����� list.txt\n";
}

void myVar(list* p) {
    float sm = 0;
    int count = 0;
    if (p == NULL) {
        cout << "������ ����" << endl;
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
            cout << "������� �������� = " << sm / count << endl;
        }
        else {
            cout << "��� ������������� ���������" << endl;
        }
    }
}

bool isEmpty(list* p) {
    return p == NULL;
}

void search(list* p, float value) {
    while (p != NULL) {
        if (p->number == value) {
            cout << "������� " << value << " ������ � ������." << endl;
            return;
        }
        p = p->next;
    }
    cout << "������� " << value << " �� ������ � ������." << endl;
}

void menu(void)
{
    cout << "�������� �����:" << endl;
    cout << " 1 - ���������� ��������" << endl;
    cout << " 2 - �������� ��������" << endl;
    cout << " 3 - ����� ��������" << endl;
    cout << " 4 - ����� ������ � ���������� ����" << endl;
    cout << " 5 - �������� ������ � ����" << endl;
    cout << " 6 - ������� ������ �� �����" << endl;
    cout << " 7 - ����� ������� �������� ������������� ���������" << endl;
    cout << " 8 - �����" << endl;
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
            cout << "������� ����� ";
            cin >> value;
            insert(first, value);
            printList(first);
            break;
        case 2:  
            if (!isEmpty(first))
            {
                cout << "������� ��������� �����: ";
                cin >> value;
                if (del(first, value))
                {
                    cout << "������� �����: " << value << endl;
                    printList(first);
                }
                else
                    cout << "����� �� �������" << endl;
            }
            else
                cout << "������ ����" << endl;
            break;
        case 3: 
            cout << "������� ����� ��� ������: ";
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
            cout << "������������ �����" << endl;
            menu();
            break;
        }
        cout << ">  ";
        cin >> choice;
    }
    cout << "�����" << endl;
    return 0;
}