#include<iostream>
#include <thread>
#include <windows.h>
using namespace std;
void task1(int** F, int, int);
void task2(int** array, int);
int main() {
	setlocale(LC_ALL, "ru");
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
			int** F, d, p;
			cout << "Введите число строк матрицы (<=16) ";
			cin >> d;
			cout << "Введите чиcло столбцов (<=18) ";
			cin >> p;
			if (d > 16 || p > 18) {
				cout << "Ошибка: размеры матрицы превышают допустимые значения" << endl;
				return 1;
			}
			F = new int* [d];
			for (int i = 0; i < d; i++)
				F[i] = new int[p];
			for (int i = 0; i < d; i++)
				for (int j = 0; j < p; j++)
				{
					cout << "Введите A[" << i << "],[" << j << "]= ";
					cin >> F[i][j];
				}
			task1(F, d, p);
			for (int i = 0; i < d; i++) {
				delete[] F[i];
			}
			delete[] F;
			system("pause");
			system("cls"); 
			break;
		}
		case 2:
		{
			const int SIZE = 4;
			int** array = new int* [SIZE];
			for (int i = 0; i < SIZE; i++) {
				array[i] = new int[SIZE];
			}
			cout << "Введите элементы матрицы 4x4: \n";
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					cout << "Элемент [" << i << "][" << j << "]: ";
					cin >> array[i][j];
				}
			}
			task2(array, SIZE);
			for (int i = 0; i < SIZE; i++) {
				delete[] array[i];
			}
			delete[] array;
			system("pause");
			system("cls");
			break;
		}
		case 3:  break;
		}
	} while (choice != 3);

}
void task1(int** F, int d, int p) {
	cout << "\nИсходная матрица:" << endl;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < p; j++) {
			cout << F[i][j] << "\t";
		}
		cout << endl;
	}

	// замена элементов главной диагонали минимальными в строках
	for (int i = 0; i < d; i++) {
		int min_element = F[i][0];
		for (int j = 0; j < p; j++) {
			if (F[i][j] < min_element) {
				min_element = F[i][j];
			}
		}
	}

	cout << "\nИзменённая матрица:" << endl;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < p; j++) {
			cout << F[i][j] << "\t";
		}
		cout << endl;
	}
}
void task2(int** array,int SIZE)
{
	cout << "Матрица: \n";
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\nИндексы k, где k-я строка совпадает с k-м столбцом: ";
	bool found = false; // проверки совпадений
	for (int k = 0; k < SIZE; k++) {
		bool match = true; // проверка совпадения строки и столбца
		for (int i = 0; i < SIZE; i++) {
			if (array[k][i] != array[i][k]) {
				match = false;
				break;
			}
		}
		if (match) {
			cout << k << " ";
			found = true;
		}
	}

	if (!found) {
		cout << "Совпадений не найдено."<<endl;
	}


}