#include "varparm.h"
using namespace Varparm;
int main() {
    setlocale(LC_ALL, "ru");
    cout << "Вызов функции ivarparm:\n";
    cout << "ivarparm1 = " << ivarparm(0) << endl;
    cout << "ivarparm2 = " << ivarparm(1, 5) << endl;
    cout << "ivarparm3 = " << ivarparm(2, 4, 6) << endl;
    cout << "ivarparm7 = " << ivarparm(7,6, 9, 12, 15, 18, 21,15);
    cout << "\nВызов функции svarparm:\n";
    cout << "svarparm1 = " << svarparm(0) << endl;
    cout << "svarparm2 = " << svarparm(1, 10) << endl;
    cout << "svarparm3 = " << svarparm(2, 4, 6) << endl;
    cout << "svarparm7 = " << svarparm(7, 12, 18, 24, 30, 36, 42,43);
    cout << "\nВызов функции fvarparm:\n";
    cout << "fvarparm1 = " << fvarparm(FLT_MAX) << endl;
    cout << "fvarparm2 = " << fvarparm(1, FLT_MAX) << endl;
    cout << "fvarparm3 = " << fvarparm(2, 4.5, FLT_MAX) << endl;
    cout << "fvarparm7 = " << fvarparm(7, 5.5, 10.5, 11.5, 12.5, 15.5,26.8, FLT_MAX);
    cout << "\nВызов функции dvarparm:\n";
    cout << "dvarparm1 = " << dvarparm(DBL_MAX) << endl;
    cout << "dvarparm2 = " << dvarparm(1, DBL_MAX) << endl;
    cout << "dvarparm3 = " << dvarparm(2, 5.6, DBL_MAX) << endl;
    cout << "dvarparm7 = " << dvarparm(7, 47.9, 102.9, 1.8, 8.9, 19.5,26.8, DBL_MAX);
    return 0;
}  