//#include <iostream>
//using namespace std;
//
//int main() {
//    setlocale(LC_ALL, "RU");
//
//    int n;
//    double p, totalyear = 0;
//    cout << "¬ведите, сколько лет фирма закупала оборудование: ";
//    cin >> n;
//    cout << "¬ведите, на сколько % оборудование уцениваетс€: ";
//    cin >> p;
//    for (int i = 1; i <= n; i++) {
//        double year;
//        cout << "¬ведите стоимость за " << i << " год: ";
//        cin >> year;
//        totalyear *= (1 - p / 100);
//        totalyear += year;
//    }
//    cout << "ќбща€ стоимость накопленного оборудовани€ за " << n << " лет: " << totalyear / 2 << " рублей." << endl;
//    return 0;
//}
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "Russian");
    float b = 0.5, m = 8, a = 20, y, z, j = 2;
    while (j <= 3)
    {

        y = (m - b) / (sin(a) - exp(a));
        z = 3 * y + sqrt(a - 4 * j * b);
        cout << "y = " << y << "\t" << "z = " << z << endl;
        j += 0.5;
    }
    return 0;
}
