#include<iostream>
usding namespace std;
void main()
{
	setlocale(LC_ALL, "ru");
	float a, sum = 0; int i;
	const int size = 4;
	for  i = 0; i < size; i++)
	{
		cout << "Введите а" << i << endl;
		cin >> a;
		sum = sum + a;
	}
	cout << "Ответ " << sum << endl;
}