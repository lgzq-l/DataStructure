#include <iostream>
using namespace std;

class linkQueue
{
private:
    struct node
    {
        int x;
        int y;
        node *next;
        node(int m,int n,node *N = NULL)
        {
            x=m;y=n;
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
    void enQueue(int m,int n);
    int size()const;
    void deQueue(int &m,int &n);
};

void linkQueue::enQueue(int m,int n)
{
    if(rear==NULL)
        front = rear = new node(m,n);
    else{
        rear->next = new node(m,n);
        rear = rear->next;
    }
}

int linkQueue::size()const
{
    node *tmp=front;
    int n=0;
    while(tmp!=NULL){tmp=tmp->next;n++;}
    return n;
}

void linkQueue::deQueue(int &m,int &n)
{
    node *tmp = front;
    m=front->x; n=front->y;
    front = front->next;
    if(front==NULL)rear=NULL;
    delete tmp;
}

linkQueue::~linkQueue()
{
    node *tmp;
    while(front!=NULL)
    {
        tmp=front;
        front=front->next;
        delete tmp;
    }
}

int main()
{
    int n,m,sum=0;
    cin>>n>>m;
    int **num = new int*[n];
    for(int i=0;i<n;i++)num[i] = new int[m];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            char ch;
            cin>>ch;
            switch (ch)
            {
                case '.':num[i][j]=0;break;
                case 'X':num[i][j]=1;break;
                case 't':{
                    num[i][j]=2;
                    sum++;
                    break;
                    }
            }
        }

    const int dire[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

    int x0,y0;
    cin>>x0>>y0;
    x0--;y0--;

    int **grid = new int*[n];
    for(int i=0;i<n;i++)grid[i] = new int[m];

    int *result = new int[sum];for(int i=0;i<sum;i++)result[i]=0;
    int t=0;

    for(int i=0;i<n;i++)for(int j=0;j<m;j++)grid[i][j]=0;
    grid[x0][y0]=1;
    int ans=0;

    linkQueue q;
    q.enQueue(x0,y0);

    if(num[x0][y0]!=1)
        while(!q.isEmpty())
        {
            int mn=q.size();
            int flag=0;
            while(mn--)
            {
                int x,y;
                q.deQueue(x,y);

                if(num[x][y]==2)
                {
                    result[t++]=ans;
                    if(t==sum){flag=1;break;}
                }

                for(int i=0;i<4;i++)
                {
                    int nx=x+dire[i][0];
                    int ny=y+dire[i][1];
                    if(nx<0||ny<0||nx>=n||ny>=m)continue;
                    if(num[nx][ny]!=1 && grid[nx][ny]==0)
                    {
                        q.enQueue(nx,ny);
                        grid[nx][ny]=1;
                    }
                }
            }
            if(flag)break;
            ans++;
        }

    int max=0;
    for(int i=0;i<t;i++)if(max<result[i])max=result[i];
    if(max)cout<<"maximum distance: "<<max<<endl;
    else cout<<"no treasure can be reached"<<endl;

    delete []result;
    delete []num;
    delete []grid;
    return 0;
}
