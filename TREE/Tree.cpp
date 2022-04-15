//用兄弟儿子结点表示树
#include <iostream>
using namespace std;

template<class T>
class linkQueue
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T &x,node *N = NULL)
        {
            data=x;
            next=N;
        }
        node():next(NULL){}
        ~node(){}
    };
    
    node *front,*rear;

public:
    linkQueue(){front=rear=NULL;}
    ~linkQueue();
    bool isEmpty(){return front==NULL;}
    T getHead(){return front->data;}
    void enQueue(const T &x);
    int size()const;
    T deQueue();
};

template<class T>
void linkQueue<T>::enQueue(const T &x)
{
    if(rear==NULL)
        front = rear = new node(x);
    else{
        rear->next = new node(x);
        rear = rear->next;
    }
}

template<class T>
T linkQueue<T>::deQueue()
{
    node *tmp = front;
    T value = front->data;
    front = front->next;
    if(front==NULL)rear=NULL;
    delete tmp;
    return value;
}

template<class T>
linkQueue<T>::~linkQueue()
{
    node *tmp;
    while(front!=NULL)
    {
        tmp=front;
        front=front->next;
        delete tmp;
    }
}

template<class T>
int linkQueue<T>::size()const
{
    node *tmp=front;
    int n=0;
    while(tmp!=NULL){tmp=tmp->next;n++;}
    return n;
}

template<class T>
class tree
{
    struct node
    {
        T data;
        node *son,*brother;

        node(T d,node *s=NULL,node *b=NULL){data =d;son=s;brother=b;}
        node(){}
    };

    node *root;

public:
    tree(node *t=NULL){root=t;}
    void createTree(T flag);
    void preOrder(){cout<<"preOrder  : ";preOrder(root);cout<<endl;}
    void postOrder(){cout<<"postOrder : ";postOrder(root);cout<<endl;}
    void levelOrder();

private:
    void preOrder(node *t);
    void postOrder(node *t);
};

template<class T>
void tree<T>::createTree(T flag)
{
    linkQueue<node*> que;
    node *tmp;
    T x,son;

    cout<<"\n输入根节点：";
    cin>>x;
    root = new node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp=que.deQueue();
        cout<<"\n输入"<<tmp->data<<"的所有儿子（以"<<flag<<"结束）：";
        cin>>son;
        if(son==flag)continue;
        tmp->son = new node(son);
        tmp = tmp->son;
        que.enQueue(tmp);
        while(true)
        {
            cin>>son;
            if(son==flag)break;
            tmp->brother = new node(son);
            tmp=tmp->brother;
            que.enQueue(tmp);
        }
    }
    cout<<"create completed!\n";
}

template<class T>
void tree<T>::preOrder(node *t)
{
    if(t==NULL)return;
    cout<<t->data<<' ';

    node *p = t->son;
    while(p!=NULL)
    {
        preOrder(p);
        p=p->brother;
    }
}

template<class T>
void tree<T>::postOrder(node *t)
{
    if(t==NULL)return;

    node *p = t->son;
    while(p!=NULL)
    {
        postOrder(p);
        p=p->brother;
    }

    cout<<t->data<<' ';
}

template<class T>
void tree<T>::levelOrder()
{
    linkQueue<node*> que;
    node *tmp;

    cout<<"levelOrder: ";

    if(root==NULL)return;
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp=que.deQueue();
        cout<<tmp->data<<' ';
        tmp=tmp->son;
        while(tmp!=NULL)
        {
            que.enQueue(tmp);
            tmp=tmp->brother;
        }
    }
    cout<<endl;
}

int main()
{
    tree<char> tr;
    tr.createTree('@');
    tr.preOrder();
    tr.postOrder();
    tr.levelOrder();

    return 0;
}
