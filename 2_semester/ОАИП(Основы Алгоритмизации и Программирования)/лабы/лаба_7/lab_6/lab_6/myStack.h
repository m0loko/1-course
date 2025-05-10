#pragma once
struct Stack
{
	int data;     
	Stack* next;
};
void push(int x, Stack*& myStk);
void toFile(Stack* myStk);
void fromFile(Stack*& myStk);
void clear(Stack*& myStk);
void Var(Stack*& myStk);
void printS(Stack*& myStk);
Stack* reverseStack(Stack* orig);