//4 ���������� 3
#include <iostream>
using namespace std;

struct Item {
    int data;
    Item* next;
};

Item* head = nullptr;
Item* tail = nullptr;

bool isNull(void) {  // �������� �� �������
    return (head == nullptr);
}

void deleteLast() {  
    if (isNull()) {
        cout << "������� �����" << endl;
    }
    else if (head == tail) {  
        delete head;
        head = tail = nullptr;
    }
    else {
        Item* current = head;
        while (current->next != tail) { 
            current = current->next;
        }
        delete tail;  
        tail = current;
        tail->next = nullptr;
    }
}

void getFromHead() {  
    if (isNull()) {
        cout << "������� �����" << endl;
    }
    else {
        cout << "������ = " << head->data << endl;
    }
}

void insertToQueue(int x) { 
    Item* newItem = new Item;
    newItem->data = x;
    newItem->next = nullptr;

    if (isNull()) {  
        head = tail = newItem;
        return;
    }

    Item* prev = nullptr;
    Item* curr = head;

    while (curr != nullptr && (curr->data > x || (curr->data == x && curr->next != nullptr))) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) {  
        newItem->next = head;
        head = newItem;
    }
    else if (curr == nullptr) {  
        tail->next = newItem;
        tail = newItem;
    }
    else { 
        prev->next = newItem;
        newItem->next = curr;
    }
}

void printQueue() {
    if (isNull()) {
        cout << "������� �����" << endl;
    }
    else {
        cout << "������� = ";
        Item* p = head;
        while (p != nullptr) {
            cout << p->data << " -> ";
            p = p->next;
        }
        cout << "nullptr" << endl;
    }
}

void clrQueue() {  
    while (!isNull()) {
        deleteLast();
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    int choice = 1, z;
    while (choice != 0) {
        cout << "1 - �������� �������" << endl;
        cout << "2 - �������� ������� � ������" << endl;
        cout << "3 - ������� ������� � �����" << endl;
        cout << "4 - ������� ��������" << endl;
        cout << "5 - �������� �������" << endl;
        cout << "0 - �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������: ";
            cin >> z;
            insertToQueue(z);
            printQueue();
            break;
        case 2:
            getFromHead();
            break;
        case 3:
            deleteLast();
            break;
        case 4:
            printQueue();
            break;
        case 5:
            clrQueue();
            break;
        }
    }
    clrQueue(); 
    return 0;
}