#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int ch, random;
    std::cin >> random; // ���� ������ ��� �����������

    while ((ch = getchar()) != EOF) {
        ch = ch - random;  // �������������� ������

        // ������������ ��������� � �������� �� 32 �� 255
        if (ch > 255) {
            ch -= 256;  // ���� ������� �� 255, �� ���������� � ��������
        }
        if (ch < 32) {
            ch += 32;  // ���� ������ 32, �� ��������� �� 32
        }

        putchar(ch);  // ������� �������������� ������
    }

    return 0;
}
