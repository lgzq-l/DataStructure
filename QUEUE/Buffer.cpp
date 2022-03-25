//火车车厢重排问题
//通过k条缓冲轨道将火车车厢从无序到从小到大排列。
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
    int avail=-1,max=0;                                 //avail为最合适的缓冲队列号，max为该队列尾元素的编号

    for(int j=0;j<size;++j)                             //寻找合适的队列
    {
        if(buffer[j].isEmpty())                         //找到空队列，备用
        {b
            if(avail==-1)avail=j;
        }
        else if(buffer[j].getTail()<in && buffer[j].getTail()>max)
        {
            avail=j;
            max=buffer[j].getTail();
        }
    }

    if(avail!=-1)                                       //进入合适的缓冲队列
    {
        buffer[avail].enQueue(in);
        cout<<in<<"进入缓冲区"<<avail<<endl;
        return true;
    }
    else
    {
        cout<<"无可行方案"<<endl;
        return false;
    }
}

void checkBuffer(linkQueue<int> *buffer,int size,int &last)
{
    int j;
    int flag=true;  //有元素出队

    while(flag){    //反复检查所有队列，将合适的元素出队
        flag=false;
        for(j=0;j<size;++j)
        {   //检查所有队列
            if(!buffer[j].isEmpty() && buffer[j].getHead()==last+1)
            {   //出队
                cout<<"将"<<buffer[j].deQueue()<<"从缓冲区"<<j<<"移到出轨"<<endl;
                ++last;
                flag=true;
                break;
            }
        }
    }
}

void arrange(int in[],int n,int k)
{
    linkQueue<int> *buffer = new linkQueue<int>[k];     //表示k条缓冲轨道
    int last=0;                                         //出轨上最后一节车厢的编号

    for(int i=0;i<n;i++)                                //依次处理入轨上的车厢
    {
        if(!putBuffer(buffer,k,in[i]))return;          //无可用的缓冲轨道
        checkBuffer(buffer,k,last);
    }
}

int main()
{
    int n,k;
    int *num = new int[n];
    cout<<"车箱数："<<endl;
    cin>>n;
    cout<<"车厢序列："<<endl;
    for(int i=0;i<n;i++)cin>>num[i];
    cout<<"缓冲轨道条数："<<endl;
    cin>>k;

    cout<<endl;
    arrange(num,n,k);
    return 0;
}
