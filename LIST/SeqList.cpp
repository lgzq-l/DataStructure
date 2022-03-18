//线性表的顺序存储
#include <iostream>
using namespace std;

//顺序表的抽象类
template<class elemType>
class list
{
public:
    virtual void clear()=0;
    virtual int length()const=0;
    virtual void insert(int i,const elemType &x)=0;
    virtual void remove(int i)=0;
    virtual int search(const elemType &x)const=0;
    virtual elemType visit(int i)const=0;
    virtual void traverse()const=0;
    virtual ~list(){};
    virtual void erase(int i)=0;
};

//顺序表类的定义与实现
template<class elemType>
class seqList:public list<elemType>
{
private:
    elemType *data;
    int currentLength;
    int maxsize;
    void doubleSpace();
public:
    seqList(int initSize=10);
    ~seqList();
    void clear();
    int length()const;
    void insert(int i,const elemType &x);
    void remove(int i);
    int search(const elemType &x)const;
    elemType visit(int i)const;
    void traverse()const;
    void erase(int i);
};

template<class elemType>
seqList<elemType>::~seqList()
{
    delete []data;
}

template<class elemType>
void seqList<elemType>::clear()
{
    currentLength=0;
}

template<class elemType>
int seqList<elemType>::length()const
{
    return currentLength;
}

template<class elemType>
elemType seqList<elemType>::visit(int i)const
{
    return data[i];
}

template<class elemType>
void seqList<elemType>::traverse()const
{
    for(int i=0;i<currentLength;++i)cout<<data[i]<<' ';
    cout<<endl;
}

template<class elemType>
seqList<elemType>::seqList(int initSize)
{
    data = new elemType[initSize];
    maxsize=initSize;
    currentLength=0;
}

template<class elemType>
int seqList<elemType>::search(const elemType &x)const
{
    int i;
    for(i=0;i<currentLength && data[i]!=x;++i);
    if(i==currentLength)return -1;
    else return i;
}

template<class elemType>
void seqList<elemType>::doubleSpace()
{
    elemType *tmp = data;
    maxsize*=2;
    data = new elemType[maxsize];
    for(int i=0;i<currentLength;++i)data[i]=tmp[i];
    delete []tmp;
}

template<class elemType>
void seqList<elemType>::insert(int i,const elemType &x)
{
    if(currentLength==maxsize)doubleSpace();
    for(int j=currentLength;j>i;j--)data[j]=data[j-1];
    data[i]=x;
    ++currentLength;
}

template<class elemType>
void seqList<elemType>::remove(int i)
{
    for(int j=i;j<currentLength-1;j++)
        data[j]=data[j+1];
    --currentLength;
}

template<class elemType>
void seqList<elemType>::erase(int i)
{
    elemType tmp = data[i];
    int cnt=0;
    for(int j=0;j<currentLength;++j)
        if(data[j]=tmp)++cnt;
        else data[j-cnt]=data[j];
    currentLength-=cnt;
} 

int main()
{
    seqList<int> obj(10);
    for(int i=0;i<10;i++)obj.insert(i,2*i+1);
    cout<<obj.length()<<endl;
    cout<<obj.visit(2)<<endl;
    obj.insert(2,56);
    cout<<obj.search(7)<<endl;
    cout<<obj.visit(3)<<endl;
    obj.remove(2);
    cout<<obj.length()<<endl;
    cout<<obj.visit(2)<<endl;
    obj.traverse();
    return 0;
}
