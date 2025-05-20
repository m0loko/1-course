#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

struct Node {
    int value;
    Node* next;
};

struct HashTable {
    Node** table;
    int size;
    int countSravn;
};

int hashFunction(int key, int tableSize) {
    return key % tableSize;
}

void init(HashTable& ht, int size) {
    ht.size = size;
    ht.countSravn = 0;
    ht.table = new Node * [size];
    for (int i = 0; i < size; i++)
        ht.table[i] = nullptr;
}

void insert(HashTable& ht, int value) {
    int index = hashFunction(value, ht.size);
    Node* newNode = new Node{ value, ht.table[index] };
    ht.table[index] = newNode;
}

Node* find(HashTable& ht, int value) {
    int index = hashFunction(value, ht.size);
    Node* current = ht.table[index];
    while (current) {
        ht.countSravn++;
        if (current->value == value)
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
            cout << current->value << " -> ";
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

void getFile(const string& filename, HashTable& ht) {
    ifstream file(filename);
    if (!file) {
        cout << "������ ��� �������� �����.\n";
        return;
    }

    int number;
    while (file >> number) {
        insert(ht, number);
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    int size;
    cout << "������� ������ ���-�������: ";
    cin >> size;
    HashTable ht;
    init(ht, size);
    string filename;
    cout << "������� ��� ����� � �������: ";
    cin >> filename;
    getFile(filename, ht);
    cout << "\n���-�������:\n";
    print(ht);
    int value;
    cout << "\n������� ����� ��� ������: ";
    cin >> value;
    auto begin = chrono::steady_clock::now();
    Node* result = find(ht, value);
    auto end = chrono::steady_clock::now();
    if (result)
        cout << "����� �������: " << result->value << endl;
    else
        cout << "����� �� �������\n";
    cout << "������ " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ����������\n";
    cout << "���������� ��������� ��� ������: " << ht.countSravn << endl;

    allRemove(ht);
    return 0;
}
