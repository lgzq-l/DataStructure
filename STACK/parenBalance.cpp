#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

char s0='\0';

class balance
{
private:
    ifstream fin;               //待检查的文件流
    int currentLine;             //正在处理的行数
    int Errors;                 //已发现错误数

    struct Symbol{char Token;   int TheLine;};      //栈元素类型
    enum CommentType{SlashSlash,SlashStar};         //c++注释与c注释

    //CheckBalance用到的工具函数
    bool CheckMatch(char Symbol1,char Symbol2,int Line1,int Line2);
    char GetNextSymbol();
    void PutBackChar(char ch);
    void SkipComment(enum CommentType type);
    void SkipQuote(char type);
    char NextChar();

public:
    balance(const char *s);
    int CheckBalance();
};

class noFile{};                                     //当输入的文件不存在时，抛出此异常

balance::balance(const char *s)
{
    fin.open(s);
    if(!fin.is_open()) throw noFile();

    currentLine=1;
    Errors=0;
}

int balance::CheckBalance()
{
    Symbol node;
    stack<Symbol> st;
    char LastChar,Match;                            //LastChar为读入的符号，Match为栈顶的符号
    
    while(LastChar = GetNextSymbol())               //从文件中读入括号，直到文件结束
    {
        switch(LastChar)
        {
            case '(': case '[': case '{':           //若是三种开括号之一，进栈
                node.Token=LastChar;
                node.TheLine=currentLine;
                st.push(node);
                break;
            case ')': case ']': case '}':
                if(st.empty())                      //无对应左括号
                {
                    ++Errors;
                    cout<<"在第"<<currentLine<<"行有一个多余的"<<LastChar<<endl;
                }
                else
                {
                    node=st.top();st.pop();
                    Match=node.Token;
                    if(!CheckMatch(Match,LastChar,node.TheLine,currentLine))++Errors;
                }
                break;
        }
    }
    while(!st.empty())                              //栈中开括号均没有遇到闭括号
    {
        ++Errors;
        node=st.top();st.pop();
        cout<<"第"<<node.TheLine<<"行的符号"<<node.Token<<"不匹配\n";
    }
    return Errors;
}

bool balance::CheckMatch(char Symbol1,char Symbol2,int Line1,int Line2)
{
    if(Symbol1=='(' && Symbol2!=')' || Symbol1=='[' && Symbol2!=']' || Symbol1=='{' && Symbol2!='}')
    {
        cout<<"发现第"<<Line2<<"的符号"<<Symbol2<<"与第"<<Line1<<"的符号"<<Symbol1<<"不匹配\n";
        return false;
    }
    else return true;
}

char balance::GetNextSymbol()
{
    char ch;
    while(ch=NextChar())
    {
        if(ch=='/')                                             //可能是注释
        {
            ch=NextChar();
            if(ch=='*') SkipComment(SlashStar);                //处理C风格的注释
            else if(ch=='/') SkipComment(SlashSlash);            //处理C++风格的注释
            else PutBackChar(ch);                               //不是注释
        }
        else if(ch=='\\'|| ch=='"' || ch=='\'')SkipQuote(ch);                //处理字符常量或字符串常量
        else if(ch=='{' || ch=='[' || ch=='(' || ch==')' || ch==']' || ch=='}')return ch;
    }
    return s0;    //文件结束
}

char balance::NextChar()
{
    char ch;
    if((ch=fin.get())==EOF)return s0;     //文件读入结束，返回s0
    if(ch=='\n')++currentLine;              //读入换行符‘\n’，行计数器+1
    return ch;
}

void balance::PutBackChar(char ch)
{
    fin.putback(ch);
    if(ch=='\n')--currentLine;
}

void balance::SkipQuote(char type)
{
    char ch;
    while((ch=NextChar()))
    {
        if(ch==type) return;
        else if(ch=='\n')
        {
            Errors++;
            cout<<"Missing closing quote at line "<<currentLine<<endl;
            return;
        }
        else if(ch=='\\\\')ch=NextChar();         //跳过转义字符
    }
}

//跳过注释
void balance::SkipComment(enum CommentType type)
{
    char ch,flag;
    
    if(type==SlashSlash)                        //处理//的情况
    {
        while(((ch=NextChar())!=s0)&&(ch!='\n'));     //跳过读入的字符，直到读到回车
        return;
    }

    //处理/*···*/的情况
    flag=' ';
    while((ch=NextChar())!=s0)
    {
        if(flag=='*' && ch=='/')return;
        flag=ch;
    }
    ++Errors;
    cout<<"Comment is unterminated!"<<endl;
}

int main(int argc,const char **argv)
{
    char filename[80];
    balance *p;
    int result;


    try{
        if(argc==1)
        {
            //没有参数
            cout<<"请输入文件名：";cin>>filename;
            p = new balance(filename);
            result=p->CheckBalance();
            delete p;
            cout<<"共"<<result<<"个错误"<<endl;
            return 0;
        }
        while(--argc)
        {
            //依次检查作为参数传入的源文件
            cout<<"检查文件"<<*++argv<<endl;
            p = new balance(*argv);
            result=p->CheckBalance();
            delete p;
            cout<<"共"<<result<<"个错误"<<endl;
        }
    }catch(noFile){cout<<"no such file"<<endl;}

    return 0;
}
