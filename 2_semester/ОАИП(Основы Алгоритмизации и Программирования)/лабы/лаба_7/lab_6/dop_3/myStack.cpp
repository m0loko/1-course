#include <iostream>
#include <fstream>
#include "myStack.h"
using namespace std;

void push(int x, Stack*& myStk) {
    Stack* e = new Stack;
    e->data = x;
    e->next = myStk;
    myStk = e;
}

void removeOtr(Stack*& myStk) {
    if (myStk == nullptr) {
        cout << "���� ����" << endl;
        return;
    }
    Stack* current = myStk;
    Stack* pred = nullptr;
    while (current != nullptr) {
        if (current->data < 0) {
            if (pred == nullptr) {
                myStk = current->next;
            }
            else {
                pred->next = current->next;
            }
            delete current;
            cout << "������ ������������� ������� ������" << endl;
            return;
        }
        pred = current;
        current = current->next;
    }
    cout << "������������� ��������� � ����� ���" << endl;
}

void printS(Stack*& myStk) {
    if (myStk == nullptr) {
        cout << "���� ����" << endl;
        return;
    }

    Stack* temp = myStk;
    while (temp != nullptr) {
        cout << "-->" << temp->data;
        temp = temp->next;
    }
    cout << "-->NULL\n";
}

void clear(Stack*& myStk) {
    while (myStk != nullptr) {
        Stack* temp = myStk;
        myStk = myStk->next;
        delete temp;
    }
    cout << "���� ������" << endl;
}