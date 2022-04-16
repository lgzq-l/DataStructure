#include <iostream>
#include <cstring>
#define N 1001
#define M 40000001
#define INF 0x3f3f3f3f

using namespace std;

template<class T>
class linkQueue
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T &x,node *N1 = NULL)
        {
            data=x;
            next=N1;
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

int n,l,r,a[N];
int k,dis[20000];

int ans,ll,rr,t1,t2;

linkQueue<int> Q;
int x,now;
bool vis[20000];

void Exchange(int &a, int &b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}

int Partition(int arr[], int low, int high)
{
    int x, i, j;

    x = arr[high]; 
    i = low - 1;

    for(j = low; j < high; j++)
    if(arr[j] <= x) 
    {
        i = i + 1;
        Exchange(arr[i], arr[j]);
    }
    Exchange(arr[i+1], arr[high]);
    return i+1;
}

// ¿ìËÙÅÅÐòËã·¨
void quickSort(int arr[], int low, int high)
{
    int q;

    if(low < high)
    {
        q = Partition(arr, low, high);
        quickSort(arr, low, q-1);
        quickSort(arr, q+1, high);
    }
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	quickSort(a,1,n);
	k = a[1];
	
	dis[0] = 0;
	for (int i = 1; i < k; ++i) dis[i] = M;
	
	while (!Q.isEmpty()) Q.deQueue();
	Q.enQueue(0);
	
	memset(vis,0,sizeof(vis));
	vis[0] = 1;
	
	while (!Q.isEmpty())
    {
		x = Q.deQueue();
		for (int i = 1; i <= n; ++i)
        {
			now = (x + a[i]) % k;
			if (dis[now] > dis[x] + a[i])
            {
				dis[now] = dis[x] + a[i];
				if (!vis[now]) Q.enQueue(now);
				vis[now] = 1;
			}
		}
		vis[x] = 0;
	}
	
    int m;
	cin>>m;
    while(m--)
    {
        int num;
        cin>>num;
        int i=num % k;
        if(num>=dis[i])cout<<"yes"<<endl;
        else cout<<"NO"<<endl;
    }
	
	return 0;
}
