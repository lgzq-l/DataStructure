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
};

//顺序表类的定义与实现
template<class elemType>
class seqList:public list<elemType>
{
private:
    elemType *data;
    int currentlength;
    int maxsize;
    void doubleSpace();
public:
    seqList(int initSize=10);
    ~seqList();
    void clear();
    int length()const;
    void insert(int i,const elemType &x);
    void
}
