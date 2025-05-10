#pragma once
struct Stack {
    int data;
    Stack* next;
};
void push(int x, Stack*& myStk);
void removeOtr(Stack*& myStk);
void printS(Stack*& myStk);
void clear(Stack*& myStk); 
