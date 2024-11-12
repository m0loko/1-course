#include<iostream>
#include<Windows.h>
using namespace std;
#define USA_WHEAT 1110000000000000ULL //ull показывает, что тип данных unsigned long long
#define RUSSIA_WHEAT 2088000000000000ULL 
#define BELARUS_WHEAT 54000000000000ULL

void wheat(string country, unsigned long long int wheat) {
    unsigned long long int sn = 1;
    for (int i = 1; i < 65; i++) {
        sn = sn << 1; // сдвиг влево на 1 бит, эквивалентно умножению на 2. сдалал с тем, что мы проходили на лекции т.к. это ускоряет вычисления на уровне процессора
        if (sn > wheat) {
            cout << "На " << i << " клетке шахматного поля закончится урожай пшеницы " << country << endl;
            break;
        }
    }
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    wheat("Соединённых Штатов", USA_WHEAT);
    wheat("России", RUSSIA_WHEAT);
    wheat("Беларуси", BELARUS_WHEAT);
    return 0;
}
