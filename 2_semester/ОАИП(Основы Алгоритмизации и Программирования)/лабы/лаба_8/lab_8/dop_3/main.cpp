#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
using namespace std;

struct Node {
    char info;
    Node* next;
};

struct Queue {
    Node* begin;
    Node* end;

    Queue() {
        begin = end = nullptr;
    }

    bool isEmpty() {
        return begin == nullptr;
    }

    void dobavl(char ch) {
        Node* newNode = new Node{ ch, nullptr };
        if (isEmpty()) {
            begin = end = newNode;
        }
        else {
            end->next = newNode;
            end = newNode;
        }
    }

    char del() {
        if (isEmpty()) return '\0';
        Node* temp = begin;
        char value = temp->info;
        begin = begin->next;
        delete temp;
        if (begin == nullptr) end = nullptr;
        return value;
    }
};

void workFiile(const string& inputFile, const string& outputFile) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);

    if (!fin || !fout) {
        cerr << "Ошибка открытия файла" << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        Queue letters;
        Queue digits;  

        for (char ch : line) {
            if (isdigit(ch)) {
                digits.dobavl(ch);
            }
            else {
                letters.dobavl(ch);
            }
        }

        while (!letters.isEmpty()) {
            fout << letters.del();
        }
        while (!digits.isEmpty()) {
            fout << digits.del();
        }

        fout << endl;
    }

    fin.close();
    fout.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    workFiile("f.txt", "g.txt");

    cout << "Dcё. Результат записан в g.txt" << endl;
    return 0;
}
