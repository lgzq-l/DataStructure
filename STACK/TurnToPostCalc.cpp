#include <iostream>
#include <stack>
using namespace std;

//计算后缀形式表达式的值
int calcPost(char *str)
{
    int op1,op2,op;
    int tmp,i;
    stack<int> s;

    i=0;
    while(str[i]!='\0')
    {
        if((str[i]>='0') && (str[i]<='9'))//数字转为整数后进栈
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

//求一个表达式的后缀形式
void inToSufForm(char *inStr,char *sufStr)
{
    stack<char> s;
    int i,j;
    char topCh,hash='#';

    s.push(hash);                       //'#'运算级别最低，用于压栈底，便于统一比较,    push接收的最好是一个变量
    i=0;j=0;
    while(inStr[i]!='\0')
    {
        if((inStr[i]>='0')&&(inStr[i]<='9'))sufStr[j++]=inStr[i++];
        else
        {
            switch(inStr[i])
            {
                case '(':s.push(inStr[i]);break;//优先级最高，直接入栈
                case ')'://弹栈，弹出元素进入后缀式，直到弹出一个左括号
                    topCh=s.top();s.pop();
                    while(topCh!='(')
                    {
                        sufStr[j++]=topCh;
                        topCh=s.top();
                        s.pop();
                    }//')'字符不入栈
                    break;
                case '*':
                case '/':
                    topCh=s.top();
                    while((topCh=='*')||(topCh=='/'))//*、/为左结合，后来者优先级低
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
                    while((topCh!='(')&&(topCh!='#'))//只有左括号和垫底优先级比+、-低
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
