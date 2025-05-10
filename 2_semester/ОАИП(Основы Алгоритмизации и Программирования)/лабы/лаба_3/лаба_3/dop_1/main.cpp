#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool findTwoWords(const string& line) {
    size_t start = 0;
    size_t end = line.find(' ');
    vector<string> words;

    while (end != string::npos) {
        string word = line.substr(start, end - start);
        if (!word.empty()) { 
            for (string w : words) {
                if (w == word) {
                    return true;
                }
            }
            words.push_back(word);
        }
        start = end + 1;
        end = line.find(' ', start);
    }
    string lastWord = line.substr(start);
    if (!lastWord.empty()) { 
        for (string& w : words) {
            if (w == lastWord) {
                return true;
            }
        }
    }
    return false;
}

int countA(string& word) {
    int count = 0;
    for (char c : word) {
        if (c == 'a' || c == 'A') {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "ru");
    ifstream inputFile("FILE1.txt");
    ofstream outputFile("FILE2.txt");

    if (!inputFile.is_open()) {
        cout << "Ошибка открытия файла FILE1.txt" << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cout << "Ошибка открытия файла FILE2.txt" << endl;
        return 1;
    }

    string line;
    int maxAIndex = -1;
    int maxACount = -1;
    int lineCount = 0;
    int globalWordIndex = 0;

    cout << "Строки с одинаковыми словами:" << endl;

    while (getline(inputFile, line)) {
        bool hasDuplicates = findTwoWords(line);
        if (hasDuplicates) {
            outputFile << line << endl;
            cout << line << endl;
            lineCount++;
        }

        size_t start = 0;
        size_t end = line.find(' ');
        while (end != string::npos) {
            string word = line.substr(start, end - start);
            if (!word.empty()) {
                int aCount = countA(word);
                if (aCount > maxACount) {
                    maxACount = aCount;
                    maxAIndex = globalWordIndex;
                }
                globalWordIndex++;
            }
            start = end + 1;
            end = line.find(' ', start);
        }
        string lastWord = line.substr(start);
        if (!lastWord.empty()) { 
            int aCount = countA(lastWord);
            if (aCount > maxACount) {
                maxACount = aCount;
                maxAIndex = globalWordIndex;
            }
            globalWordIndex++;
        }
    }

    inputFile.close();
    outputFile.close();

    if (maxAIndex != -1) {
        cout << "\nНомер слова с наибольшим количеством букв 'a' во ВСЕМ ФАЙЛЕ: " << maxAIndex + 1 << endl;
    }
    else {
        cout << "\nВ файле нет слов с буквой 'a'" << endl;
    }

    return 0;
}