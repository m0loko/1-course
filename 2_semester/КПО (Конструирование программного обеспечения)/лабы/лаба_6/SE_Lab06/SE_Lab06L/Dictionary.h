#pragma once
#include <cstring>
#define DICTNAMEMAXSIZE 20 //максимальный размер имени словар€
#define DICTMAXSIZE 100 //максимальна€ Ємкость словар€
#define ENTRYNAMEMAXSIZE 30 //максимальна€ длина имени в словаре 
#define THROW01 "Create: привышен размер словар€" 
#define THROW02 "Create: превышен размер максимальной Ємкости словар€"
#define THROW03 "AddEntry: переполнение словар€"
#define THROW04 "AddEntry: дублирование идентификатора"
#define THROW05 "GetEntry: не найден элемент"
#define THROW06 "DelEntry: не найден элемент"
#define THROW07 "UpdEntry: не найден элемент"
#define THROW08 "UpdEntry: дублирование идефнтификатора"
namespace Dictionary {
	struct Entry //элемент словар€
	{
		int id;
		char name[ENTRYNAMEMAXSIZE]; //символьна€ информаци€
	};
	struct Instance //экземпл€р словар€
	{
		char name[DICTNAMEMAXSIZE]; //им€ словар€
		int maxsize; //максимальна€ Ємкость
		int size; //текущий ращмер словар€
		Entry* dictionary; //массив элементов
	};
	Instance Create(const char name[DICTNAMEMAXSIZE], int size); //создаЄм словарь (им€ словар€,Ємкость словар€)
	void AddEntry(Instance& inst, Entry ed); //добавить элемент словар€(экземпл€р и элемент словар€)
	void DelEntry(Instance& inst, int id); //удалить элемент словар€ (экземпл€р и идентификатор словар€)
	void UpdEntry(Instance& inst, int id, Entry new_ed); //изменить элемент словар€ (экземпл€р словар€ и иденикатор удал€емого элемента)
	Entry GetEntry(Instance inst, int id); //получить элемент словар€ (экземпл€р словар€ и идентификатор)
	void Print(Instance d); //печать словар€
	void Delete(Instance& d); //удалить словарь
};