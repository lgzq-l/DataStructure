//二叉链表
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template<class T>
class binaryTree
{
    friend void printTree(const binaryTree<T> &t,T flag)
    {
    queue<T> q;
    q.push(t.root->data);
    cout<<endl;
    while(!q.empty())
    {
        T p,l,r;
        p=q.front();q.pop();
        l=t.lchild(p,flag);
        r=t.rchild(p,flag);
        cout<<p<<" "<<l<<" "<<r<<endl;
        if(l!=flag)q.push(l);
        if(r!=flag)q.push(r);
    }
}
private:
    struct node{
        friend struct stNode;
        node *left,*right;
        T data;

        node():left(NULL),right(NULL){}
        node(T item,node *L=NULL,node *R=NULL):data(item),left(L),right(R){}
        ~node(){}
    };
    struct stNode
    {
        node *no;
        int TimesPop;
        stNode(node *N=NULL):no(N),TimesPop(0){}
    };
    node *root;
public:
    binaryTree():root(NULL){}
    binaryTree(T x){root = new node(x);}
    ~binaryTree();
    void clear();
    bool isEmpty()const;
    T Root(T flag)const;
    T lchild(T x,T flag)const;//flag表示当x没有父亲、左儿子或右儿子时，函数返回的特殊值
    T rchild(T x,T flag)const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder()const;
    void midOrder()const;
    void postOrder()const;
    void levelOrder()const;
    void createTree(T flag);
    int size()const;
    int height()const;
    T parent(T x,T flag)const{return flag;}
private:
    node *find(T x,node *t)const
    {
        node *tmp;
        node *pin=NULL;
        if(t==NULL)return pin;
        if(t->data==x)return t;
        if(tmp=find(x,t->left))return tmp;
        else return find(x,t->right);
    }
    int size(node *t)const;
    int height(node *t)const;
    void clear(node *&t);
    void preOrder(node *t)const;
    void midOrder(node *t)const;
    void postOrder(node *t)const;
};

template<class T>
bool binaryTree<T>::isEmpty()const
{
    return root=NULL;
}

template<class T>
T binaryTree<T>::Root(T flag)const
{
    if(root==NULL)return flag;
    else return root->data;
}

template<class T>
void binaryTree<T>::clear(binaryTree<T>::node *&t)
{
    if(t==NULL)return;
    clear(t->left);
    clear(t->right);
    delete t;
    t=NULL;
}

template<class T>
void binaryTree<T>::clear()
{
    clear(root);
}

template<class T>
binaryTree<T>::~binaryTree()
{
    clear(root);
}

template<class T>
void binaryTree<T>::preOrder(binaryTree<T>::node *t)const
{
    if(t==NULL)return;
    cout<<t->data<<' ';
    preOrder(t->left);
    preOrder(t->right);
}

template<class T>
void binaryTree<T>::preOrder()const
{
    cout<<"\n（ 递归 ）前序遍历：";
    preOrder(root);

    cout<<"\n（非递归）前序遍历：";
    stack<node*> s;
    node *tmp;

    s.push(root);
    while(!s.empty())
    {
        tmp=s.top();s.pop();
        cout<<tmp->data<<' ';
        if(tmp->right!=NULL)s.push(tmp->right);
        if(tmp->left!=NULL)s.push(tmp->left);
    }
}

template<class T>
void binaryTree<T>::postOrder(binaryTree<T>::node *t)const
{
    if(t==NULL)return;
    postOrder(t->left);
    postOrder(t->right);
    cout<<t->data<<' ';
}

template<class T>
void binaryTree<T>::postOrder()const
{
    cout<<"\n（ 递归 ）后序遍历：";
    postOrder(root);

    cout<<"\n（非递归）后序遍历：";
    stack<stNode> s;
    stNode tmp(root);

    s.push(tmp);

    while(!s.empty())
    {
        tmp=s.top();s.pop();
        if(++tmp.TimesPop == 3)
        {
            cout<<tmp.no->data<<' ';
            continue;
        }
        s.push(tmp);
        if(tmp.TimesPop == 1)
        {
            if(tmp.no->left != NULL)
                s.push(stNode(tmp.no->left));
        }
        else
        {
            if(tmp.no->right != NULL)
                s.push(stNode(tmp.no->right));
        }
    }
    
}

template<class T>
void binaryTree<T>::midOrder(binaryTree<T>::node *t)const
{
    if(t==NULL)return;
    midOrder(t->left);
    cout<<t->data<<' ';
    midOrder(t->right);
}

template<class T>
void binaryTree<T>::midOrder()const
{
    cout<<"\n（ 递归 ）中序遍历：";
    midOrder(root);

    cout<<"\n（非递归）中序遍历：";
    stack<stNode> s;
    stNode tmp(root);

    s.push(tmp);
    while(!s.empty())
    {
        tmp=s.top();s.pop();
        if(++tmp.TimesPop == 2)
        {
            cout<<tmp.no->data<<' ';
            if(tmp.no->right != NULL)
                s.push(stNode(tmp.no->right));
        }
        else
        {
            s.push(tmp);
            if(tmp.no->left != NULL)
                s.push(stNode(tmp.no->left));
        }
    }
}

template<class T>
void binaryTree<T>::levelOrder()const
{
    queue<node*> que;
    node *tmp;

    cout<<"\n层序遍历：";
    que.push(root);

    while(!que.empty())
    {
        tmp=que.front();que.pop();
        cout<<tmp->data<<' ';
        if(tmp->left)que.push(tmp->left);
        if(tmp->right)que.push(tmp->right);
    }
}

template<class T>
void binaryTree<T>::delLeft(T x)
{
    node *tmp=find(x,root);
    if(tmp==NULL)return;
    clear(tmp->left);
}

template<class T>
void binaryTree<T>::delRight(T x)
{
    node *tmp=find(x,root);
    if(tmp==NULL)return;
    clear(tmp->right);
}

template<class T>
T binaryTree<T>::lchild(T x,T flag)const
{
    node *tmp=find(x,root);
    if(tmp==NULL || tmp->left==NULL)return flag;
    return tmp->left->data;
}

template<class T>
T binaryTree<T>::rchild(T x,T flag)const
{
    node *tmp=find(x,root);
    if(tmp==NULL || tmp->right==NULL)return flag;
    return tmp->right->data;
}

template<class T>
void binaryTree<T>::createTree(T flag)
{
    queue<node*> que;
    node *tmp;
    T x,ldata,rdata;
    //创建树，输入flag表是空
    cout<<"\n请输入根节点：";
    cin>>x;
    root = new node(x);
    que.push(root);

    while(!que.empty())
    {
        tmp=que.front();que.pop();
        cout<<"\n请输入 "<<tmp->data<<" 的两个儿子（"<<flag<<"表示空结点）：";
        cin>>ldata>>rdata;
        if(ldata!=flag)que.push(tmp->left = new node(ldata));
        if(rdata!=flag)que.push(tmp->right = new node(rdata));
    }

    cout<<"creat completed!\n";
}

template<class T>
int binaryTree<T>::size()const
{
    return size(root);
}

template<class T>
int binaryTree<T>::size(binaryTree<T>::node *t)const
{
    if(t==NULL)return 0;
    else return 1+size(t->left)+size(t->right);
}

template<class T>
int binaryTree<T>::height()const
{
    return height(root);
}

template<class T>
int binaryTree<T>::height(binaryTree<T>::node *t)const
{
    if(t==NULL)return 0;
    else return 1+(height(t->left) > height(t->right) ? height(t->left) : height(t->right));
}

int main()
{
    binaryTree<char> tree;

    tree.createTree('@');
    tree.preOrder();
    tree.midOrder();
    tree.postOrder();
    tree.levelOrder();
    printTree(tree,'@');
    cout<<tree.size()<<' '<<tree.height();
    tree.delLeft('L');
    tree.delRight('C');
    tree.delLeft('C');
    printTree(tree,'@');
    cout<<tree.size()<<' '<<tree.height();

    return 0;

}
