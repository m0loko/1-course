#pragma once

struct Country {
    char name[50];          
    char capital[50];       
    long population;       
    double area;            
    char president[50];     
};

struct Element {
    Element* Prev;
    Element* Next;
    void* Data;
    Element(Element* prev, void* data, Element* next) {
        Prev = prev;
        Data = data;
        Next = next;
    }
    Element* GetNext() {
        return Next;
    }
    Element* GetPrev() {
        return Prev;
    }
};

struct Object {
    Element* Head;
    Object() {
        Head = nullptr;
    }
    Element* GetFirst() {
        return Head;
    }
    Element* GetLast();
    Element* Search(void* data);
    Element* SearchByName(const char* name);
    bool Insert(void* data);
    bool InsertEnd(void* data);
    bool Delete(Element* e);
    bool Delete(void* data);
    bool DeleteList();
    void PrintList(void(*f)(void*));
    void PrintList(void(*f)(void*), Element*);
    int CountList();
};

Object Create();