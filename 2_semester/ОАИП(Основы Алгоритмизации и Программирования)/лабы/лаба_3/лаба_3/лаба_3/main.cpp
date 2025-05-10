#include <iostream>
#include <fstream>
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
    char firstWord[100];  
    first >> firstWord;  
    char buffer[1000]; 
    first.getline(buffer, 1000); 
    while (first.getline(buffer, 1000)) {
        char word[100];  
        int i = 0, j = 0;
        bool found = false;

        while (buffer[i] != '\0') {
            if ((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') ||
                (buffer[i] >= 'а' && buffer[i] <= 'я') || (buffer[i] >= 'А' && buffer[i] <= 'Я')) {
                word[j++] = buffer[i]; 
            }
            else {
                if (j > 0) {  
                    word[j] = '\0';  
                    j = 0;

                    int k = 0;
                    bool isEqual = true;
                    while (firstWord[k] != '\0' && word[k] != '\0') {
                        if (firstWord[k] != word[k]) {
                            isEqual = false;
                            break;
                        }
                        k++;
                    }
                    if (firstWord[k] != '\0' || word[k] != '\0') {
                        isEqual = false;
                    }

                    if (isEqual) {
                        found = true;
                    }
                }
            }
            i++;
        }

        if (j > 0) {  
            word[j] = '\0';
            int k = 0;
            bool isEqual = true;
            while (firstWord[k] != '\0' && word[k] != '\0') {
                if (firstWord[k] != word[k]) {
                    isEqual = false;
                    break;
                }
                k++;
            }
            if (firstWord[k] != '\0' || word[k] != '\0') {
                isEqual = false;
            }

            if (isEqual) {
                found = true;
            }
        }

        if (found) {
            second << buffer << endl;
        }
    }

    first.close();
    second.close();

    ifstream secondRead("FILE2.txt");
    if (!secondRead.is_open()) {
        cout << "Ошибка открытия файла FILE2" << endl;
        return 1;
    }

    int letterCount = 0;
    while (secondRead.getline(buffer, 1000)) {
        int i = 0;
        while (buffer[i] != '\0') {
            if ((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') ||
                (buffer[i] >= 'а' && buffer[i] <= 'я') || (buffer[i] >= 'А' && buffer[i] <= 'Я')) {
                letterCount++;
            }
            i++;
        }
    }

    secondRead.close();
    cout << "Количество букв в FILE2: " << letterCount << endl;

    return 0;
}
