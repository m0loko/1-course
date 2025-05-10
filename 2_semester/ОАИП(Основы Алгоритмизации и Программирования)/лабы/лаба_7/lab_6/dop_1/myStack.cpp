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

bool proverka(Stack* stk, int value) {
    Stack* current = stk;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Stack* findEqEl(Stack* Stack1, Stack* Stack2) {
    Stack* result = nullptr;
    Stack* current = Stack1;

    while (current != nullptr) {
        int value = current->data;
        if (proverka(Stack2, value) && !proverka(result, value)) {
            push(value, result);
        }
        current = current->next;
    }
    return result;
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

Stack* Var() {   
    Stack* Stack1 = nullptr;
    push(12, Stack1);
    push(14, Stack1);
    push(2, Stack1);
    push(4, Stack1);

    Stack* Stack2 = nullptr;
    push(1, Stack2);
    push(2, Stack2);
    push(3, Stack2);
    push(4, Stack2);

    Stack* glStack = findEqEl(Stack1, Stack2);

    cout << "Повторяющиеся элементы: ";
    printS(glStack);
    clear(Stack1);
    clear(Stack2);
    return glStack;
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