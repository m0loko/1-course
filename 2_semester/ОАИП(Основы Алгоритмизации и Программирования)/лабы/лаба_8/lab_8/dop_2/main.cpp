#include <Windows.h>
#include <iostream>
using namespace std;

struct Node {
    double info;
    Node* next;
};

struct Queue {
    Node* begin;
    Node* end;
    int size;
};

void initQueue(Queue* q) {
    q->begin = q->end = nullptr;
    q->size = 0;
}

bool isEmpty(Queue* q) {
    return q->size == 0;
}

void vstavka(Queue* q, double value) {
    Node* newNode = new Node{ value, nullptr };
    if (isEmpty(q)) {
        q->begin = q->end = newNode;
    }
    else {
        q->end->next = newNode;
        q->end = newNode;
    }
    q->size++;
}

double udal(Queue* q) {
    if (isEmpty(q)) {
        cout << "Очередь пуста\n";
        return -1;
    }
    Node* temp = q->begin;
    double value = temp->info;
    q->begin = q->begin->next;
    delete temp;
    q->size--;

    if (isEmpty(q)) {
        q->end = nullptr;
    }
    return value;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "Очередь пуста\n";
        return;
    }
    Node* current = q->begin;
    cout << "Очередь: ";
    while (current) {
        cout << current->info << " ";
        current = current->next;
    }
    cout << "\n";
}

void sdvig(Queue* q) {
    if (q->size <= 1) return;

    Node* current = q->begin;
    Node* maxNode = q->begin;
    int maxIndex = 0, index = 0;

    while (current) { 
        if (current->info > maxNode->info) {
            maxNode = current;
            maxIndex = index;
        }
        current = current->next;
        index++;
    }

    for (int i = 0; i < maxIndex; i++) { 
        double temp = udal(q);
        vstavka(q, temp);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Queue q;
    initQueue(&q);
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " вещественных чисел: ";
    for (int i = 0; i < n; i++) {
        double num;
        cin >> num;
        vstavka(&q, num);
    }
    cout << "Исходная очередь:";
    printQueue(&q);
    sdvig(&q);
    cout << "Очередь после сдвига:";
    printQueue(&q);
    return 0;
}
