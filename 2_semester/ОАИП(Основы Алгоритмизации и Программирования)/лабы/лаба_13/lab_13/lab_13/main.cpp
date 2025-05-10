#include <iostream>
#include <string>
#include <map>
#include <chrono>
using namespace std;

map<string, int> collisions;

struct HashTableOne {
    string* data;
    int count;
    int size;

    HashTableOne(int tableSize) {
        size = tableSize;
        count = 0;
        data = new string[size];
        for (int i = 0; i < size; ++i)
            data[i] = "";
    }

    int hashFunction(string& key) {
        int hash = 0;
        for (char c : key)
            hash = hash * 53 + c;
        return hash % size;
    }

    void resize() {
        int oldSize = size;
        size *= 2;
        string* oldData = data;
        data = new string[size];
        for (int i = 0; i < size; i++) data[i] = "";

        for (int i = 0; i < oldSize; i++) {
            if (oldData[i] != "") {
                insert(oldData[i]);
            }
        }
        delete[] oldData;
    }

    bool insert(string key) {
        if ((static_cast<double>(count) / size >= 0.5)) {
            resize();
        }

        int index = hashFunction(key);
        int startIndex = index;

        int originalIndex = -1; 
        while (true) {
            if (data[index] == "") {
                data[index] = key;
                count++;
                if (originalIndex != -1) {
                    collisions[key] = originalIndex;
                }
                return true;
            }
            else if (data[index] == key) {
                return false;
            }
            else {
                if (originalIndex == -1) {
                    originalIndex = index; 
                }
            }
            index = (index + 1) % size;
            if (index == startIndex) break;
        }

        return false;
    }


    void printTable() {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]: ";
            if (data[i] == "") cout << "пусто";
            else cout << data[i];
            cout << endl;
        }
    }

    bool search(string key) {
        int index = hashFunction(key);
        int start = index;
        while (data[index] != "") {
            if (data[index] == key) return true;
            index = (index + 1) % size;
            if (index == start) break;
        }
        return false;
    }

    void deleteByKey(string key) {
        int index = hashFunction(key);
        int start = index;
        while (data[index] != "") {
            if (data[index] == key) {
                data[index] = "";
                count--;
                cout << "Элемент " << key << " удалён" << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
        cout << "Элемент " << key << " не найден" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    int tableSize, choice, vb;
    string k;
    cout << "Введите размер хеш-таблицы (1: 16 элементов, 2: 32 элемента, 3: 64 элемента, 4:128 элементов)" << endl;
    cin >> vb;
    switch (vb) {
    case 1: tableSize = 16; break;
    case 2: tableSize = 32; break;
    case 3: tableSize = 64; break;
    case 4: tableSize = 128; break;
    default:
        cout << "Неверный выбор" << endl;
        return 1;
    }
    HashTableOne hashTable(tableSize);
    int elementsToInsert = 0;
    switch (tableSize) {
    case 16: elementsToInsert = 7; break;
    case 32: elementsToInsert = 15; break;
    case 64: elementsToInsert = 31; break;
    case 128: elementsToInsert = 63; break;
    }
    for (int i = 1; i <= elementsToInsert; i++) {
        hashTable.insert("a" + to_string(i));
    }
    while (true) {
        cout << "\n1 - вывод хеш-таблицы\n";
        cout << "2 - добавление элемента\n";
        cout << "3 - удаление элемента\n";
        cout << "4 - поиск элемента\n";
        cout << "5 - вывод коллизий\n";
        cout << "0 - выход\n";
        cout << "Сделайте выбор: ";
        cin >> choice;

        switch (choice) {
        case 0:
            return 0;
        case 1:
        {
            hashTable.printTable();
            break;
        }
        case 2:
        {
            cout << "Введите элемент для добавления: ";
            cin >> k;
            hashTable.insert(k);
            break;
        }
        case 3:
        {
            cout << "Введите ключ для удаления: ";
            cin >> k;
            hashTable.deleteByKey(k);
            break;
        }
        case 4:
        {
            cout << "Введите ключ для поиска: ";
            cin >> k;
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            bool found = hashTable.search(k);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Прошло " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl;
            if (found)
                cout << "Элемент найден: " << k << endl;
            else
                cout << "Элемент не найден" << endl;
            break;
        }
        case 5:
        {
            if (collisions.empty()) {
                cout << "Коллизий нет\n";
            }
            else {
                cout << "Коллизии:\n";
                for (auto el : collisions) {
                    cout << "Ключ: " << el.first << ", индекс: " << el.second << endl;
                }
            }
            break;
        }
        default:
        {
            cout << "Неверный выбор!" << endl;
            break;
        }
        }
    }

    return 0;
}
