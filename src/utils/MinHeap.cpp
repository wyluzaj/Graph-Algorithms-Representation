#include "../../include/utils/MinHeap.h"

MinHeap::MinHeap(int capacity) {
    cap = capacity;
    size = 0;
    data = new HeapEdge[cap];
}

MinHeap::~MinHeap() {
    delete[] data;
}

bool MinHeap::isEmpty() const {
    return size == 0;
}

void MinHeap::insert(const HeapEdge &e) {
    if (size == cap) {
        int newCap = cap * 2;
        HeapEdge* tmp = new HeapEdge[newCap];
        for (int i = 0; i < cap; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        cap = newCap;
    }
    data[size] = e;
    siftUp(size);
    size++;
}

HeapEdge MinHeap::extractMin() {
    HeapEdge root = data[0];
    size--;
    data[0] = data[size];
    siftDown(0);
    return root;
}

void MinHeap::siftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (data[parent].weight <= data[i].weight) break;
        swap(data[parent], data[i]);
        i = parent;
    }
}

void MinHeap::siftDown(int i) {
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && data[left].weight < data[smallest].weight)
            smallest = left;
        if (right < size && data[right].weight < data[smallest].weight)
            smallest = right;

        if (smallest == i) break;

        swap(data[i], data[smallest]);
        i = smallest;
    }
}

void MinHeap::swap(HeapEdge &a, HeapEdge &b) {
    HeapEdge tmp = a;
    a = b;
    b = tmp;
}
