//括号配对检查
#include <iostream>
#include <stack>
using namespace std;

bool parenMatch(const char *str)
{
    stack<char> s;
    while(*str!='\0')
    {
        switch(*str)
        {
            case '(':s.push(*str);break;
            case ')':
                if(s.empty()){cout<<"An opening bracket '(' is expected!\n";return false;}
                else s.pop();
                break;
        }
        str++;
    }
    if(!s.empty()){cout<<"An closing bracket ')' is expected!\n";return false;}
    return true;
}

int main()
{
    char s[80];
    cin.getline(s,81);
    if(parenMatch(s))
    {
        //运行代码
        cout<<"Right expression"<<endl;
    }
    return 0;
}
