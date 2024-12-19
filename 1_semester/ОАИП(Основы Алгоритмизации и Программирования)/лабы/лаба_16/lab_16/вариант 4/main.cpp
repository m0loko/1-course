#include<iostream>
#include <thread>
#include <windows.h>
#include<vector>
#include<string>
using namespace std;
void task1(int** &A, int** &number, int);
void task2(string &);
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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
			int** A, **result, n;
			cout << "������� ����� ����� � �������� �������(��� ����������) ";
			cin >> n;
			A = new int* [n];
			result = new int* [n];
			for (int i = 0; i < n; i++) {
				A[i] = new int[n];
				result[i] = new int[n];
			}
			for (int i = 0; i < n; i++) 
				for (int j = 0; j < n; j++)
				{
					cout << "������� A[" << i << "],[" << j << "]= ";
					cin >> A[i][j];
				}
			task1(A, result, n);
			for (int i = 0; i < n; i++) {
				delete[] A[i];
				delete[] result[i];
			}
			delete[] A;
			delete[] result;
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			string input;
			cout << "������� ������: ";
			cin.ignore();
			getline(cin, input);
			task2(input);
			system("pause");
			system("cls");
			break;
		}
		case 3:  break;
		}
	} while (choice != 3);

}
void task1(int** &A, int** &result,int n) {
	cout << "�������� �������:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0)
			{
				result[i][j] = A[i][j] - A[n - 1][j];
			}
			else
			{
				result[i][j] = A[i][j] - A[i - 1][j];
			}
		}
	}
	cout << "����� �������:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
}
void task2(string &input)
{
	int sum = 0;
	string temp = "";
	for (char &ch : input)
	{
		if (static_cast<int>(ch) >= 48 && static_cast<int>(ch) <= 57)
		{
			temp += ch;
		}
		else
		{
			if (!temp.empty())
			{
				sum += stoi(temp);
				temp = "";
			}
		}
	}
	// �������� ��� ���������� ����� �������
	if (!temp.empty()) {
		sum += stoi(temp);
	}
	cout << "�����=" << sum<<endl;

}