//�𳵳�����������
//ͨ��k�����������𳵳�������򵽴�С�������С�
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
    T getTail(){return rear->data;}
    void enQueue(const T &x);
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


bool putBuffer(linkQueue<int> *buffer,int size,int in)
{
    int avail=-1,max=0;                                 //availΪ����ʵĻ�����кţ�maxΪ�ö���βԪ�صı��

    for(int j=0;j<size;++j)                             //Ѱ�Һ��ʵĶ���
    {
        if(buffer[j].isEmpty())                         //�ҵ��ն��У�����
        {b
            if(avail==-1)avail=j;
        }
        else if(buffer[j].getTail()<in && buffer[j].getTail()>max)
        {
            avail=j;
            max=buffer[j].getTail();
        }
    }

    if(avail!=-1)                                       //������ʵĻ������
    {
        buffer[avail].enQueue(in);
        cout<<in<<"���뻺����"<<avail<<endl;
        return true;
    }
    else
    {
        cout<<"�޿��з���"<<endl;
        return false;
    }
}

void checkBuffer(linkQueue<int> *buffer,int size,int &last)
{
    int j;
    int flag=true;  //��Ԫ�س���

    while(flag){    //����������ж��У������ʵ�Ԫ�س���
        flag=false;
        for(j=0;j<size;++j)
        {   //������ж���
            if(!buffer[j].isEmpty() && buffer[j].getHead()==last+1)
            {   //����
                cout<<"��"<<buffer[j].deQueue()<<"�ӻ�����"<<j<<"�Ƶ�����"<<endl;
                ++last;
                flag=true;
                break;
            }
        }
    }
}

void arrange(int in[],int n,int k)
{
    linkQueue<int> *buffer = new linkQueue<int>[k];     //��ʾk��������
    int last=0;                                         //���������һ�ڳ���ı��

    for(int i=0;i<n;i++)                                //���δ�������ϵĳ���
    {
        if(!putBuffer(buffer,k,in[i]))return;          //�޿��õĻ�����
        checkBuffer(buffer,k,last);
    }
}

int main()
{
    int n,k;
    int *num = new int[n];
    cout<<"��������"<<endl;
    cin>>n;
    cout<<"�������У�"<<endl;
    for(int i=0;i<n;i++)cin>>num[i];
    cout<<"������������"<<endl;
    cin>>k;

    cout<<endl;
    arrange(num,n,k);
    return 0;
}
