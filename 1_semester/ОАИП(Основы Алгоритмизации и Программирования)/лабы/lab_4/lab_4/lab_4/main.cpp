#include <iostream>
#include <iomanip>
int main() {
    setlocale(LC_ALL, "Russian");
    using namespace std;
    double speeds[5];
    double totalTime = 0.0;
    double totalDistance = 0.0;
    const double length = 1.0;
    for (int i = 0; i < 5; i++) {
        cout << "¬ведите среднюю скорость на участке " << (i + 1) << " (км/ч): ";
        cin >> speeds[i];
        totalTime += (length / speeds[i]);
    }
    totalDistance = 5 * length;
    double srSpeed = totalDistance / totalTime;
    cout << "—редн€€ скорость на всем пути: " << srSpeed << " км/ч" << endl;

    return 0;
}
