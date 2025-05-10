#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeToFile(const string& filename, const string& input) {
    ofstream fileOut(filename);
    if (!fileOut) {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }
    fileOut << input;
    fileOut.close();
}

string removeZero(const string& str) {
    size_t nonZeroPos = str.find_first_not_of('0');
    return (nonZeroPos == string::npos) ? "0" : str.substr(nonZeroPos);
}

string findShort(const string& filename) {
    ifstream fileIn(filename);
    if (!fileIn) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return "";
    }

    string line, shortestGroup;
    int minLength = 1000000;

    while (getline(fileIn, line)) {
        string currentGroup;
        for (size_t i = 0; i <= line.length(); i++) {
            if (i < line.length() && isdigit(line[i])) {
                currentGroup += line[i];
            }
            else if (!currentGroup.empty()) {
                string cleanedWord = removeZero(currentGroup);
                if (cleanedWord.length() < minLength) {
                    minLength = cleanedWord.length();
                    shortestGroup = cleanedWord;
                }
                currentGroup.clear();
            }
        }
    }

    fileIn.close();
    return shortestGroup;
}

int main() {
    setlocale(LC_ALL, "ru");
    string input;
    cout << "Введите строку (группы цифр и нулей через пробел): ";
    getline(cin, input);
    string filename = "numbers.txt";
    writeToFile(filename, input);   
    string shortest = findShort(filename);
    if (!shortest.empty()) {
        cout << "Самая короткая группа: " << shortest << endl;
    }
    else {
        cout << "Файл пуст или нет данных" << endl;
    }

    return 0;
}
