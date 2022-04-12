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

//�����������Ķ���
template<class T>
class ThreadTree{
private:
    struct node{
        node *left,*right;
        T data;
        bool lflag,rflag;

        node():left(NULL),right(NULL),lflag(false),rflag(false){}
        node(T item,node *L=NULL,node *R=NULL):data(item),left(L),right(R),lflag(false),rflag(false){}
        ~node(){}
    };

    node *root;

    void clear(node *t){
        if(t==NULL)return;
        if(!t->lflag)clear(t->left);
        if(!t->rflag)clear(t->right);
        delete t;
    }

    void makeThread(node *t,node *&p);

public:
    ThreadTree():root(NULL){}
    ThreadTree(const T &value){root = new node(value);}
    ThreadTree(node *p){root = p;}

    void createTree(T flag);
    void makeThread();
    void visitThread();
    ~ThreadTree(){clear(root);}
};

//����������������ͨ�������Ĺ�����ͬ
template<class T>
void ThreadTree<T>::createTree(T flag)
{
    linkQueue<node *> que;
    node *tmp;
    T x,ldata,rdata;

    //������������flag��ʾ��
    cout<<"\n������ڵ㣺";
    cin>>x;
    root = new node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp=que.deQueue();
        cout<<"\n����"<<tmp->data<<"���������ӣ�"<<flag<<"��ʾ�սڵ㣩��";
        cin>>ldata>>rdata;
        if(ldata!=flag){tmp->left = new node(ldata);que.enQueue(tmp->left);}
        if(rdata!=flag){tmp->right = new node(rdata);que.enQueue(tmp->right);}
    }

    cout<<"create completed!\n";
}

//�����������Ĵ���
template<class T>
void ThreadTree<T>::makeThread()//���еĴ��ߺ���
{
    if(root)
    {
        node *pt=NULL;
        makeThread(root,pt);
    }
}

template<class T>
void ThreadTree<T>::makeThread(node *t,node *&p)//˽�еĴ��ߺ���
{
    if(t==NULL)return;
    if(t->left==NULL){                          //������Ϊ�գ�pΪt�����������ǰ��
        t->left = p;
        t->lflag = true;
    }
    else{                                       //�������ǿ�
        makeThread(t->left,p);                  //Ϊ����������
        if(p!=NULL){                            //Ϊ����������������е����һ���ڵ㴩��
            p->right = t;
            p->rflag = true;
        }
    }

    p=t;                                        //�����ڵ���Ϊ������������һ�����
    makeThread(t->right,p);                     //Ϊ����������
}

template<class T>
void ThreadTree<T>::visitThread()
{
    node *t = root;

    if(root==NULL)return;

    while(t->left != NULL)t = t->left;
    do{
        cout<<t->data<<' ';
        if(t->rflag)t = t->right;
        else{
            t = t->right;
        while(t!=NULL && !t->lflag && t->left!=NULL)t=t->left;
        }
    }while(t!=NULL);

    cout<<endl;
}

int main()
{
    ThreadTree<char> thTree;
    thTree.createTree('#');
    thTree.makeThread();
    thTree.visitThread();
    return 0;
}
