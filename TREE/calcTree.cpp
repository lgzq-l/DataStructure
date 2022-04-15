#include <iostream>
#include <cstring>
using namespace std;

class calc
{
    enum Type{DATA,ADD,SUB,MULTI,DIV,OPAREN,CPAREN,EOL};

    struct node
    {
        Type type;
        int data;
        node *lchild,*rchild;

        node(Type t,int d=0,node *lc=NULL,node *rc=NULL)
        {type=t; data=d; lchild=lc; rchild=rc;}
    };

    node *root;

    node *create(char *&s);//从s创建一棵表达式树
    Type getToken(char *&s,int &value);//从s中获取一个语法单位
    int result(node *t);

public:
    calc(char *s){root = create(s);}
    int result()
    {
        if(root==NULL)return 0;
        return result(root);
    }
};

calc::node *calc::create(char *&s)
{
    calc::node *p,*root=NULL;
    Type returnType;
    int value;
    while(*s){
        returnType = calc::getToken(s,value);
        switch(returnType)
        {
            case DATA: case OPAREN:
                if(returnType==DATA)p = new calc::node(DATA,value);
                else p=create(s);
                if(root != NULL)
                    if(root->rchild == NULL)root->rchild = p;
                    else root->rchild->rchild = p;
                break;

            case CPAREN: case EOL: return root;

            case ADD: case SUB:
                if(root == NULL)root = new node(returnType,0,p);
                else root = new node(returnType,0,root);
                break;

            case MULTI: case DIV:
                if(root==NULL)root = new node(returnType,0,p);
                else if(root->type == MULTI || root->type == DIV)
                    root = new node(returnType,0,root);
                else root->rchild = new node(returnType,0,root->rchild);
        }
    }
    return root;
}

calc::Type calc::getToken(char *&s,int &data)
{
    char type;

    while (*s==' ')++s;

    if(*s>='0' && *s<='9')
    {
        data=0;
        while(*s>='0' && *s<='9')
        {
            data=data*10 + *s - '0';
            ++s;
        }
        return DATA;
    }
    
    if(*s=='\0')return EOL;

    type=*s;++s;
    switch(type)
    {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MULTI;
        case '/': return DIV;
        case '(': return OPAREN;
        case ')': return CPAREN;
        default:  return EOL;
    }
}

int calc::result(calc::node *t)
{
    int num1,num2;

    if(t->type == DATA)return t->data;
    num1=result(t->lchild);
    num2=result(t->rchild);
    switch (t->type)
    {
        case ADD:   t->data = num1 + num2;break;
        case SUB:   t->data = num1 - num2;break;
        case MULTI: t->data = num1 * num2;break;
        case DIV:   t->data = num1 / num2;break;
    }
    return t->data;
}

int main()
{
    char *s;
    s = new char[200];
    strcpy(s,"2*3+(1*2*3+6*6)*(2+3)/5+2/2");
    calc exp(s);
    cout<<exp.result()<<endl;
    delete s;
    return 0;
}
