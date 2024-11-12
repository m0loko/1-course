#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int ch, random;
    std::cin >> random; // Ввод сдвига для дешифратора

    while ((ch = getchar()) != EOF) {
        ch = ch - random;  // Расшифровываем символ

        // Ограничиваем результат в пределах от 32 до 255
        if (ch > 255) {
            ch -= 256;  // Если выходит за 255, то возвращаем в диапазон
        }
        if (ch < 32) {
            ch += 32;  // Если меньше 32, то поднимаем до 32
        }

        putchar(ch);  // Выводим расшифрованный символ
    }

    return 0;
}
