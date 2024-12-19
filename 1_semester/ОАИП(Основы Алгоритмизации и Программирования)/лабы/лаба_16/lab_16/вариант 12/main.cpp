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
		cout << "����� ������� ����� ��������" << endl;
		cout << "1 - ������ �������" << endl;
		cout << "2 - ������ �������" << endl;
		cout << "3 - �����" << endl;
		cin >> choice; 
		switch (choice)
		{
		case 1:
		{
			int** F, d, p;
			cout << "������� ����� ����� ������� (<=16) ";
			cin >> d;
			cout << "������� ��c�� �������� (<=18) ";
			cin >> p;
			if (d > 16 || p > 18) {
				cout << "������: ������� ������� ��������� ���������� ��������" << endl;
				return 1;
			}
			F = new int* [d];
			for (int i = 0; i < d; i++)
				F[i] = new int[p];
			for (int i = 0; i < d; i++)
				for (int j = 0; j < p; j++)
				{
					cout << "������� A[" << i << "],[" << j << "]= ";
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
			cout << "������� �������� ������� 4x4: \n";
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					cout << "������� [" << i << "][" << j << "]: ";
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
	cout << "\n�������� �������:" << endl;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < p; j++) {
			cout << F[i][j] << "\t";
		}
		cout << endl;
	}

	// ������ ��������� ������� ��������� ������������ � �������
	for (int i = 0; i < d; i++) {
		int min_element = F[i][0];
		for (int j = 0; j < p; j++) {
			if (F[i][j] < min_element) {
				min_element = F[i][j];
			}
		}
	}

	cout << "\n��������� �������:" << endl;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < p; j++) {
			cout << F[i][j] << "\t";
		}
		cout << endl;
	}
}
void task2(int** array,int SIZE)
{
	cout << "�������: \n";
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\n������� k, ��� k-� ������ ��������� � k-� ��������: ";
	bool found = false; // �������� ����������
	for (int k = 0; k < SIZE; k++) {
		bool match = true; // �������� ���������� ������ � �������
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
		cout << "���������� �� �������."<<endl;
	}


}