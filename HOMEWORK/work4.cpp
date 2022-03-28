#include <iostream>
#define M 100000007
using namespace std;

int main()
{
    long long i;long long n;
    cin>>n;
    long long *f = new long long[n+4];
    long long *A = new long long[n+4];
    f[3]=1;A[1]=1;A[0]=1;
    for(i=2;i<n+3;i++)A[i]=((M-M/i)*A[M%i])%M;
    for(i=3;i<n+3;i++)
    {
        f[i+1]=(4*i-6)%M;
        f[i+1]=f[i+1]*f[i]%M;
        long long k=A[i];
        f[i+1]=(f[i+1]*k)%M;
    }
    cout<<f[n+3]<<endl;
    delete []f;
    delete []A;
    return 0;
}
