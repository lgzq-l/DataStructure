#include <iostream>
using namespace std;

struct Type
{
    int coff;
    int exp;
};

struct Node
{
    Type data;
    Node* next;

    Node():next(NULL){}
    Node(int a,int b,Node *n=NULL){data.coff=a;data.exp=b;next=n;}
    ~Node(){}
};

class Poly
{
private:
    Node *head;
    Type stop_flag;                //用于判断多项式输入结束
public:
    Poly(const Type &stop);        //从用户处获取结束标志并初始化多项式
    void getPoly();
    void addPoly(const Poly &L1,const Poly &L2);
    void disPoly();
    void clear();
    ~Poly(){clear();delete head;}
};

void getStop(Type &x)
{
    int m,n;
    cout<<"请输入结束标志：";
    cin>>m>>n;
    x.coff=m;
    x.exp=n;
}

Poly::Poly(const Type &stop)
{
    head = new Node();
    stop_flag=stop;
}

void Poly::getPoly()
{
    int m,n;
    while(true)
    {
        cin>>m>>n;
        if(m == stop_flag.coff && n == stop_flag.exp)break;
        Node *tmp,*p=head->next;
        tmp = new Node(m,n,p);
        head->next = tmp;
    }
}

void Poly::addPoly(const Poly &L1,const Poly &L2)
{
    Node *tmp,*p;

    Node *exp1 = L1.head;
    Node *exp2 = L2.head;
    head=p=new Node();
    exp1=exp1->next;exp2=exp2->next;
    while(exp1 != NULL && exp2 != NULL)
    {
        if(exp1->data.exp < exp2->data.exp)
        {
            p->next = new Node(exp1->data.coff,exp1->data.exp);
            exp1 = exp1->next;
        }

        else if(exp1->data.exp > exp2->data.exp)
        {
            p->next = new Node(exp2->data.coff,exp2->data.exp);
            exp2 = exp2->next;
        }

        else if(exp1->data.coff + exp2->data.coff != 0)
        {
            p->next = new Node(exp1->data.coff + exp2->data.coff,exp2->data.exp);
            exp1 = exp1->next;
            exp2 = exp2->next;
        }
        else if(exp1->data.coff + exp2->data.coff == 0)
        {
            exp1 = exp1->next;
            exp2 = exp2->next;
        }
        p = p->next;
    }

    if(exp1 == NULL)tmp = exp2;else tmp = exp1;
    while(tmp != NULL)
    {
        p->next = new Node(tmp->data.coff,tmp->data.exp);
        tmp = tmp->next;
        p = p->next;
    }
}

void Poly::disPoly()
{
    Node *p = head->next;
    while(p != NULL)
    {
        cout<< p->data.coff << "x^" << p->data.exp;
        if(p->next !=NULL)cout<<" + ";
        p = p->next;
    }
    cout<<endl;
}

void Poly::clear()
{
    Node *p = head->next,*q;
    head->next = NULL;
    while(p!=NULL)
    {
        q=p->next;
        delete p;
        p=q;
    }
}

int main()
{
    Type stop_flag;
    getStop(stop_flag);

    Poly L1(stop_flag),L2(stop_flag),L3(stop_flag);

    L1.getPoly();
    L2.getPoly();

    L3.addPoly(L1,L2);
    L1.disPoly();
    L2.disPoly();
    L3.disPoly();

    return 0;
}
