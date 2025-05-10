#include "stdafx.h"
#include <iostream>
#include <locale>
#include "Dictionary.h"
#if defined(TEST_CREATE_01) + defined(TEST_CREATE_02) + defined(TEST_ADDENTRY_03) + \
    defined(TEST_ADDENTRY_04) + defined(TEST_GETENTRY_05) + defined(TEST_DELENTRY_06) + \
    defined(TEST_UPDENTRY_07) + defined(TEST_UPDENTRY_08) + defined(TEST_DICTIONARY) > 1
#error "Должен быть активирован только один макрос"
#endif
int main()
{
    setlocale(LC_ALL, "rus");
    try
    {
            #ifdef TEST_DICTIONARY
        Dictionary::Instance d1 = Dictionary::Create("Преподаватели", 5);

        Dictionary::Entry e1 = { 1, "Гладкий" }, e2 = { 2, "Веялкин" },
            e3 = { 3, "Смелов" }, e4 = { 4, "Урбанович" }, e5 = { 2, "Пацей" };

        // Добавление элементов в словарь
        Dictionary::AddEntry(d1, e1); //добавление элемента словарь 
        Dictionary::AddEntry(d1, e2); //добавление элемента словарь 
        Dictionary::AddEntry(d1, e3); //добавление элемента словарь 
        Dictionary::AddEntry(d1, e4); //добавление элемента словарь 
        Dictionary::Entry ex2 = Dictionary::GetEntry(d1, 4); //найти элемент в словаре по идентификатору
        Dictionary::DelEntry(d1, 2); //удалить элемент по идентификатору
        Dictionary::Entry newentry1 = { 6, "Гурни" }; //элемент словаря
        Dictionary::UpdEntry(d1, 3, newentry1); //заменить элемент словаря по идентификатору
        Dictionary::Print(d1); //распечатать элементы словаря
        Dictionary::Instance d2 = Dictionary::Create("Студенты", 5);

        Dictionary::Entry s1 = { 1, "Иванов" }, s2 = { 2, "Петров" }, s3 = { 3, "Сидоров" };

        Dictionary::AddEntry(d2, s1);
        Dictionary::AddEntry(d2, s2);
        Dictionary::AddEntry(d2, s3);

        Dictionary::Entry newentry3 = { 3, "Николаев" };

        Dictionary::UpdEntry(d2, 3, newentry3);

        Dictionary::Print(d2);

        Delete(d1);
        Delete(d2);
    }
           #endif
    catch (const char* e) //обработка исключений словаря
    {
        std::cout << e << std::endl;
    }

    system("pause");
    return 0;
}