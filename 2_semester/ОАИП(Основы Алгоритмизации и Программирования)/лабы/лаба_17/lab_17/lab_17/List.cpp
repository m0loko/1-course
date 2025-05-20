#include "List.h"
#include <cstring>

bool Object::Insert(void* data) {
    bool rc = false;
    if (Head == nullptr) {
        Head = new Element(nullptr, data, nullptr);
        rc = true;
    }
    else {
        Head = (Head->Prev = new Element(nullptr, data, Head));
        rc = true;
    }
    return rc;
}

bool Object::InsertEnd(void* data) {
    bool rc = false;
    if (Head == nullptr) {
        Head = new Element(nullptr, data, nullptr);
        rc = true;
    }
    else {
        Element* last = GetLast();
        last->Next = new Element(last, data, nullptr);
        rc = true;
    }
    return rc;
}

Element* Object::Search(void* data) {
    Element* rc = Head;
    while (rc != nullptr && rc->Data != data) {
        rc = rc->Next;
    }
    return rc;
}

Element* Object::SearchByName(const char* name) {
    Element* rc = Head;
    while (rc != nullptr) {
        Country* country = (Country*)rc->Data;
        if (strcmp(country->name, name) == 0) {
            return rc;
        }
        rc = rc->Next;
    }
    return nullptr;
}

void Object::PrintList(void(*f)(void*)) {
    Element* e = Head;
    while (e != nullptr) {
        f(e->Data);
        e = e->GetNext();
    }
}

void Object::PrintList(void(*f)(void*), Element* e) {
    if (e != nullptr) {
        f(e->Data);
    }
}

bool Object::Delete(Element* e) {
    bool rc = false;
    if (e != nullptr) {
        if (e->Next != nullptr) {
            e->Next->Prev = e->Prev;
        }
        if (e->Prev != nullptr) {
            e->Prev->Next = e->Next;
        }
        else {
            Head = e->Next;
        }
        delete (Country*)e->Data;
        delete e;
        rc = true;
    }
    return rc;
}

bool Object::Delete(void* data) {
    return Delete(Search(data));
}

Element* Object::GetLast() {
    Element* e = Head;
    Element* rc = e;
    while (e != nullptr) {
        rc = e;
        e = e->GetNext();
    }
    return rc;
}

int Object::CountList() {
    int count = 0;
    Element* e = Head;
    while (e != nullptr) {
        count++;
        e = e->GetNext();
    }
    return count;
}

bool Object::DeleteList() {
    bool rc = false;
    Element* current = Head;
    while (current != nullptr) {
        Element* next = current->Next;
        delete (Country*)current->Data; 
        delete current; 
        current = next;
        rc = true;
    }
    Head = nullptr;
    return rc;
}


Object Create() {
    return *(new Object());
}