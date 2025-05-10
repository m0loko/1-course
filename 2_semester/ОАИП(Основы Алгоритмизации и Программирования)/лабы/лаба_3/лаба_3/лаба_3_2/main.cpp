#include <iostream>
#include <fstream>

using namespace std;

void toFile(const char* filename, const char* input) {
    ofstream fileOut(filename);
    fileOut << input;
    fileOut.close();
}

void result(const char* filename) {
    ifstream fileIn(filename);
    char ch;
    char word[100];
    int j = 0;
    bool found = false;

    cout << "Нечетные числа: ";

    while (fileIn.get(ch)) {
        if (ch != ' ' && ch != '\n') {
            word[j++] = ch;
        }
        else {
            if (j > 0) {
                word[j] = '\0';
                j = 0;
                if (isdigit(word[0])) {
                    int num = 0, i = 0;
                    while (word[i] != '\0') num = num * 10 + (word[i++] - '0');
                    if (num % 2 != 0) {
                        cout << num << " ";
                        found = true;
                    }
                }
            }
        }
    }

    if (j > 0) {
        word[j] = '\0';
        if (isdigit(word[0])) {
            int num = 0, i = 0;
            while (word[i] != '\0') num = num * 10 + (word[i++] - '0');
            if (num % 2 != 0) {
                cout << num << " ";
                found = true;
            }
        }
    }

    if (!found) cout << "отсутствуют";
    cout << endl;

    fileIn.close();
}

int main() {
    setlocale(LC_ALL, "ru");

    char input[1000];
    cout << "Введите строку (цифры и слова через пробел): ";
    cin.getline(input, 1000);

    const char* filename = "two.txt";
    toFile(filename, input);
    result(filename);

    return 0;
}