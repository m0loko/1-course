#pragma once
struct Stack {
    int data;
    Stack* next;
};

void push(int x, Stack*& myStk);
void toFile(Stack* myStk);
void fromFile(Stack*& myStk);
void clear(Stack*& myStk);
Stack* Var();
void printS(Stack*& myStk);
bool proverka(Stack* stk, int value);
Stack* findEqEl(Stack* Stack1, Stack* Stack2);
Stack* reverseStack(Stack* orig);