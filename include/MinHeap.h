#ifndef AIZO_GRAFS_MINHEAP_H
#define AIZO_GRAFS_MINHEAP_H


struct HeapEdge {
    int from;
    int to;
    int weight;
};

class MinHeap {
public:
    //default capacity is 128 can be overwritten
    MinHeap(int capacity = 128);
    ~MinHeap();

    //is empty
    bool isEmpty() const;

    // add new edge to heap
    void insert(const HeapEdge &e);

    //extract min edge from heap
    HeapEdge extractMin();

private:
    HeapEdge* data;  //array for storing heap
    int size;        //current number of elements
    int cap;         //capacity of the heap

    //sort upwards
    void siftUp(int i);

    //sort downwards
    void siftDown(int i);

    //swap
    static void swap(HeapEdge &a, HeapEdge &b);
};

#endif //AIZO_GRAFS_MINHEAP_H


