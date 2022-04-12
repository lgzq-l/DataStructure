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

//中序线索树的定义
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

//线索树建立，和普通二叉树的构造相同
template<class T>
void ThreadTree<T>::createTree(T flag)
{
    linkQueue<node *> que;
    node *tmp;
    T x,ldata,rdata;

    //创建树，输入flag表示空
    cout<<"\n输入根节点：";
    cin>>x;
    root = new node(x);
    que.enQueue(root);

    while(!que.isEmpty())
    {
        tmp=que.deQueue();
        cout<<"\n输入"<<tmp->data<<"的两个儿子（"<<flag<<"表示空节点）：";
        cin>>ldata>>rdata;
        if(ldata!=flag){tmp->left = new node(ldata);que.enQueue(tmp->left);}
        if(rdata!=flag){tmp->right = new node(rdata);que.enQueue(tmp->right);}
    }

    cout<<"create completed!\n";
}

//中序线索树的穿线
template<class T>
void ThreadTree<T>::makeThread()//共有的穿线函数
{
    if(root)
    {
        node *pt=NULL;
        makeThread(root,pt);
    }
}

template<class T>
void ThreadTree<T>::makeThread(node *t,node *&p)//私有的穿线函数
{
    if(t==NULL)return;
    if(t->left==NULL){                          //左子树为空，p为t的中序遍历的前驱
        t->left = p;
        t->lflag = true;
    }
    else{                                       //左子树非空
        makeThread(t->left,p);                  //为左子树穿线
        if(p!=NULL){                            //为左子树中序遍历序列的最后一个节点穿线
            p->right = t;
            p->rflag = true;
        }
    }

    p=t;                                        //将根节点设为中序遍历的最后一个结点
    makeThread(t->right,p);                     //为右子树穿线
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
