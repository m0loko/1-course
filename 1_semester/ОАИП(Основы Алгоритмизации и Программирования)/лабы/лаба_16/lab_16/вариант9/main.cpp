	#include<iostream>
	#include <thread>
	#include <windows.h>
	#include<vector>
	#include<string>
	using namespace std;
	void task1(int** F, int,int,int);
	void task2(vector<string>&);
	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		int choice;
		do
		{
			cout << "Какое задание нужно показать" << endl;
			cout << "1 - первое задание" << endl;
			cout << "2 - второе задание" << endl;
			cout << "3 - выход" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				int** F, n, m, number;
				cout << "Введите число строк матрицы ";
				cin >> n;
				cout << "Введите чиcло столбцов ";
				cin >> m;
				F = new int* [n];
				for (int i = 0; i < n; i++)//выделение памяти
					F[i] = new int[m];
				for (int i = 0; i < n; i++)//заполнение 
					for (int j = 0; j < m; j++)
					{
						cout << "Введите F[" << i << "],[" << j << "]= ";
						cin >> F[i][j];
					}
				cout << "Введите число number: "; cin >> number;
				task1(F, n, m, number);
				for (int i = 0; i < n; i++) {
					delete[] F[i];
				}
				delete[] F;
				system("pause");
				system("cls");
				break;
			}
			case 2:
			{
				vector<string> stroka;
				string input;
				cin.ignore();
				cout << "Введите строку:\n";
				while (true) {
					getline(cin, input);
					if (input.empty()) break;  // Завершаем ввод по пустой строке
					stroka.push_back(input);
				}
				task2(stroka);
				system("pause");
				system("cls");
				break;
			}
			case 3:  break;
			}
		} while (choice != 3);

	}
	void task1(int** F,int n,int m, int number) {
		bool e_numer = false, e_diag = false;//проверка есть ли number вообще и на главную диагональ
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (F[i][j] == number) {
					e_numer = true;
					break;
				}
			}
		}
		if (e_numer)
		{
			cout << "Число " << number << " есть в массиве\n";
			for (int i = 0; i < n; i++)
			{
				if (F[i][i] == number) {
					e_diag = true;
					break;
				}
			}
			if (e_diag)
			{
				cout << "Число " << number << " находится на главной диагонали\n";
			}
			else
			{
				cout << "Число " << number << " не находится на главной диагонали\n";
			}
		}
		else
		{
			cout << "Числа " << number << " нет в массиве\n";
		}
	}
	void task2(vector<string>& stroka)
	{
		cout << "Строки начинающиеся с буквы b:\n";
		for (string& str : stroka)
		{
			if (!str.empty() && str[0] == 'b')
			{
				cout << str << endl;
			}
		}
	}