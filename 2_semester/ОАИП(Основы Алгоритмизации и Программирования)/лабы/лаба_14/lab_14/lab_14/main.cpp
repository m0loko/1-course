#include <iostream>
#include <string>
#include <chrono>
using namespace std;

struct Node {
    string number;    
    string people;  
    Node* next;
};

struct HashTable {
    Node** table;
    int size;
};

int hashFunction(string key, int tableSize) {
    int h = 0;
    for (char ch : key)
        h ^= (h << 5) + (h >> 2) + (unsigned char)ch;
    return h % tableSize;
}

void init(HashTable& ht, int size) {
    ht.size = size;
    ht.table = new Node * [size];
    for (int i = 0; i < size; ++i)
        ht.table[i] = nullptr;
}

void insert(HashTable& ht, string number, string people) {
    int index = hashFunction(number, ht.size);
    Node* newNode = new Node{ number, people, ht.table[index] };
    ht.table[index] = newNode;
}

bool remove(HashTable& ht, string number) {
    int index = hashFunction(number, ht.size);
    Node* current = ht.table[index];
    Node* prev = nullptr;

    while (current) {
        if (current->number == number) {
            if (prev)
                prev->next = current->next;
            else
                ht.table[index] = current->next;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

Node* find(HashTable& ht, string number) {
    int index = hashFunction(number, ht.size);
    Node* current = ht.table[index];
    while (current) {
        if (current->number == number)
            return current;
        current = current->next;
    }
    return nullptr;
}

void print(HashTable& ht) {
    for (int i = 0; i < ht.size; ++i) {
        cout << "[" << i << "]: ";
        Node* current = ht.table[i];
        while (current) {
            cout << "(" << current->number << ", " << current->people << ") -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

void allRemove(HashTable& ht) {
    for (int i = 0; i < ht.size; ++i) {
        Node* current = ht.table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] ht.table;
}

int main() {
    setlocale(LC_ALL, "ru");
    HashTable ht;
    int size;
    cout << "������� ������ �������: ";
    cin >> size;
    cin.ignore();
    init(ht, size);

    int choice;
    do {
        cout << "\n����:\n";
        cout << "1 - ����� ���-�������" << endl;
        cout << "2 - ���������� ��������" << endl;
        cout << "3 - �������� ��������" << endl;
        cout << "4 - ����� ��������" << endl;
        cout << "0 - �����" << endl;
        cout << "�������� �����: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            print(ht);
        }
        else if (choice == 2) {
            string number, people;
            cout << "����� ��������: ";
            getline(cin, number);
            cout << "������: ";
            getline(cin, people);
            insert(ht, number, people);
            cout << "������� ��������\n";
        }
        else if (choice == 3) {
            string number;
            cout << "����� �������� ��� ��������: ";
            getline(cin, number);
            if (remove(ht, number))
                cout << "������� �����\n";
            else
                cout << "������� �� ������\n";
        }
        else if (choice == 4) {
            string number;
            cout << "����� �������� ��� ������: ";
            getline(cin, number);
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            Node* result = find(ht, number);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            if (result)
                cout << "�������: " << result->number << " - " << result->people << endl;
            else
                cout << "������� �� ������\n";

            cout << "������ " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ����������" << endl;
        }

    } while (choice != 0);

    allRemove(ht);
    return 0;
}
