#include <iostream>
#include <windows.h>
// ���������� ���������� ��� �������� �����������
int sum1 = 0;
int sum2 = 0;
// �������, ����������� ��������
DWORD WINAPI CalculateSum(LPVOID param) {
    int start = (int)param;  // ��������� ��������

    // ������� ����� ����� � ���������
    for (int i = start; i < start + 5; ++i) {
        if (start == 1) {
            sum1 += i;  // ����� �� 1 �� 5
        }
        else {
            sum2 += i;  // ����� �� 6 �� 10
        }
    }

    return 0;
}
int main() {
    setlocale(LC_ALL, "ru");
    // �������� �������
    HANDLE hThread1 = CreateThread(NULL, 0, CalculateSum, (LPVOID)1, 0, NULL);  // ����� ��� ����� �� 1 �� 5
    HANDLE hThread2 = CreateThread(NULL, 0, CalculateSum, (LPVOID)6, 0, NULL);  // ����� ��� ����� �� 6 �� 10
    // �������� ���������� �������
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    // �������� ������������ �������
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    // ����� �����������
    std::cout << "����� �� 1 �� 5: " << sum1 << std::endl;
    std::cout << "����� �� 6 �� 10: " << sum2 << std::endl;
    std::cout << "����� �����: " << sum1 + sum2 << std::endl;
    return 0;
}
