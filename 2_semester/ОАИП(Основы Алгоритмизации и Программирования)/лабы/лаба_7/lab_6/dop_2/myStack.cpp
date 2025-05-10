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

Stack* reverseStack(Stack* orig) {
    Stack* reversed = nullptr;
    while (orig != nullptr) {
        push(orig->data, reversed);
        orig = orig->next;
    }
    return reversed;
}

void toFile(Stack* myStk) {
    ofstream frm("Stack.txt");
    if (frm.fail()) {
        cout << "\nОшибка открытия файла";
        exit(1);
    }

    Stack* reversed = reverseStack(myStk);
    Stack* current = reversed;

    while (current != nullptr) {
        frm << current->data << endl;
        current = current->next;
    }

    frm.close();

    while (reversed != nullptr) {
        Stack* temp = reversed;
        reversed = reversed->next;
        delete temp;
    }

    cout << "Стек записан в файл Stack.txt\n";
}

void fromFile(Stack*& myStk) {
    clear(myStk);
    ifstream frm("Stack.txt");
    if (frm.fail()) {
        cout << "\nОшибка открытия файла";
        exit(1);
    }

    int data;
    while (frm >> data) {
        push(data, myStk);
    }

    frm.close();
    cout << "\nСтек считан из файла Stack.txt\n";
}

void clear(Stack*& myStk) {
    while (myStk != nullptr) {
        Stack* temp = myStk;
        myStk = myStk->next;
        delete temp;
    }
    cout << "Стек очищен" << endl;
}

void Var(Stack*& myStk, Stack*& Stack1, Stack*& Stack2) {
    clear(Stack1);
    clear(Stack2);

    Stack* temp = myStk;

    while (temp != nullptr) {
        if (temp->data > 0) {
            push(temp->data, Stack1);
        }
        else if (temp->data < 0) {
            push(temp->data, Stack2);
        }
        temp = temp->next;
    }
}

void printS(Stack*& myStk) {
    if (myStk == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }

    Stack* temp = myStk;
    while (temp != nullptr) {
        cout << "-->" << temp->data;
        temp = temp->next;
    }
    cout << "-->NULL\n";
}