#include <iostream>
#include <windows.h>
// Глобальные переменные для хранения результатов
int sum1 = 0;
int sum2 = 0;
// Функция, исполняемая потоками
DWORD WINAPI CalculateSum(LPVOID param) {
    int start = (int)param;  // Начальное значение

    // Считаем сумму чисел в диапазоне
    for (int i = start; i < start + 5; ++i) {
        if (start == 1) {
            sum1 += i;  // Сумма от 1 до 5
        }
        else {
            sum2 += i;  // Сумма от 6 до 10
        }
    }

    return 0;
}
int main() {
    setlocale(LC_ALL, "ru");
    // Создание потоков
    HANDLE hThread1 = CreateThread(NULL, 0, CalculateSum, (LPVOID)1, 0, NULL);  // Поток для суммы от 1 до 5
    HANDLE hThread2 = CreateThread(NULL, 0, CalculateSum, (LPVOID)6, 0, NULL);  // Поток для суммы от 6 до 10
    // Ожидание завершения потоков
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    // Закрытие дескрипторов потоков
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    // Вывод результатов
    std::cout << "Сумма от 1 до 5: " << sum1 << std::endl;
    std::cout << "Сумма от 6 до 10: " << sum2 << std::endl;
    std::cout << "Общая сумма: " << sum1 + sum2 << std::endl;
    return 0;
}
