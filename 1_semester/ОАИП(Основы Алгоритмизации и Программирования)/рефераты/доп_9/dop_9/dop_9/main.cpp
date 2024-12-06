#include <iostream>
#include <string>
using namespace std;

// Функция для временных объектов
void process(string&& temp) {
    cout << "Обработан временный объект: " << temp << '\n';
}

// Функция для постоянных объектов
void process(const string& ref) {
    cout << "Обработана постоянная строка: " << ref << '\n';
}

int main() {
    setlocale(LC_ALL, "ru");
    string str = "Привет";

    process(str);              // Передается постоянная строка
    process("Временный объект"); // Передается временный объект

    return 0;
}
