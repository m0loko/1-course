#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int A, B, n, p, q,m;
    char tmp[33];
    cout << "Введите целое число A: ";
    cin >> A;
    cout << "Введите целое число B: ";
    cin >> B;
    cout << "Сколько битов числа A нужно установить в 0? ";
    cin >> n;
    cout << "Введите позицию p в числе A, вправо от которой нужно установить в 0 биты: ";
    cin >> p;
    cout << "Сколько битов числа B нужно заменить? ";
    cin >> m;
    cout << "Введите позицию q в числе B, начиная с которой нужно заменить биты: ";
    cin >> q;
    _itoa_s(A, tmp, 2);
    cout << "Число A в двоичной системе: " << tmp << endl;
    _itoa_s(B, tmp, 2);
    cout << "Число B в двоичной системе: " << tmp << endl;
    // Создание маски для установки n битов в 0 влево от позиции p
    int maskA = ((1 << n) - 1) << (p - n);
    _itoa_s(maskA, tmp, 2);
    cout << "Маска A: " << tmp << endl;
    // Установка n битов в 0 в числе A
    A = A & ~maskA;
    _itoa_s(A, tmp, 2);
    cout << "Число A после установки битов в 0: " << tmp << endl;
    // Извлечение n битов из числа A
    int extractedBits = (A & maskA) >> p;
    _itoa_s(extractedBits, tmp, 2);
    cout << "Извлеченные биты из числа A: " << tmp << endl;
    // Создание маски для замены m битов в числе B начиная с позиции q
    int maskB = ((1 << m) - 1) << q;
    _itoa_s(maskB, tmp, 2);
    cout << "Маска B: " << tmp << endl;
    // Очистка m битов в числе B и замена их извлеченными битами
    B = (B & ~maskB) | (extractedBits << (q - 1));
    _itoa_s(B, tmp, 2);
    cout << "Число B после замены битов: " << tmp << endl;
    return 0;
}
