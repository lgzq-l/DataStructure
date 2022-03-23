//排队系统的模拟
#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

class simulator{
    int arrivalLow;         //到达间隔时间下限
    int arrivalHigh;        //到达间隔时间上限
    int serviceTimeLow;     //服务时间下限
    int serviceTimeHigh;    //服务时间上限
    int customNum;          //模拟的顾客数


public:
    simulator();
    int avgWaitTime()const;
};

simulator::simulator()
{
    cout<<"请输入到达时间间隔的下、上界：";
    cin>>arrivalLow>>arrivalHigh;

    cout<<"请输入服务时间的下、上界：";
    cin>>serviceTimeLow>>serviceTimeHigh;

    cout<<"请输入模拟的顾客数：";
    cin>>customNum;

    srand(time(NULL));//初始化随机数发生器
}

int simulator::avgWaitTime()const
{
    int currentTime=0;
    int totalWaitTime=0;
    int eventTime;
    queue<int> customerQueue;
    int i;

    for(i=0;i<customNum;++i)
    {
        currentTime += arrivalLow + (arrivalHigh - arrivalLow+1)*rand()/(RAND_MAX+1);
        customerQueue.push(currentTime);
    }

    //处理所有到达事件
    currentTime=0;
    while(!customerQueue.empty())
    {
        eventTime = customerQueue.front();
        customerQueue.pop();
        if(eventTime < currentTime)
            totalWaitTime += currentTime - eventTime;
        else currentTime = eventTime;
        currentTime += serviceTimeLow + (serviceTimeHigh - serviceTimeLow)*rand()/(RAND_MAX+1);
    }
    return totalWaitTime/customNum;
}

int main()
{
    simulator sim;
    cout<<"平均等待时间："<<sim.avgWaitTime()<<endl;

    return 0;
}
