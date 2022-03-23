//循环队列线性实现
#include <iostream>
using namespace std;

template<class T>
class seqQueue
{
private:
    T *elem;
    int maxSize;
    int front,rear;
    void doubleSpace();

public:
    seqQueue(int size=10)
    {
        elem = new T[size];
        maxSize = size;
        front = rear =0;
    }
    ~seqQueue(){delete []elem;}
    bool isEmpty(){return front==rear;}  //front指向头元素的前一个位置
    T getHead(){return elem[(front+1)%maxSize];}            //T &getHead(){return elem[(front+1)%maxSize];}     加上&提高性能
    void enQueue(const T &x);//进队
    T deQueue();//出队
};

template<class T>
void seqQueue<T>::doubleSpace()
{
    T *tmp=elem;
    elem = new T[2*maxSize];
    for(int i=1;i<maxSize;++i)
        elem[i]=tmp[(front+i)%maxSize];
    front=0; rear=maxSize-1;
    maxSize*=2;
    delete tmp;
}

template<class T>
void seqQueue<T>::enQueue(const T &x)
{
    if((rear+1)%maxSize==front)doubleSpace();
    rear=(rear+1)%maxSize;
    elem[rear]=x;
}

template<class T>
T seqQueue<T>::deQueue()
{
    front=(front+1)%maxSize;
    return elem[front];
}

int main()
{
    seqQueue<int> s(5);int i;
    for(i=1;i<10;i++)
    s.enQueue(i);

    cout<<s.getHead();

    while(i-->7)s.enQueue(s.deQueue());
    while(!s.isEmpty())cout<<s.deQueue();

    return 0;
}
