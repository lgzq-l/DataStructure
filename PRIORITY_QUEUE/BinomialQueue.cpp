#include <iostream>
#include "tree.h"
#include <cmath>
using namespace std;

//Binomial的定义
template<class T>
class Binomial
{
    typename tree<T>::node **forest;
    int noOfTree;

    typename tree<T>::node *merge(typename tree<T>::node *t1,typename tree<T>::node *t2);
    int findmin();
    void deleteTree(typename tree<T>::node *rt)
    {
        typename tree<T>::node *son = rt->son,*t;
        while(son!=NULL)
        {
            t=son;
            son=son->brother;
            deleteTree(t);
        }
        delete rt;
    }

public:
    Binomial(int n=100)
    {
        noOfTree=int (log(n)/log(2))+1;
        forest = new typename tree<T>::node *[noOfTree];
        for(int i=0;i<noOfTree;i++)forest[i]=NULL;
    }

    ~Binomial()
    {
        for(int i=0;i<noOfTree;i++)
            if(forest[i]!=NULL)deleteTree(forest[i]);
        delete []forest;
    }
    
    void enQueue(T x);
    T deQueue();
    bool isEmpty();
    T getHead();
    void merge(Binomial &other);
};

template<class T>
void Binomial<T>::merge(Binomial &other)
{
    typename tree<T>::node **tmp = forest, *carry;                                    //当前对象暂存在tmp中
    int tmpSize=noOfTree;                                                   //当前对象规模暂存在tmpSize中
    int min=noOfTree < other.noOfTree ? noOfTree : other.noOfTree;
    int i;

    if(noOfTree < other.noOfTree)                                           //确定归并后的森林规模
    {
        noOfTree = other.noOfTree;
        if(other.forest[noOfTree] != NULL)++noOfTree;
    }
    else if(forest[noOfTree] != NULL)++noOfTree;

    forest = new typename tree<T>::node *[noOfTree];                                 //为归并后的队列申请空间
    for(i=0;i<noOfTree;++i)forest[i]=NULL;

    carry=NULL;                                                             //初始时进位为空
    for(i=0;i<min;++i)                                                      //归并两个队列中阶数相同的树
    {
        if(carry==NULL)                                                     //没有进位
        {
            if(tmp[i]==NULL)forest[i]=other.forest[i];
            else{
                if(other.forest[i]==NULL)forest[i]=tmp[i];
                else carry=merge(other.forest[i],tmp[i]);
            }
        }
        else{                                                               //有进位
            if(tmp[i]!=NULL && other.forest[i]!=NULL)
            {
                forest[i]=carry;
                carry=merge(other.forest[i],tmp[i]);
            }
            else{
                if(tmp[i]==NULL && other.forest[i]==NULL){
                    forest[i]=carry;
                    carry=NULL;
                }
                else 
                    if(tmp[i]==NULL)carry=merge(other.forest[i],carry);
                    else carry=merge(tmp[i],carry);
            }
        }
    }

    //一个队列已结束
    if(other.noOfTree==min){
        for(;i<tmpSize;++i)
            if(carry==NULL)forest[i]=tmp[i];
            else
                if(tmp[i]==NULL){forest[i]=carry;carry=NULL;}
                else carry=merge(tmp[i],carry);
    }
    else{
        for(;i<other.noOfTree;++i)
            if(carry==NULL)forest[i]=other.forest[i];
            else
                if(other.forest[i]==NULL){forest[i]=carry;carry=NULL;}
                else carry=merge(other.forest[i],carry);
    }
    if(carry!=NULL)forest[i]=carry;

    for(i=0;i<other.noOfTree;i++)other.forest[i]=NULL;
    delete []tmp;
}

template<class T>
typename tree<T>::node *Binomial<T>::merge(typename tree<T>::node *t1,typename tree<T>::node *t2)
{
    typename tree<T>::node *min,*max;
    if(t1->data < t2->data){min=t1;max=t2;}
    else{min=t2;max=t1;}

    if(min->son==NULL)min->son=max;
    else{
        typename tree<T>::node *t=min->son;
        while(t->brother!=NULL)t=t->brother;
        t->brother=max;
    }
    return min;
}

template<class T>
void Binomial<T>::enQueue(T x)
{
    Binomial tmp(1);
    tmp.forest[0] = new typename tree<T>::node(x);
    merge(tmp);
}

template<class T>
T Binomial<T>::deQueue()
{
    T value;
    int min=findmin();

    if(min==0){
        value=forest[0]->data;
        delete forest[0];
        forest[0]=NULL;
        return value;
    }

    typename tree<T>::node *t=forest[min],*son,*brother;
    int sizeOfQueue=int(pow(2,min)-1);
    Binomial tmp(sizeOfQueue);
    value=t->data;
    forest[min]=NULL;

    son=t->son;
    delete t;
    int i=0;
    do{
        tmp.forest[i++]=son;
        brother=son->brother;
        son->brother=NULL;
    }while((son=brother)!=NULL);

    merge(tmp);
    return value;
}

template<class T>
int Binomial<T>::findmin()
{
    int min;

    //找到第一棵非空树min
    int i;
    for(i=0;i<noOfTree && forest[i]==NULL;++i);
    min=i;

    //扫描后续的树，找到根节点最小的树
    for(;i<noOfTree;++i)
        if(forest[i]!=NULL && forest[i]->data < forest[min]->data)min=i;

    return min;
}

template<class T>
bool Binomial<T>::isEmpty()
{
    for(int i=0;i<noOfTree;i++)
        if(forest[i]!=NULL)return false;
    return true;
}

template<class T>
T Binomial<T>::getHead()
{
    int pos=findmin();
    return forest[pos]->data;
}

int main()
{
    int a[10]={1,6,5,89,23,4,6,124,25,12};
    Binomial<int> q(10);
    for(int i=0;i<10;i++)q.enQueue(a[i]);
    q.deQueue();

    int b[10]={3,5,2,8,6,41,15,23,65,98};
    Binomial<int> p(10);
    for(int i=0;i<10;i++)p.enQueue(b[i]);

    q.merge(p);

    while(!q.isEmpty())cout<<q.deQueue()<<' ';

    return 0;
}
