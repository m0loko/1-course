#include "Heap.h"
#include <iostream>
#include <iomanip>

void AAA::print()
{
    std::cout << x;
}

namespace heap
{
    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f));
    }

    int Heap::left(int ix)
    {
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);
    }

    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2);
    }

    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;
    }

    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];
        storage[i] = storage[j];
        storage[j] = buf;
    }

    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;
        if (l >= 0 && l < size)
        {
            if (isGreat(storage[l], storage[ix])) irl = l;
            if (r >= 0 && r < size && isGreat(storage[r], storage[irl])) irl = r;
            if (irl != ix)
            {
                swap(ix, irl);
                heapify(irl);
            }
        }
    }

    void Heap::insert(void* x)
    {
        if (!isFull())
        {
            int i = size++;
            storage[i] = x;
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);
                i = parent(i);
            }
        }
    }

    void* Heap::extractMax()
    {
        void* rc = nullptr;
        if (!isEmpty())
        {
            rc = storage[0];
            storage[0] = storage[--size];
            heapify(0);
        }
        return rc;
    }

    void* Heap::extractMin()
    {
        if (isEmpty()) return nullptr;

        if (size == 1) {
            void* min = storage[0];
            size = 0;
            return min;
        }
        int firstLeaf = size / 2;
        int minIndex = firstLeaf;
        for (int i = firstLeaf + 1; i < size; i++) {
            if (isLess(storage[i], storage[minIndex])) {
                minIndex = i;
            }
        }

        void* min = storage[minIndex];
        storage[minIndex] = storage[--size];
        if (minIndex != size) {
            int p = parent(minIndex);
            if (p >= 0 && isLess(storage[minIndex], storage[p])) {
                
                while (minIndex > 0 && isLess(storage[minIndex], storage[parent(minIndex)])) {
                    swap(minIndex, parent(minIndex));
                    minIndex = parent(minIndex);
                }
            }
            else {
                
                heapify(minIndex);
            }
        }

        return min;
    }

    void* Heap::extractI(int index)
    {
        if (index < 0 || index >= size) return nullptr;

        void* extracted = storage[index];
        storage[index] = storage[--size];

        if (index != size) {
            int p = parent(index);
            if (p >= 0 && isLess(storage[index], storage[p])) {
                while (index > 0 && isLess(storage[index], storage[parent(index)])) {
                    swap(index, parent(index));
                    index = parent(index);
                }
            }
            else {
                heapify(index);
            }
        }

        return extracted;
    }

    Heap* unionHeap(Heap* h1, Heap* h2)
    {
        if (!h1 || !h2 || h1->compare != h2->compare) return nullptr;

        Heap* result = new Heap(h1->size + h2->size, h1->compare);

        for (int i = 0; i < h1->size; i++) {
            result->insert(h1->storage[i]);
        }

        for (int i = 0; i < h2->size; i++) {
            result->insert(h2->storage[i]);
        }

        return result;
    }

    void Heap::scan(int i) const
    {
        int probel = 20;
        std::cout << '\n';
        if (size == 0)
            std::cout << "Куча пуста";

        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();

            if (u == y)
            {
                std::cout << '\n';
                if (y == 0)
                    y = 2;
                else
                    y += y * 2;
                probel /= 2;
            }
        }
        std::cout << '\n';
    }
}