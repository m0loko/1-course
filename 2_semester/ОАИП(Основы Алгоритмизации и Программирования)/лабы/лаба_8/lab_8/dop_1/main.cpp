#include <iostream>
#include <Windows.h>
using namespace std;

struct Node {
    char info;
    Node* next;
};

struct Queue {
    Node* begin;
    Node* end;
    int maxSize;
    int currentSize;
};

void showMenu() {
    cout << "\n����:\n"
        << "1. �������� ������\n"
        << "2. ������� ������\n"
        << "3. �������� �������\n"
        << "4. �������� ������\n"
        << "5. ������� �� ��������\n"
        << "6. �����\n"
        << "�������� ��������:\n> ";
}

void initQueue(Queue* q, int maxSize) {
    q->begin = q->end = nullptr;
    q->maxSize = maxSize;
    q->currentSize = 0;
}

bool isFull(Queue* q) {
    return q->currentSize >= q->maxSize;
}

bool isEmpty(Queue* q) {
    return q->currentSize == 0;
}

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����\n";
        return;
    }
    Node* current = q->begin;
    cout << "���������� �������: ";
    while (current) {
        cout << current->info << " ";
        current = current->next;
    }
    cout << endl;
}

void dobavl(Queue* q, char ch) {
    if (isFull(q)) {
        cout << "������� �����������\n";
        return;
    }
    Node* newNode = new Node{ ch, nullptr };
    if (isEmpty(q)) {
        q->begin = q->end = newNode;
    }
    else {
        q->end->next = newNode;
        q->end = newNode;
    }
    q->currentSize++;
}

void del(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����\n";
        return;
    }
    Node* temp = q->begin;
    q->begin = q->begin->next;
    delete temp;
    q->currentSize--;

    if (isEmpty(q)) {
        q->end = nullptr;
    }
}

void delToEl(Queue* q, char el) {
    while (q->begin && q->begin->info != el) {
        Node* temp = q->begin;
        q->begin = q->begin->next;
        delete temp;
        q->currentSize--;
    }
    if (isEmpty(q)) {
        q->end = nullptr;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Queue myQueue;
    int maxSize;
    cout << "������� ������������ ������ �������: ";
    cin >> maxSize;
    initQueue(&myQueue, maxSize);

    int choice;
    char ch, el;

    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            if (isFull(&myQueue)) {
                cout << "������� ���������\n";
                break;
            }
            cout << "������� ������: ";
            cin >> ch;
            dobavl(&myQueue, ch);
            break;
        case 2:
            del(&myQueue);
            break;
        case 3:
            printQueue(&myQueue);
            break;
        case 4:
            cout << "������� ������: " << myQueue.currentSize << "\n";
            break;
        case 5:
            cout << "������� �������, �� �������� �������: ";
            cin >> el;
            delToEl(&myQueue, el);
            break;
        case 6:
            cout << "�����\n";
            break;
        default:
            cout << "�������� �����\n";
        }
    } while (choice != 6);

    return 0;
}
