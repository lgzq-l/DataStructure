//À≥–Ú’ª µœ÷
#include <iostream>
using namespace std;

template<class T>
class stack
{
public:
    virtual bool isEmpty()const=0;
    virtual void push(const T &x)=0;
    virtual T pop()=0;
    virtual T top()const=0;
    virtual ~stack(){}
};

template<class T>
class seqStack:public stack<T>
{
private:
    T *elem;
    int top_p;
    int maxSize;
    void doubleSpace();

public:
    seqStack(int initSize=10);
    ~seqStack();
    bool isEmpty()const;
    void push(const T &x);
    T pop();
    T top()const;
};

template<class T>
seqStack<T>::seqStack(int initSize)
{
    elem = new T[initSize];
    maxSize = initSize;
    top_p = -1;
}

template<class T>
seqStack<T>::~seqStack()
{
    delete []elem;
}

template<class T>
bool seqStack<T>::isEmpty()const
{
    return top_p == -1;
}

template<class T>
void seqStack<T>::push(const T &x)
{
    if(top_p == maxSize-1)doubleSpace();
    elem[++top_p]=x;
}

template<class T>
T seqStack<T>::pop()
{
    return elem[top_p--];
}

template<class T>
T seqStack<T>::top()const
{
    return elem[top_p];
}

template<class T>
void seqStack<T>::doubleSpace()
{
    T *tmp = elem;
    elem = new T[2*maxSize];
    for(int i=0;i<maxSize;++i)elem[i]=tmp[i];
    maxSize*=2;
    delete []tmp;
}

int main()
{
    seqStack<int> s(5);
    if(!s.isEmpty())cout<<"True"<<endl;else cout<<"False"<<endl;
    for(int i=0;i<5;i++)s.push(2*i+i*i);
    if(!s.isEmpty())cout<<"True"<<endl;
    cout<<s.pop()<<endl;
    cout<<s.top()<<endl;
    return 0;
}
