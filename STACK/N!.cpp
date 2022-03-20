//阶乘计算的递归和非递归实现
#include <iostream>
#include <stack>
using namespace std;

//递归实现
int f1(int n)
{
    if(n<0)return 0;
    if((n==0)||(n==1))return 1;
    return n*f1(n-1);
}

//非递归实现
int f2(int n)
{
    stack<int> s;
    int m,sum;

    sum=1;
    while(n!=0){s.push(n);n--;}

    while(!s.empty()){m=s.top();s.pop();sum*=m;}

    return sum;
}

int main()
{
    int n;
    cin>>n;

    cout<<f1(n)<<'\t'<<f2(n)<<endl;
    return 0;
}
