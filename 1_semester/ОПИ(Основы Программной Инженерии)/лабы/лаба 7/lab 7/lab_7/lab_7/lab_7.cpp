#include <iostream>
#include <vector>

using namespace std;

// Функция для определения количества байт в UTF-8
int determineByteLength(int codePoint) {
    if (codePoint <= 0x7F) {
        return 1;
    }
    else if (codePoint <= 0x7FF) {
        return 2;
    }
    else if (codePoint <= 0xFFFF) {
        return 3;
    }
    else if (codePoint <= 0x10FFFF) {
        return 4;
    }
    else {
        return 0; // Недопустимое значение
    }
}

// Функция кодирования символа в UTF-8
vector<unsigned char> encodeUTF8(int codePoint) {
    int byteLength = determineByteLength(codePoint);
    vector<unsigned char> utf8Bytes(byteLength);

    switch (byteLength) {
    case 1:
        utf8Bytes[0] = static_cast<unsigned char>(codePoint);
        break;
    case 2:
        utf8Bytes[0] = static_cast<unsigned char>(0xC0 | (codePoint >> 6));
        utf8Bytes[1] = static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
        break;
    case 3:
        utf8Bytes[0] = static_cast<unsigned char>(0xE0 | (codePoint >> 12));
        utf8Bytes[1] = static_cast<unsigned char>(0x80 | ((codePoint >> 6) & 0x3F));
        utf8Bytes[2] = static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
        break;
    case 4:
        utf8Bytes[0] = static_cast<unsigned char>(0xF0 | (codePoint >> 18));
        utf8Bytes[1] = static_cast<unsigned char>(0x80 | ((codePoint >> 12) & 0x3F));
        utf8Bytes[2] = static_cast<unsigned char>(0x80 | ((codePoint >> 6) & 0x3F));
        utf8Bytes[3] = static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
        break;
    default:
        cout << "Неправильный код символа." << endl;
        break;
    }
    return utf8Bytes;
}

// Функция вывода результата в UTF-8
void outputResult(const vector<unsigned char>& utf8Bytes) {
    cout << "UTF-8 кодировка: ";
    for (unsigned char byte : utf8Bytes) {
        printf("%02X ", byte);
    }
    cout << endl;
}

// Основная функция
int main() {
    int codePoint;

    cout << "Введите код символа Юникода в формате 0x...: ";
    cin >> hex >> codePoint;

    int byteLength = determineByteLength(codePoint);
    if (byteLength == 0) {
        cout << "Неверный код символа." << endl;
        return 1;
    }

    vector<unsigned char> utf8Bytes = encodeUTF8(codePoint);
    outputResult(utf8Bytes);

    return 0;
}
