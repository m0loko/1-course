#include <iostream>

int main()
{
	setlocale(LC_ALL, "ru");
	//��������� ����� ������� � ������ ����� � �����������
	double americanmiligr = 49320000000000000, russianmiligr = 92800000000000000, belarusianmiligr = 8000000000000000, zernomiligr = 60, q = 2;
	int n;

	//������ ���������� ������ ��������� ����� ����� ������� ����� �������������� ���������� (1) ��� �������
	n = log2(americanmiligr / zernomiligr + 1) + 1;
	printf("����� ������� � ��� ���������� �� %d", n);
	printf(" ������\n");

	//(1) ��� ������
	n = log2(russianmiligr / zernomiligr + 1) + 1;
	printf("����� ������� � ������ ���������� �� %d", n);
	printf(" ������\n");

	// (1) ��� ��������
	n = log2(belarusianmiligr / zernomiligr + 1) + 1;
	printf("����� ������� � �������� ���������� �� %d", n);
	printf(" ������\n");
	printf("������, ������, ����������� ������ ����\n");
	printf("�����:)");

	return 0;
}
