//#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "ru");
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	int target1 = 3;
	int num_items1 = count(v.begin(), v.end(), target1);
	cout << "число: " << target1 << " количество: " << num_items1 << '\n';
	int num_items3 = count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0; });
	cout << "количесвто элементов , кратных 3: " << num_items3 << "\n";

	cout << endl << "Лямбда, захват переменных" << endl;
	for (auto i : v)[i]() {if (i % 3 == 0) cout << i << " "; }();

	cout << endl << "Лямбда с параметрами" << endl;
	for (auto i : v)[](auto i){if (i % 3 == 0)cout << i << " "; }(i);

	cout << endl << "Лямбда без параметров" << endl;
	for (auto i : v)[i] {if (i % 3 == 0)cout << i << " "; }();

	//допы
	cout << "\n----------------------------\nВведите число: ";
	int a;
	cin >> a;
	[](int num) -> bool {
		if (num > 0)
			cout << "Положительное\n";
		else if (num < 0)
			cout << "Отрицательное\n";
		return num > 0;
		}(a);
	[](string a, string b) {
		cout<< a + b<<endl;
		}("hello ", "goodbye");
	[](string a, string b) {
		if (a.length()>b.length())
		{
			cout << a << endl;
		}
		else
		{
			cout << b << endl;
		}
		}("aa", "bbb");

}