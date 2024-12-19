#include<iostream>
#include <thread>
#include <windows.h>
#include<string>
using namespace std;

void task1(float* A, int, int);
void task2(string &str);

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
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			float* A, C;
			int i, n;

			printf("Input size of array, n < 30 \n");
			cin >> n; 
			A = new float[n];
			for (i = 0; i < n; i++)
			{
				printf("Input element [%d]\n", i + 1);
				cin >> A[i];  
			}

			printf("Input C: ");
			cin >> C; 
			task1(A, n, C);
			delete[] A;
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			string str;
			cout << "������� ������: ";
			getline(cin, str);
			task2(str);
			system("pause");
			system("cls");
			break;
		}
		case 3:  break;
		}
	} while (choice != 3);

}

void task1(float* A, int n, int C) {
	float max = fabs(*A), sum = 0, prz = 1;
	int count = 0, count_C = 0;
	for (int i = 0; i < n; i++)
	{
		if (fabs(*(A + i)) > max)
		{
			max = fabs(*(A + i));
			count = i;
		}
		if (*(A + i) > C)
		{
			count_C++;
		}
	}
	for (int i = count + 1; i < n; i++) {
		prz *= A[i];
	}


	cout << "\n����������:" << endl;
	cout << "������������ ������� �� ������: " << max << endl;
	cout << "������������ ��������� ����� �������������: " << prz << endl;
	cout << "���������� ��������� ������ " << C << ": " << count_C << endl;
}

void task2(string &str)
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			break; 
		}

		
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i]>='�' && str[i]<='�' ) || (str[i]=='�')) {
			str[i] -= 32; 
		}
	}
	cout << "\n��������� ������: " << str << endl;
}
