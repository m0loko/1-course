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
    cout << "\nХеш-таблица букв:\n";
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].count > 0)
            cout << table[i].letter << ": " << table[i].count << endl;
    }
}

void find(HashEntry table[], char ch) {
    if (!isalpha(ch)) {
        cout << "Некорректный символ\n";
        return;
    }

    int index = hashFunction(ch);
    if (table[index].count > 0)
        cout << "Буква '" << table[index].letter << "' встречается " << table[index].count << " раз\n";
    else
        cout << "Буква '" << ch << "' не встречается во входной строке\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    HashEntry table[TABLE_SIZE] = {}; 
    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    for (char ch : input)
        insert(table, ch);
    print(table);
    char search;
    cout << "\nВведите букву для поиска: ";
    cin >> search;
    find(table, search);
    return 0;
}

