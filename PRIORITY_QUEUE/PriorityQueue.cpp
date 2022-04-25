//堆的实现
#include<iostream>
using namespace std;

template<class T>
class priorityQueue
{
private:
    int currentSize;
    T *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);

public:
    priorityQueue(int capacity=100)
    {
        array = new T[capacity];
        maxSize=capacity;
        currentSize=0;
    }
    priorityQueue(const T *items,int size);
    ~priorityQueue(){delete []array;}
    bool isEmpty()const{return currentSize==0;}
    void enQueue(const T &x);
    T deQueue();
    T getHead(){return array[1];}
};

template<class T>
void priorityQueue<T>::enQueue(const T &x)
{
    if(currentSize==maxSize-1)doubleSpace();

    //向上过滤
    int hole = ++currentSize;
    for(;hole>1 && x<array[hole/2];hole/=2)
        array[hole]=array[hole/2];
    array[hole]=x;
}

template<class T>
T priorityQueue<T>::deQueue()
{
    T minItem;
    minItem=array[1];
    array[1]=array[currentSize--];
    percolateDown(1);
    return minItem;
}

template<class T>
void priorityQueue<T>::percolateDown(int hole)
{
    int child;
    T tmp=array[hole];

    for(;hole*2<currentSize;hole=child)
    {
        child=hole*2;
        if(child!=currentSize && array[child+1]<array[child])
            child++;
        if(array[child]<tmp)array[hole]=array[child];
        else break;
    }
    array[hole]=tmp;
}

template<class T>
void priorityQueue<T>::buildHeap()
{
    for(int i=currentSize/2;i>0;i--)
        percolateDown(i);
}

template<class T>
priorityQueue<T>::priorityQueue(const T *items,int size):maxSize(size+10),currentSize(size)
{
    array = new T[maxSize];
    for(int i=0;i<size;i++)
        array[i+1]=items[i];
    buildHeap();
}

template<class T>
void priorityQueue<T>::doubleSpace()
{
    T *tmp = new T[maxSize];
    for(int i=1;i<maxSize;i++)
        tmp[i]=array[i];

    maxSize*=2;
    array = new T[maxSize];
    for(int i=1;i<maxSize;i++)
        array[i]=tmp[i];
    delete tmp;
}

int main()
{
    int a[10]={1,6,5,89,23,4,6,124,25,12};
    priorityQueue<int> q(a,10);
    q.enQueue(66);
    q.enQueue(159);
    q.deQueue();
    while(!q.isEmpty())cout<<q.deQueue()<<' ';
    return 0;
}
