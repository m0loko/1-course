#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand((unsigned)time(NULL));

    int ch, random = rand() % 10 + 1; // Генерация случайного сдвига
    std::cout <<random<<std::endl; // вывод сдвига

    while ((ch = getchar()) != EOF) {
        ch = ch + random;

        // Ограничиваем результат в пределах от 32 до 255
        if (ch > 255) {
            ch -= 256;  // Если выходит за 255, то возвращаем в диапазон
        }
        if (ch < 32) {
            ch += 32;  // Если меньше 32, то поднимаем до 32 (непечатаемые символы)
        }

        putchar(ch);  // Выводим зашифрованный символ
    }

    return 0;
}
