//线性表的链式存储————双链表
#include <iostream>
using namespace std;

//顺序表的抽象类
template<class T>
class list
{
public:
    virtual void clear()=0;
    virtual int length()const=0;
    virtual void insert(int i,const T &x)=0;
    virtual void remove(int i)=0;
    virtual int search(const T &x)const=0;
    virtual T visit(int i)const=0;
    virtual void traverse()const=0;
    virtual void reverse()const=0;
    virtual ~list(){};
};

//双链表类的定义与实现
template<class T>
class linkList:public list<T>
{
private:
    struct node
    {
        T data;
        node *prior,*next;
        node(const T &x,node *p=NULL,node *n=NULL)
        {data=x;prior=p;next=n;}
        node():next(NULL),prior(NULL){}
        ~node(){}
    };
    node *head,*tail;
    int currentLength;
    node *move(int i)const
    {
        node *p=head;
        while(i-->=0)p=p->next;
        return p;
    }
public:
    linkList();
    ~linkList(){clear();delete head;delete tail;}
    void clear();
    int length()const{return currentLength;}
    void insert(int i,const T &x);
    void remove(int i);
    int search(const T &x)const;
    T visit(int i)const;
    void traverse()const;
    void reverse()const;
};

template<class T>
linkList<T>::linkList()
{
    head = new node;
    head->next = tail = new node;
    tail->prior = head;
    currentLength=0;
}

template<class T>
void linkList<T>::insert(int i,const T &x)
{
    node *pos=move(i),*tmp;
    if(!pos)return;
    tmp = new node(x,pos->prior,pos);
    pos->prior->next = tmp;
    pos->prior = tmp;
    currentLength++;
}

template<class T>
void linkList<T>::remove(int i)
{
    node *pos;
    pos = move(i);
    pos->prior->next = pos->next;
    pos->next->prior = pos->prior;
    delete pos;
    currentLength--;
}

template<class T>
void linkList<T>::clear()
{
    node *p = head->next,*q;
    head->next = tail;
    tail->prior = head;
    while(p!=tail)
    {
        q=p->next;
        delete p;
        p=q;
    }
    currentLength=0;
}

template<class T>
int linkList<T>::search(const T &x)const
{
    node *p=head->next;
    int i;
    for(i=0;p!=tail && p->data != x;i++)p=p->next;
    if(p==tail)return -1;else return i;
}

template<class T>
T linkList<T>::visit(int i)const
{
    return move(i)->data;
}

template<class T>
void linkList<T>::traverse()const
{
    node *p = head->next;
    while(p!=tail)
    {
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<endl;
}

template<class T>
void linkList<T>::reverse()const
{
    node *p;

    for(p = tail->prior; p != head;p = p->prior)cout<<p->data<<' ';
    cout<<endl;
}

int main()
{
    linkList<int> obj;
    for(int i=0;i<=10;i++)obj.insert(i,2*i);
    obj.traverse();
    cout<<obj.visit(1)<<endl;
    obj.remove(2);
    obj.traverse();
    obj.insert(5,111);
    obj.traverse();
    cout<<obj.search(111)<<endl;
    cout<<obj.length()<<endl;
    obj.reverse();
    return 0;
}
