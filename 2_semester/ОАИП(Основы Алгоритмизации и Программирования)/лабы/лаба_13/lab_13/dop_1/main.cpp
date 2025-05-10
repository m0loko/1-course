#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <vector>

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
        int a = rand() % size;
        int b = rand() % size;
        for (char c : key)
        {
            hash = (a * hash + c + b) % size;
        }
        return hash;
        
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
        bool collisionFlag = false;

        do {
            if (data[index] == "") {
                data[index] = key;
                count++;
                return true;
            }
            else if (!collisionFlag && data[index] != key) {
                collisions[key] = startIndex;
                collisionFlag = true;
            }
            index = (index + 1) % size;
        } while (index != startIndex);

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
                cout << "Ёлемент " << key << " удалЄн" << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
        cout << "Ёлемент " << key << " не найден" << endl;
    }
};
struct HashTableTwo {
    string* data;
    int count;
    int size;

    HashTableTwo(int tableSize) {
        size = tableSize;
        count = 0;
        data = new string[size];
        for (int i = 0; i < size; i++)
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
        bool collisionFlag = false;

        do {
            if (data[index] == "") {
                data[index] = key;
                count++;
                return true;
            }
            else if (!collisionFlag && data[index] != key) {
                collisions[key] = startIndex;
                collisionFlag = true;
            }
            index = (index + 1) % size;
        } while (index != startIndex);

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
                cout << "Ёлемент " << key << " удалЄн" << endl;
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
        cout << "Ёлемент " << key << " не найден" << endl;
    }
};
int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int tableSize, choice, vb;
    string k;
    cout << "¬ведите размер хеш-таблицы (1: 16 элементов, 2: 32 элемента, 3: 64 элемента, 4:128 элементов)" << endl;
    cin >> vb;
    switch (vb) {
    case 1: tableSize = 16; break;
    case 2: tableSize = 32; break;
    case 3: tableSize = 64; break;
    case 4: tableSize = 128; break;
    default:
        cout << "Ќеверный выбор" << endl;
        return 1;
    }
    HashTableOne hashTableOne(tableSize);
    HashTableTwo hashTableTwo(tableSize);
    int elementsToInsert = 0;
    switch (tableSize) {
    case 16: elementsToInsert = 7; break;
    case 32: elementsToInsert = 15; break;
    case 64: elementsToInsert = 31; break;
    case 128: elementsToInsert = 63; break;
    }
    for (int i = 1; i <= elementsToInsert; i++) {
        hashTableOne.insert("a" + to_string(i));
        hashTableTwo.insert("a" + to_string(i));
    }
    while (true) {
        cout << "\n1 - вывод хеш-таблицы\n";
        cout << "2 - добавление элемента\n";
        cout << "3 - удаление элемента\n";
        cout << "4 - поиск элемента\n";
        cout << "5 - вывод коллизий\n";
        cout << "0 - выход\n";
        cout << "—делайте выбор: ";
        cin >> choice;

        switch (choice) {
        case 0:
            return 0;
        case 1:
        {
            hashTableOne.printTable();
            cout << "\n---------------------\n";
            hashTableTwo.printTable();
            break;
        }
        case 2:
        {
            cout << "¬ведите элемент дл€ добавлени€: ";
            cin >> k;
            hashTableOne.insert(k);
            hashTableTwo.insert(k);
            break;
        }
        case 3:
        {
            cout << "¬ведите ключ дл€ удалени€: ";
            cin >> k;
            hashTableOne.deleteByKey(k);
            hashTableTwo.deleteByKey(k);
            break;
        }
        case 4:
        {
            cout << "¬ведите ключ дл€ поиска: ";
            cin >> k;
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            bool found1 = hashTableOne.search(k);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "¬рем€ поиска в первой таблице: прошло " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " наносекунд" << endl;
            chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
            bool found2 = hashTableTwo.search(k);
            chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
            cout << "¬рем€ поиска в первой таблице: прошло " << chrono::duration_cast<chrono::nanoseconds>(end1 - begin1).count() << " наносекунд" << endl;
            if (found1 && found2)
                cout << "Ёлемент найден в обоих таблицах: " << k << endl;
            else
                cout << "Ёлемент не найден в одной из таблиц" << endl;
            break;
        }
        case 5:
        {
            if (collisions.empty()) {
                cout << " оллизий нет\n";
            }
            else {
                cout << " оллизии:\n";
                for (auto el : collisions) {
                    cout << " люч: " << el.first << ", индекс: " << el.second << endl;
                }
            }
            break;
        }
        default:
        {
            cout << "Ќеверный выбор" << endl;
            break;
        }
        }
    }

    return 0;
}
