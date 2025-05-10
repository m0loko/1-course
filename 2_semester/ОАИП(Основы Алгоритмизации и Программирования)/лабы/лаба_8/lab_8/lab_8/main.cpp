#include <Windows.h>
#include <iostream>
using namespace std;

struct Node {
    char info;
    Node* next;
};

struct Queue {
    Node* begin ;
    Node* end;
    int maxSize;
    int currentSize;
};

void initQueue(Queue* q, int maxSize) {
    q->begin  = q->end = nullptr;
    q->maxSize = maxSize;
    q->currentSize = 0;
}

bool isZapolnen(Queue* q) {
    return q->currentSize >= q->maxSize;
}

bool isEmpty(Queue* q) {
    return q->currentSize == 0;
}

void dobavl(Queue* q, char ch) {
    if (isZapolnen(q)) {
        cout << "������� �����������\n";
        return;
    }
    Node* newNode = new Node;
    newNode->info = ch;
    newNode->next = nullptr;
    if (isEmpty(q)) {
        q->begin  = q->end = newNode;
    } else {
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

    Node* temp = q->begin ;
    q->begin  = q->begin ->next;
    delete temp;
    q->currentSize--;

    if (isEmpty(q)) {
        q->end = nullptr;
    }
}   

void printQueue(Queue* q) {
    if (isEmpty(q)) {
        cout << "������� �����\n";
        return;
    }

    Node* current = q->begin ;
    cout << "���������� �������: ";
    while (current) {
        cout << current->info << " ";
        current = current->next;
    }
    cout << "\n";
}

void showMenu() {
    cout << "\n����:\n"
         << "1. �������� ������\n"
         << "2. ������� ������\n"
         << "3. �������� �������\n"
         << "4. �������� ������\n"
         << "5. �����\n"
         << "�������� ��������:\n>";
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
    char ch;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                if (isZapolnen(&myQueue)) {
                    cout << "������� ���������\n";
                    break;
                }
                cout << "������� ������: ";
                cin >> ch;
                
                if (!isEmpty(&myQueue) && ch == myQueue.begin ->info) {
                    printQueue(&myQueue);
                    cout << "������� ������ �������: " << myQueue.currentSize << "\n";
                }
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
                cout << "�����\n";
                break;

            default:
                cout << "�������� �����\n";
        }
    } while (choice != 5);

    while (!isEmpty(&myQueue)) {
        del(&myQueue);
    }
    return 0;
}