#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
#include <chrono>
using namespace std;
#ifdef max
#undef max
#endif

struct elem {
    int phone;
    string name;
    elem() : phone(0), name("") {}
    elem(int p, string n) : phone(p), name(n) {}
};

struct HashTable {
    elem* table;
    int size;
    int count;

    HashTable(int tableSize) {
        size = tableSize;
        count = 0;
        table = new elem[size];
    }

    int hashFunction(int key, int p = 0) {
        const double A = 0.6180339887;
        double product = key * A;
        double fractional_part = product - floor(product);
        int res = static_cast<int>(floor(size * fractional_part));
        return (res + p) % size;
    }

    bool insert(int phone, string name) {
        if (count >= size) {
            cout << "Внизу хранится null" << endl;
            return false;
        }

        int p = 0;
        int i = hashFunction(phone, p++);
        while (table[i].phone != 0) {
            if (p > size) {
                cout << "Внизу хранится null" << endl;
                return false;
            }
            cout << "Коллизия: ключ " << phone << " пробируется в слот " << i << endl;
            i = hashFunction(phone, p++);
        }

        table[i] = elem(phone, name);
        count++;
        if (p > 1) cout << "Ключ " << phone << " помещён в слот " << i << " после " << p - 1 << " коллизий" << endl;
        return true;
    }

    bool search(int phone, string& name) {
        int p = 0;
        int i = hashFunction(phone, p++);
        for (; p <= size; ++p) {
            if (table[i].phone == phone) {
                name = table[i].name;
                return true;
            }
            i = hashFunction(phone, p);
        }
        return false;
    }

    void deleteByKey(int phone) {
        int p = 0;
        int i = hashFunction(phone, p++);
        for (; p <= size; ++p) {
            if (table[i].phone == phone) {
                table[i] = elem();
                count--;
                cout << "Элемент с номером " << phone << " удалён" << endl;
                return;
            }
            i = hashFunction(phone, p);
        }
        cout << "Элемент с номером " << phone << " не найден" << endl;
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i].phone != 0) {
                cout << "[" << i << "]: (" << table[i].phone << ", " << table[i].name << ")" << endl;
            }
            else {
                cout << "[" << i << "]: null" << endl;
            }
        }
    }

    ~HashTable() {
        delete[] table;
    }
};

bool strCheck(string str) {
    for (unsigned char ch : str) {
        if (isalpha(ch)) continue;
        if (ch == ' ') continue;
        bool isCyrillic = (ch >= 0xC0 && ch <= 0xFF) || (ch == 0xA8) || (ch == 0xB8);
        if (!isCyrillic) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int tableSize, choice, vb;
    string temp;
    int phone;
    string name;

    cout << "Введите размер хеш-таблицы (1: 16 элементов, 2: 32 элемента, 3: 64 элемента, 4: 128 элементов): ";
    while (!(cin >> vb) || vb < 1 || vb > 4) {
        cout << "Неверный выбор! Введите 1–4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    switch (vb) {
    case 1: tableSize = 16; break;
    case 2: tableSize = 32; break;
    case 3: tableSize = 64; break;
    case 4: tableSize = 128; break;
    }

    HashTable hashTable(tableSize);
    cout << "\nНачальная таблица:\n";
    hashTable.printTable();

    while (true) {
        cout << "\n1 - вывод хеш-таблицы\n";
        cout << "2 - добавление элемента\n";
        cout << "3 - удаление элемента\n";
        cout << "4 - поиск элемента\n";
        cout << "0 - выход\n";
        cout << "> ";
        while (!(cin >> choice)) {
            cout << "Неверный выбор! Введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 0:
            return 0;
        case 1:
            hashTable.printTable();
            break;
        case 2:
            cout << "Введите ключ(номер телефона):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "Номер телефона не должен превышать 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }

            cout << "Введите значение(ФИО):" << endl;
            getline(cin, name, '\n');
            if (!strCheck(name)) {
                cout << "Неверный ввод ФИО!" << endl;
                break;
            }

            if (hashTable.insert(phone, name)) {
                cout << "Элемент добавлен!" << endl;
            }
            else {
                cout << "Таблица полна!" << endl;
            }
            break;
        case 3:
            cout << "Введите ключ(номер телефона):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "Номер телефона не должен превышать 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "Некорректный ввод!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }

            hashTable.deleteByKey(phone);
            break;
        case 4:
            cout << "Введите ключ(номер телефона):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "Номер телефона не должен превышать 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "Некорректный ввод!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "Некорректный ввод номера!" << endl;
                break;
            }

            {
                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                string foundName;
                bool found = hashTable.search(phone, foundName);
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "Прошло " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " мкс" << endl;
                if (found) {
                    cout << "Элемент найден: телефон = " << phone << ", ФИО = " << foundName << endl;
                }
                else {
                    cout << "Элемент не найден!" << endl;
                }
            }
            break;
        default:
            cout << "Некорректный ввод!" << endl;
            break;
        }
    }

    return 0;
}