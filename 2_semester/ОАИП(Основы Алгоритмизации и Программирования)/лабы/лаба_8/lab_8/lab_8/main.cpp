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
        cout << "Очередь переполнена\n";
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
        cout << "Очередь пуста\n";
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
        cout << "Очередь пуста\n";
        return;
    }

    Node* current = q->begin ;
    cout << "Содержимое очереди: ";
    while (current) {
        cout << current->info << " ";
        current = current->next;
    }
    cout << "\n";
}

void showMenu() {
    cout << "\nМеню:\n"
         << "1. Добавить символ\n"
         << "2. Удалить символ\n"
         << "3. Показать очередь\n"
         << "4. Показать размер\n"
         << "5. Выход\n"
         << "Выберите действие:\n>";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Queue myQueue;
    int maxSize;
    cout << "Введите максимальный размер очереди: ";
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
                    cout << "Очередь заполнена\n";
                    break;
                }
                cout << "Введите символ: ";
                cin >> ch;
                
                if (!isEmpty(&myQueue) && ch == myQueue.begin ->info) {
                    printQueue(&myQueue);
                    cout << "Текущий размер очереди: " << myQueue.currentSize << "\n";
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
                cout << "Текущий размер: " << myQueue.currentSize << "\n";
                break;

            case 5:
                cout << "Выход\n";
                break;

            default:
                cout << "Неверный выбор\n";
        }
    } while (choice != 5);

    while (!isEmpty(&myQueue)) {
        del(&myQueue);
    }
    return 0;
}