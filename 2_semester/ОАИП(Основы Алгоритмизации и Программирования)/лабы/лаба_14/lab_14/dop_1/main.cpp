#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cctype>
using namespace std;

struct Node {
    string word;
    Node* next;
};

struct HashTable {
    Node** table;
    int size;
    int sravn; 
};

int hashFunction(string& key, int tableSize) {
    int h = 0;
    for (char ch : key)
        h ^= (h << 5) + (h >> 2) + (unsigned char)ch;
    return h % tableSize;
}

void init(HashTable& ht, int size) {
    ht.size = size;
    ht.table = new Node * [size];
    ht.sravn = 0;
    for (int i = 0; i < size; i++)
        ht.table[i] = nullptr;
}

void insert(HashTable& ht, string word) {
    int index = hashFunction(word, ht.size);
    Node* newNode = new Node{ word, ht.table[index] };
    ht.table[index] = newNode;
}

bool remove(HashTable& ht, string word) {
    int index = hashFunction(word, ht.size);
    Node* current = ht.table[index];
    Node* prev = nullptr;

    while (current) {
        ht.sravn++; 
        if (current->word == word) {
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

Node* find(HashTable& ht, string word) {
    int index = hashFunction(word, ht.size);
    Node* current = ht.table[index];
    while (current) {
        ht.sravn++;
        if (current->word == word)
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
            cout << current->word << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

void removeWordStart(HashTable& ht, char letter) {
    for (int i = 0; i < ht.size; i++) {
        Node* current = ht.table[i];
        Node* prev = nullptr;

        while (current) {
            if (tolower(current->word[0]) == tolower(letter)) {
                if (prev)
                    prev->next = current->next;
                else
                    ht.table[i] = current->next;
                delete current;
                current = (prev) ? prev->next : ht.table[i]; 
            }
            else {
                prev = current;
                current = current->next;
            }
        }
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

void getFile(string& filename, HashTable& ht) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка при открытии файла\n";
        return;
    }

    string word;
    while (file >> word) {
        insert(ht, word);
    }

    file.close();
}

int main() {
    setlocale(LC_ALL, "ru");

    int size;
    cout << "Введите размер таблицы: ";
    cin >> size;
    cin.ignore();
    HashTable ht;
    init(ht, size);
    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    getFile(filename, ht);
    cout << "\nХеш-таблица:\n";
    print(ht);
    string wordToFind;
    cout << "\nВведите слово для поиска: ";
    getline(cin, wordToFind);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Node* result = find(ht, wordToFind);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    if (result) {
        cout << "Слово найдено: " << result->word << endl;
    }
    else {
        cout << "Слово не найдено\n";
    }
    cout << "Прошло " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд\n";
    cout << "Количество сравнений при поиске: " << ht.sravn << endl;
    char letter;
    cout << "\nВведите букву для удаления слов, начинающихся на неё: ";
    cin >> letter;
    removeWordStart(ht, letter);
    cout << "\nХеш-таблица после удаления слов, начинающихся на '" << letter << "':\n";
    print(ht);
    allRemove(ht);
    return 0;
}
