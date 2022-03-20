#include <iostream>
#include <stack>
using namespace std;

//�����׺��ʽ���ʽ��ֵ
int calcPost(char *str)
{
    int op1,op2,op;
    int tmp,i;
    stack<int> s;

    i=0;
    while(str[i]!='\0')
    {
        if((str[i]>='0') && (str[i]<='9'))//����תΪ�������ջ
        {
            tmp=str[i]-'0';
            s.push(tmp);
        }
        else
        {
            op2=s.top();s.pop(); op1=s.top();s.pop();

            switch(str[i])
            {
                case '*': op=op1*op2;break;
                case '/': op=op1/op2;break;
                case '+': op=op1+op2;break;
                case '-': op=op1-op2;break;
            }
            s.push(op);
        }
        i++;
    }
    op = s.top();s.pop();
    return op;
}

//��һ�����ʽ�ĺ�׺��ʽ
void inToSufForm(char *inStr,char *sufStr)
{
    stack<char> s;
    int i,j;
    char topCh,hash='#';

    s.push(hash);                       //'#'���㼶����ͣ�����ѹջ�ף�����ͳһ�Ƚ�,    push���յ������һ������
    i=0;j=0;
    while(inStr[i]!='\0')
    {
        if((inStr[i]>='0')&&(inStr[i]<='9'))sufStr[j++]=inStr[i++];
        else
        {
            switch(inStr[i])
            {
                case '(':s.push(inStr[i]);break;//���ȼ���ߣ�ֱ����ջ
                case ')'://��ջ������Ԫ�ؽ����׺ʽ��ֱ������һ��������
                    topCh=s.top();s.pop();
                    while(topCh!='(')
                    {
                        sufStr[j++]=topCh;
                        topCh=s.top();
                        s.pop();
                    }//')'�ַ�����ջ
                    break;
                case '*':
                case '/':
                    topCh=s.top();
                    while((topCh=='*')||(topCh=='/'))//*��/Ϊ���ϣ����������ȼ���
                    {
                        s.pop();
                        sufStr[j++]=topCh;
                        topCh=s.top();
                    }
                    s.push(inStr[i]);
                    break;
                case '+':
                case '-':
                    topCh=s.top();
                    while((topCh!='(')&&(topCh!='#'))//ֻ�������ź͵�����ȼ���+��-��
                    {
                        s.pop();
                        sufStr[j++]=topCh;
                        topCh=s.top();
                    }
                    s.push(inStr[i]);
                    break;
            }
            i++;
        }
    }
    topCh=s.top();
    while (topCh!='#')
    {
        s.pop();
        sufStr[j++]=topCh;
        topCh=s.top();
    }
    sufStr[j]='\0';
    int t=0;
    while(sufStr[t]!='\0'){cout<<sufStr[t];t++;}
    cout<<endl;
}


int main()
{
    char ins[80],sufs[80];
    cin.getline(ins,81);
    inToSufForm(ins,sufs);
    cout<<calcPost(sufs)<<endl;
    return 0;
}
