#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    ifstream first("FILE1.txt");
    if (!first.is_open()) {
        cout << "Ошибка открытия файла FILE1" << endl;
        return 1;
    }
    ofstream second("FILE2.txt");
    if (!second.is_open()) {
        cout << "Ошибка открытия файла FILE2" << endl;
        first.close();
        return 1;
    }

    string line;
    while (getline(first, line)) {  
        if (!line.empty() && line[0] == 'A') { 
            second << line << endl; 
        }
    }

    first.close();
    second.close(); 

    ifstream result("FILE2.txt");
    if (!result.is_open()) {
        cout << "Ошибка открытия файла FILE2" << endl;
        return 1;
    }

    int wordCount = 0;
    string word;
    while (result >> word) { 
        wordCount++;
    }

    result.close();
    cout << "Количество слов в FILE2: " << wordCount << endl;

    return 0;
}
