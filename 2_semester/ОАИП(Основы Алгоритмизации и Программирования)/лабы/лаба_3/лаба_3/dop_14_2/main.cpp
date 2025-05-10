#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool writeToFile(const string& text, const string& filename) {
    ofstream output_file(filename);
    if (output_file.is_open()) {
        output_file << text << endl;
        output_file.close();
        return true;
    }
    else {
        cout << "Ошибка открытия файла для записи" << endl;
        return false;
    }
}

string readFromFile(const string& filename) {
    ifstream input_file(filename);
    string read_string;
    if (input_file.is_open()) {
        getline(input_file, read_string);
        input_file.close();
    }
    else {
        cout << "Ошибка открытия файла для чтения!" << endl;
    }
    return read_string;
}

int main() {
    setlocale(LC_ALL, "ru");
    string input_string;
    cout << "Введите строку: ";
    getline(cin, input_string);
    if (writeToFile(input_string, "output.txt")) {
        cout << "Строка успешно записана в файл output.txt" << endl;
    }
    else {
        return 1; 
    }

    string read_string = readFromFile("output.txt");

    if (!read_string.empty()) {
        int k;
        cout << "Введите длину первой подстроки (k): ";
        cin >> k;

        if (k < 0 || k > read_string.length()) {
            cerr << "Некорректная длина k" << endl;
            return 1;
        }

        string substring1 = read_string.substr(0, k);
        string substring2 = read_string.substr(k);

        cout << "Первая подстрока (длина = )"<<k<<" : " << substring1 << endl;
        cout << "Вторая подстрока: " << substring2 << endl;
    }
    else {
        return 1;
    }

    return 0;
}