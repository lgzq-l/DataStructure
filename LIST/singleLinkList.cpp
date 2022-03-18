//线性表的链式存储————单链表
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
    virtual void reverse()=0;
    virtual void erase(int i)=0;
    virtual ~list(){};
};

//单链表类的定义与实现
template<class T>
class slinkList:public list<T>
{
private:
    struct node     //内嵌类
    {
        T data;
        node *next;

        node(const T &x,node *n=NULL){data=x;next=n;}
        node():next(NULL){}     //服务于头指针开辟
        ~node(){}
    };

    node *head;

public:
    slinkList();
    ~slinkList(){clear();delete head;}

    void clear();
    int length()const;
    void insert(int i,const T &x);
    void remove(int i);
    int search(const T &x)const;
    T visit(int i)const;
    void traverse()const;
    void reverse();
    void erase(int i);
};

template<class T>
slinkList<T>::slinkList()
{head = new node();}

template<class T>
int slinkList<T>::length()const
{
    int count=0;
    node *p = head->next;
    while(p!=NULL){count++; p = p->next;}
    return count;
}

template<class T>
int slinkList<T>::search(const T &x)const
{
    node *p = head->next;
    int i=0;
    while(p != NULL && p->data != x){p=p->next;i++;}
    if(p==NULL)return -1;else return i;
}

template<class T>
void slinkList<T>::insert(int i,const T &x)
{
    if(i<0)return;
    node *tmp,*p=head;
    for(int j=0;p && j<i;j++)p = p->next;
    if(!p)return;
    tmp = new node(x,p->next);
    p->next=tmp;
}

template<class T>
void slinkList<T>::remove(int i)
{
    if(i<0)return;
    node *tmp,*p=head;
    for(int j=0;p && j<i-1;j++)p = p->next;
    if(!p || !p->next)return;
    tmp = p->next;
    p->next = tmp->next;
    delete tmp;
}

template<class T>
void slinkList<T>::clear()
{
    node *p = head->next,*q;
    head->next = NULL;
    while(p!=NULL)
    {
        q=p->next;
        delete p;
        p=q;
    }
}

template<class T>
T slinkList<T>::visit(int i)const
{
    node *p = head;
    while(p != NULL && i>=0){p=p->next;i--;}
    return p->data;
}

template<class T>
void slinkList<T>::traverse()const
{
    node *p = head->next;
    while(p!=NULL){cout<<p->data<<' ';p = p->next;}
    cout<<endl;
}

template<class T>
void slinkList<T>::reverse()
{
    node *p,*q;
    p = head->next;
    head->next = NULL;          //断开head 和 head->next

    while(p)                    //做插入操作，将 head->next 元素从头开始依次插入到 head 之后
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

template<class T>
void slinkList<T>::erase(int i)
{
    node *pre=head;
    for(int j=0;pre && j<i;j++)pre = pre->next;     //pre指向被删除结点的前一个结点，delp指向被删结点
    node *delp = pre->next;
    T tmp = delp->data;
    int cnt=1;

    pre->next = delp->next;                         //删除第i个结点
    delete delp;

    for(pre = head; pre->next !=NULL; pre = pre->next)
        if(pre->next->data == tmp)
        {
            delp = pre->next;
            pre->next = delp->next;
            delete delp;
            ++cnt;
        }
}

int main()
{
    slinkList<int> obj;
    for(int i=0;i<=10;i++)obj.insert(i,2*i);
    obj.traverse();
    cout<<obj.visit(1)<<endl;
    obj.remove(2);
    obj.traverse();
    obj.insert(5,16);
    obj.traverse();
    cout<<obj.search(16)<<endl;
    cout<<obj.length()<<endl;
    obj.reverse();
    obj.traverse();
    obj.erase(2);
    obj.traverse();
    return 0;
}
