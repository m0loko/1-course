#include <iostream>
#include <fstream>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
	char name[NAME_SIZE];
	char city[CITY_SIZE];
	Address* next;
	Address* prev;
};
//----------------------------------------------------------- просто поле для меню
int menu(void)
{
	char s[80];  int c;
	cout << endl;
	cout << "1. Ввод имени" << endl;
	cout << "2. Удаление имени" << endl;
	cout << "3. Вывод на экран" << endl;
	cout << "4. Поиск" << endl;
	cout << "5. Удаление элемента по имени" << endl;
	cout << "6. Проверить пуст ли список" << endl;
	cout << "7. Выход" << endl;
	cout << endl;
	do
	{
		cout << "Ваш выбор: ";
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);
	} while (c < 0 || c > 7);
	return c;
}
//-----------------------------------------------------------
void insert(Address* e, Address** phead, Address** plast) //Добавление в конец списка
{
	Address* p = *plast;
	if (*plast == NULL)
	{
		e->next = NULL;
		e->prev = NULL;
		*plast = e;
		*phead = e;
		return;
	}
	else
	{
		p->next = e;
		e->next = NULL;
		e->prev = p;
		*plast = e;
	}
}
//-----------------------------------------------------------
Address* setElement()      // Создание элемента и ввод его значений с клавиатуры 
{
	Address* temp = new  Address();
	if (!temp)
	{
		cerr << "Ошибка выделения памяти памяти";
		return NULL;
	}
	cout << "Введите имя: ";
	cin.getline(temp->name, NAME_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "Введите город: ";
	cin.getline(temp->city, CITY_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}
//-----------------------------------------------------------
void outputList(Address** phead, Address** plast)      //Вывод списка на экран
{
	Address* t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}
//-----------------------------------------------------------
void find(char name[NAME_SIZE], Address** phead)    // Поиск имени в списке
{
	Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name)) break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
		cout << t->name << ' ' << t->city << endl;
}
//-----------------------------------------------------------
void delet(char name[NAME_SIZE], Address** phead, Address** plast)  // Удаление имени
{
	struct Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name))  break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)
				(*phead)->prev = NULL;
			else
				*plast = NULL;
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
				t->next->prev = t->prev;
			else
				*plast = t->prev;
		}
		delete t;
		cout << "Элемент удален" << endl;
	}
}
//-----------------------------------------------------------
void deleteX(char x[NAME_SIZE], Address** phead, Address** plast) {
	Address* t = *phead;
	while (t) {
		if (!strcmp(x, t->name)) {
			delet(x, phead, plast);  
			return;
		}
		t = t->next;
	}
	cerr << "Элемент " << x << " не найден\n";
}
//-----------------------------------------------------------
bool returnN(Address* phead, Address* plast) {
	if (phead == nullptr && plast == nullptr) {
		cout << "Список пуст\n";
		return true;
	}
	else {
		cout << "Список не пуст\n";
		return false;
	}
}
//-----------------------------------------------------------
int countX(const char* targetName, Address* phead) {
	int count = 0;
	Address* current = phead;

	while (current != nullptr) {
		if (strcmp(current->name, targetName) == 0) {
			count++;
		}
		current = current->next;
	}

	return count;
}
//-----------------------------------------------------------

int main(void)
{
	setlocale(LC_ALL, "Rus");
	Address* head = NULL;
	Address* last = NULL;
	while (true)
	{
		switch (menu())
		{
		case 1:
		{
			insert(setElement(), &head, &last);
			break;
		}
		case 2: {
			char dname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			delet(dname, &head, &last);
			break;
		}
		case 3:
		{
			outputList(&head, &last);
			break;
		}
		case 4: {
			char fname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
			break;
		}
		case 5: {
			char x[NAME_SIZE];
			cout << "Введите элемент для удаления: ";
			cin.getline(x, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.clear();
			deleteX(x, &head, &last);
			break;
		}
		case 6: {
			returnN(head,last);
			break;
		}
		case 7:  exit(0);
		default: exit(1);
		}
	}
	return 0;
}
