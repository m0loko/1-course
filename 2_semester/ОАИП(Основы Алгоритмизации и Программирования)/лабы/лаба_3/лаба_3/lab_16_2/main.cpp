#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void toFile(const string& filename, const string& input) {
    ofstream fileOut(filename);
    if (fileOut.is_open()) {
        fileOut << input;
        fileOut.close();
    }
    else {
        cout << "������ �������� ����� ��� ������" << endl;
    }
}

bool isNumber(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch)) return false;
    }
    return !str.empty();
}

void result(const string& filename) {
    ifstream fileIn(filename);
    if (!fileIn.is_open()) {
        cout << "������ �������� ����� ��� ������" << endl;
        return;
    }

    string line, word;
    bool found = false;
    cout << "׸���� �����: ";

    while (fileIn >> word) {
        if (isNumber(word)) {
            int num = stoi(word);
            if (num % 2 == 0) {
                cout << num << " ";
                found = true;
            }
        }
    }

    if (!found) cout << "�����������";
    cout << endl;

    fileIn.close();
}

int main() {
    setlocale(LC_ALL, "ru");
    string input;
    cout << "������� ������ (����� � ����� ����� ������): ";
    getline(cin, input);
    const string filename = "two.txt";
    toFile(filename, input);
    result(filename);
    return 0;
}
