//�Ŷ�ϵͳ��ģ��
#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

class simulator{
    int arrivalLow;         //������ʱ������
    int arrivalHigh;        //������ʱ������
    int serviceTimeLow;     //����ʱ������
    int serviceTimeHigh;    //����ʱ������
    int customNum;          //ģ��Ĺ˿���


public:
    simulator();
    int avgWaitTime()const;
};

simulator::simulator()
{
    cout<<"�����뵽��ʱ�������¡��Ͻ磺";
    cin>>arrivalLow>>arrivalHigh;

    cout<<"���������ʱ����¡��Ͻ磺";
    cin>>serviceTimeLow>>serviceTimeHigh;

    cout<<"������ģ��Ĺ˿�����";
    cin>>customNum;

    srand(time(NULL));//��ʼ�������������
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

    //�������е����¼�
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
    cout<<"ƽ���ȴ�ʱ�䣺"<<sim.avgWaitTime()<<endl;

    return 0;
}
