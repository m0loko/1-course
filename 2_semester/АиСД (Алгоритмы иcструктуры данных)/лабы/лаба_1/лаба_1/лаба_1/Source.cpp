#include <iostream>
#include <chrono>
using namespace std;
unsigned long long int getRec( long long a){
	if (a==0)
	{
		return a;
	}
	if (a==1)
	{
		return a;
	}
	return getRec(a - 1) + getRec(a - 2);
}
unsigned long long int getCycle( long long a) {
	if (a == 0) return 0;	
	if (a == 1) return 1;

	int fib = 1, num1 = 0, num2 = 1;
	for (int i = 2; i <= a; i++) { 
		fib = num1 + num2;
		num1 = num2;
		num2 = fib;
	}
	return fib;
}

int main() {
	setlocale(LC_ALL, "ru");
	long long int a;
	cout << "������� �����: "; cin >> a;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	cout << "������: " << getCycle(a)<<endl;
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << "�� ����� YY ������ ZZ ����������� = " << chrono::duration_cast<chrono::minutes>(end - begin).count() << " ����� \t" << chrono::duration_cast<chrono::seconds>(end - begin).count() << " ������\t" << chrono::duration_cast<chrono::microseconds>(end - begin).count()<<" �����������"<<endl;
	chrono::steady_clock::time_point beginTwo = chrono::steady_clock::now();
	cout << "���������: " << getRec(a)<<endl;
	chrono::steady_clock::time_point endTwo = chrono::steady_clock::now();
	cout << "�� ����� YY ������ ZZ ����������� = " << chrono::duration_cast<chrono::minutes>(endTwo - beginTwo).count() << " ����� \t" << chrono::duration_cast<chrono::seconds>(endTwo - beginTwo).count() << " ������\t" << chrono::duration_cast<chrono::microseconds>(endTwo - beginTwo).count() << " �����������" << endl;
	return 0;
}
