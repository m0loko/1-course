#include <iostream>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    vector<double> a1 = {130.5,130,129.5,129,128.5,128.2,128,127,9,127.6};
    vector<double> a2 = {19.214,18.953,18.521,18.040,17.712,17.001,16.483,16.0229,15.537};
    for (int i = 0; i < 9; i++)
    {
        cout<<a1[i]/(a2[i]*1e6) << endl;
    }
    return 0;
}
