#include <iostream>
#include <cctype>
#include<string>
using namespace std;

const int TABLE_SIZE = 30; 

struct HashEntry {
    char letter;
    int count;
};

int hashFunction(char ch) {
    return tolower(ch) - 'a'; 
}

void insert(HashEntry table[], char ch) {
    if (isalpha(ch)) {
        int index = hashFunction(ch);
        table[index].letter = tolower(ch);
        table[index].count++;
    }
}

void print(HashEntry table[]) {
    cout << "\n���-������� ����:\n";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].count > 0)
            cout << table[i].letter << ": " << table[i].count << endl;
    }
}

void find(HashEntry table[], char ch) {
    if (!isalpha(ch)) {
        cout << "������������ ������\n";
        return;
    }

    int index = hashFunction(ch);
    if (table[index].count > 0)
        cout << "����� '" << table[index].letter << "' ����������� " << table[index].count << " ���\n";
    else
        cout << "����� '" << ch << "' �� ����������� �� ������� ������\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    HashEntry table[TABLE_SIZE] = {}; 
    string input;
    cout << "������� ������: ";
    getline(cin, input);
    for (char ch : input)
        insert(table, ch);
    print(table);
    char search;
    cout << "\n������� ����� ��� ������: ";
    cin >> search;
    find(table, search);
    return 0;
}

