#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
#include <chrono>
#include <list>
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
    list<elem>* table;
    int size;
    int count;

    HashTable(int tableSize) {
        size = tableSize;
        count = 0;
        table = new list<elem>[size];
    }

    int hashFunction(int key) {
        const double A = 0.6180339887;
        double product = key * A;
        double fractional_part = product - floor(product);
        int res = static_cast<int>(floor(size * fractional_part));
        return res % size;
    }

    bool insert(int phone, string name) {
        int i = hashFunction(phone);
        if (!table[i].empty()) {
            cout << "��������: ���� " << phone << " ����������� � ������� ����� " << i << endl;
        }
        table[i].push_back(elem(phone, name));
        count++;
        return true;
    }

    bool search(int phone, string& name) {
        int i = hashFunction(phone);
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (it->phone == phone) {
                name = it->name;
                return true;
            }
        }
        return false;
    }

    void deleteByKey(int phone) {
        int i = hashFunction(phone);
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (it->phone == phone) {
                table[i].erase(it);
                count--;
                cout << "������� � ������� " << phone << " �����" << endl;
                return;
            }
        }
        cout << "������� � ������� " << phone << " �� ������" << endl;
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i].empty()) {
                cout << "[" << i << "]: null" << endl;
            }
            else {
                cout << "[" << i << "]: ";
                for (auto& e : table[i]) {
                    cout << "(" << e.phone << ", " << e.name << ") ";
                }
                cout << endl;
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

    cout << "������� ������ ���-������� (1: 16 ���������, 2: 32 ��������, 3: 64 ��������, 4: 128 ���������): ";
    while (!(cin >> vb) || vb < 1 || vb > 4) {
        cout << "�������� �����! ������� 1�4: ";
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
    cout << "\n��������� �������:\n";
    hashTable.printTable();

    while (true) {
        cout << "\n1 - ����� ���-�������\n";
        cout << "2 - ���������� ��������\n";
        cout << "3 - �������� ��������\n";
        cout << "4 - ����� ��������\n";
        cout << "0 - �����\n";
        cout << "> ";
        while (!(cin >> choice)) {
            cout << "�������� �����! ������� �����: ";
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
            cout << "������� ����(����� ��������):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "������������ ���� ������!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "����� �������� �� ������ ��������� 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "������������ ���� ������!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "������������ ���� ������!" << endl;
                break;
            }

            cout << "������� ��������(���):" << endl;
            getline(cin, name, '\n');
            if (!strCheck(name)) {
                cout << "�������� ���� ���!" << endl;
                break;
            }

            if (hashTable.insert(phone, name)) {
                cout << "������� ��������!" << endl;
            }
            else {
                cout << "������� �����!" << endl;
            }
            break;
        case 3:
            cout << "������� ����(����� ��������):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "������������ ���� ������!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "����� �������� �� ������ ��������� 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "������������ ����!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "������������ ���� ������!" << endl;
                break;
            }

            hashTable.deleteByKey(phone);
            break;
        case 4:
            cout << "������� ����(����� ��������):" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, temp, '\n');
            if (temp.size() > 5) {
                cout << "������������ ���� ������!" << endl;
                break;
            }
            try {
                phone = stoi(temp);
                if (phone > 32767) {
                    cout << "����� �������� �� ������ ��������� 32767!" << endl;
                    break;
                }
            }
            catch (...) {
                cout << "������������ ����!" << endl;
                break;
            }
            if (phone <= 0) {
                cout << "������������ ���� ������!" << endl;
                break;
            }

            {
                chrono::steady_clock::time_point begin = chrono::steady_clock::now();
                string foundName;
                bool found = hashTable.search(phone, foundName);
                chrono::steady_clock::time_point end = chrono::steady_clock::now();
                cout << "������ " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " ���" << endl;
                if (found) {
                    cout << "������� ������: ������� = " << phone << ", ��� = " << foundName << endl;
                }
                else {
                    cout << "������� �� ������!" << endl;
                }
            }
            break;
        default:
            cout << "������������ ����!" << endl;
            break;
        }
    }

    return 0;
}