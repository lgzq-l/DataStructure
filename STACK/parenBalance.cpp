#include<iostream>
#include<fstream>
#include<stack>
using namespace std;

char s0='\0';

class balance
{
private:
    ifstream fin;               //�������ļ���
    int currentLine;             //���ڴ��������
    int Errors;                 //�ѷ��ִ�����

    struct Symbol{char Token;   int TheLine;};      //ջԪ������
    enum CommentType{SlashSlash,SlashStar};         //c++ע����cע��

    //CheckBalance�õ��Ĺ��ߺ���
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

class noFile{};                                     //��������ļ�������ʱ���׳����쳣

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
    char LastChar,Match;                            //LastCharΪ����ķ��ţ�MatchΪջ���ķ���
    
    while(LastChar = GetNextSymbol())               //���ļ��ж������ţ�ֱ���ļ�����
    {
        switch(LastChar)
        {
            case '(': case '[': case '{':           //�������ֿ�����֮һ����ջ
                node.Token=LastChar;
                node.TheLine=currentLine;
                st.push(node);
                break;
            case ')': case ']': case '}':
                if(st.empty())                      //�޶�Ӧ������
                {
                    ++Errors;
                    cout<<"�ڵ�"<<currentLine<<"����һ�������"<<LastChar<<endl;
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
    while(!st.empty())                              //ջ�п����ž�û������������
    {
        ++Errors;
        node=st.top();st.pop();
        cout<<"��"<<node.TheLine<<"�еķ���"<<node.Token<<"��ƥ��\n";
    }
    return Errors;
}

bool balance::CheckMatch(char Symbol1,char Symbol2,int Line1,int Line2)
{
    if(Symbol1=='(' && Symbol2!=')' || Symbol1=='[' && Symbol2!=']' || Symbol1=='{' && Symbol2!='}')
    {
        cout<<"���ֵ�"<<Line2<<"�ķ���"<<Symbol2<<"���"<<Line1<<"�ķ���"<<Symbol1<<"��ƥ��\n";
        return false;
    }
    else return true;
}

char balance::GetNextSymbol()
{
    char ch;
    while(ch=NextChar())
    {
        if(ch=='/')                                             //������ע��
        {
            ch=NextChar();
            if(ch=='*') SkipComment(SlashStar);                //����C����ע��
            else if(ch=='/') SkipComment(SlashSlash);            //����C++����ע��
            else PutBackChar(ch);                               //����ע��
        }
        else if(ch=='\\'|| ch=='"' || ch=='\'')SkipQuote(ch);                //�����ַ��������ַ�������
        else if(ch=='{' || ch=='[' || ch=='(' || ch==')' || ch==']' || ch=='}')return ch;
    }
    return s0;    //�ļ�����
}

char balance::NextChar()
{
    char ch;
    if((ch=fin.get())==EOF)return s0;     //�ļ��������������s0
    if(ch=='\n')++currentLine;              //���뻻�з���\n�����м�����+1
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
        else if(ch=='\\\\')ch=NextChar();         //����ת���ַ�
    }
}

//����ע��
void balance::SkipComment(enum CommentType type)
{
    char ch,flag;
    
    if(type==SlashSlash)                        //����//�����
    {
        while(((ch=NextChar())!=s0)&&(ch!='\n'));     //����������ַ���ֱ�������س�
        return;
    }

    //����/*������*/�����
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
            //û�в���
            cout<<"�������ļ�����";cin>>filename;
            p = new balance(filename);
            result=p->CheckBalance();
            delete p;
            cout<<"��"<<result<<"������"<<endl;
            return 0;
        }
        while(--argc)
        {
            //���μ����Ϊ���������Դ�ļ�
            cout<<"����ļ�"<<*++argv<<endl;
            p = new balance(*argv);
            result=p->CheckBalance();
            delete p;
            cout<<"��"<<result<<"������"<<endl;
        }
    }catch(noFile){cout<<"no such file"<<endl;}

    return 0;
}
