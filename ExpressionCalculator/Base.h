#ifndef Base
#define Base

#include<stdio.h>

/*---------------------------------------
 ��ͷ�ļ��ж�����һЩ��Ŀ���õ��ı����ͺ���
----------------------------------------*/

/**
**ȫ�ֱ��������ʽ��������ö�٣�
**0:δ�����쳣[no exception]
**1:�Ƿ��ı��ʽ[invalid expression]
**2:��֧�ֵĺ���[unsupported function]
**3:���Ų�ƥ��[unmatched bracket]
**4:��ѧ�߼�����[logic error]
**5:�����������[data overflow]
**/
enum ErrorType{no_exception,invalid_expression,unsupported_function,unmatched_bracket,logic_error,data_overflow}Error=no_exception;

//�쳣��׽
bool CatchException();

//�׳��쳣
void ThrowException();

//�õ��ַ�������
int StrLen(char* str);

//�ַ���copy
char* StrCpy(char* to,const char* from);

//�Լ�д��memset
char* MemSet(char* p,const char ch,int index);

//�Լ�д��strcat
char* StrCat(char* to,const char* from);

//�ж�һ���ַ��Ƿ���һ�����֣�0~9��
bool IsDigit(char ch_digit);

//�����ַ���ʽ������,�������-1,˵����������,��ch_digitΪ�����ָ�ʽ
int ParseDigit(char ch_digit);

//������0~9ת��Ϊ��Ӧ�ַ�,Ĭ��Ϊ���ַ�
char toChar(int digit);

//��str������Ϊindex���ַ��Ƴ�
void RemoveCharAt(char* str,int index);

//���ַ����е���ĸȫ������Сд
void toLowercase(char* str);

//�ַ�������:��frag���뵽body������Ϊindex��λ�ã�body�Ŀռ�һ��Ҫ�㹻����������
void InsertString(char* body,int index,char* frag);

//�ж�һ���ַ��Ƿ���һ��������ɲ��֣�0~9��С���㡰.����-����
bool IsPartOfNumber(char ch);

//�ж�һ���ַ��Ƿ��ǲ�������+��-��*��/��^��!��
bool IsOperator(char* expression,int index);

//�õ����ڲ����ŵ��±�,������ʱ����-1
int GetIndexOfInnermostLeftBracket(char* expression);
int GetIndexOfInnermostRightBracket(char* expression);

//�ж����ڲ������Ǻ������Ż���һ������
bool IsBracketOfFun(char* expression,int IndexOfInnermostLeftBracket,int IndexOfInnermostRightBracket);

//�жϱ��ʽ��start��endƬ���Ƿ���ֻ��������Ͳ��������������������ŵļ򵥱��ʽ
bool IsSimpleExpression(char* expression,int start,int end);

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ�������������±�
int GetStartIndexOfLeftOperand(char* expression,int index_of_operator);

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��Ҳ����������±�
int GetEndIndexOfRightOperand(char* expression,int index_of_operator);

/*--------------------------------
�����Ǳ�ͷ�ļ��������ĸ�������ʵ��
--------------------------------*/

//�쳣��׽
bool CatchException()
{
	return Error!=no_exception;
}

//�׳��쳣
void ThrowException()
{
	switch(Error)
	{
	case invalid_expression:
		printf("����:�Ƿ��ı��ʽ![invalid expression]\n");
		break;
	case unsupported_function:
		printf("����:��֧�ֵĺ���![unsupported function]\n");
		break;
	case unmatched_bracket:
		printf("����:���Ų�ƥ��![unmatched bracket]\n");
		break;
	case logic_error:
		printf("����:��ѧ�߼�����![logic error]\n");
		break;
	case data_overflow:
		printf("����:�����������![data overflow]\n");
		break;
	}
}

//�õ��ַ�������(��'\0'Ϊ������־)
int StrLen(char* str)
{
	int len=0;
	while(str[len]!=0)len++;
	return len;
}

//�ַ���copy
char* StrCpy(char* to,const char* from)
{
	if(to==NULL||from==NULL)
	{
		printf("Invalid argument(s)!");
		return NULL;
	}
	else
	{
		char* dest=to;
		while((*(dest++)=*(from++))!='\0');
		return dest;
	}
}

//�Լ�д��memset
char* MemSet(char* p,const char ch,int index)
{
	int i=index>StrLen(p)?StrLen(p):index;
	while(i>=0)
	{
		p[i]=ch;
		i--;
	}
	return p;
}

//�Լ�д��strcat
char* StrCat(char* to,const char* from)
{
	int len=StrLen(to);
	int i=0;
	while(from[i]!=0)
	{
		to[len+i]=from[i];
		i++;
	}
	to[len+i]=0;
	return to;
}

//�ж�һ���ַ��Ƿ���һ�����֣�0~9��
bool IsDigit(char ch_digit)
{
	if(ch_digit>='0'&&ch_digit<='9')
	{
		return true;
	}
	else
		return false;
}

//�����ַ���ʽ�����֡��������-1��˵����������
int ParseDigit(char ch_digit)
{
	int digit=-1;
	switch(ch_digit)
	{
	case '0':
		digit=0;
		break;
	case '1':
		digit=1;
		break;
	case '2':
		digit=2;
		break;
	case '3':
		digit=3;
		break;
	case '4':
		digit=4;
		break;
	case '5':
		digit=5;
		break;
	case '6':
		digit=6;
		break;
	case '7':
		digit=7;
		break;
	case '8':
		digit=8;
		break;
	case '9':
		digit=9;
		break;
	}
	return digit;
}

//������0~9ת��Ϊ��Ӧ�ַ�,Ĭ��Ϊ���ַ�
char toChar(int digit)
{
	char number=0;
	switch(digit)
	{
	case 0:
		number='0';
		break;
	case 1:
		number='1';
		break;
	case 2:
		number='2';
		break;
	case 3:
		number='3';
		break;
	case 4:
		number='4';
		break;
	case 5:
		number='5';
		break;
	case 6:
		number='6';
		break;
	case 7:
		number='7';
		break;
	case 8:
		number='8';
		break;
	case 9:
		number='9';
		break;
	}
	return number;
}

//��str������Ϊindex���ַ��Ƴ�
void RemoveCharAt(char* str,int index)
{
	int len=StrLen(str);
	for(int i=index;i<len-1;i++)
	{
		str[i]=str[i+1];
	}
	str[len-1]=0;
}

//���ַ����е���ĸȫ������Сд
void toLowercase(char* str)
{
	int len=StrLen(str);
	for(int i=0;i<len;i++)
	{
		if(str[i]>='A'&&str[i]<='Z')
		{
			str[i]+=32;
		}
	}
}

//�ַ�������:��frag���뵽body������Ϊindex��λ�ã�body�Ŀռ�һ��Ҫ�㹻����������
void InsertString(char* body,int index,char* frag)
{
	int body_len=StrLen(body);
	int frag_len=StrLen(frag);
	for(int i=body_len-1;i>=index;i--)
	{
		body[i+frag_len]=body[i];
	}
	for(int j=index,k=0;j<index+frag_len;j++,k++)
	{
		body[j]=frag[k];
	}
}

//�ж�һ���ַ��Ƿ���һ��������ɲ��֣�0~9��С���㡰.����-����
bool IsPartOfNumber(char ch)
{
	if(ch=='.'||ch=='-'||(ch>='0'&&ch<='9'))
	{
		return true;
	}
	else
		return false;
}

//����һ���򵥱��ʽ���ж�һ���ַ��Ƿ��ǲ�������+��-��*��/��^��!��
bool IsOperator(char* expression,int index)
{
	if(index<1)
	{
		return false;
	}
	else
	{
		char ch=expression[index];
		char ch_former=expression[index-1];
		//�򵥱��ʽ�в������ţ����Բ�����ǰ��һ��������'!'
		if((ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='!')&&(IsDigit(ch_former)||ch_former=='!'))
		{
			return true;
		}
		else return false;
	}
}

//�õ����ڲ������ŵ��±�,������ʱ����-1
int GetIndexOfInnermostLeftBracket(char* expression)
{
	int index=-1;
	int len=StrLen(expression);
	int pair=GetIndexOfInnermostRightBracket(expression);
	if(pair>0)
	{
		for(int i=0;i<pair;i++)
		{
			if(expression[i]=='(')
			{
				index=i;
			}
		}
	}
	return index;
}

//�õ����ڲ������ŵ��±�,������ʱ����-1
int GetIndexOfInnermostRightBracket(char* expression)
{
	int index=-1;
	int len=StrLen(expression);
	for(int i=0;i<len;i++)
	{
		if(expression[i]==')')
		{
			index=i;
			break;
		}
	}
	if(index==0)
	{
		Error=invalid_expression;
		ThrowException();
		printf("Bracket was found closed without open!\n");
	}
	return index;
}

//�ж����ڲ������Ǻ������Ż���һ������(�������ŵ�������ǰһ������ĸ)
bool IsBracketOfFun(char* expression,int IndexOfInnermostLeftBracket,int IndexOfInnermostRightBracket)
{
	bool flag=false;
	if(IndexOfInnermostLeftBracket==0)
	{
		flag=false;
	}
	else if(expression[IndexOfInnermostLeftBracket-1]>='a'&&expression[IndexOfInnermostLeftBracket-1]<='z')
	{
		flag=true;
	}
	return flag;
}

//�жϱ��ʽ��start��endƬ���Ƿ���ֻ��������Ͳ��������������������ŵļ򵥱��ʽ
bool IsSimpleExpression(char* expression,int start,int end)
{
	bool flag=true;
	for(int i=start;i<=end;i++)
	{
		if((!IsOperator(expression,i))&&(!IsPartOfNumber(expression[i])))
		{
			flag=false;
			break;
		}
	}
	return flag;
}

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ�������������±�
int GetStartIndexOfLeftOperand(char* expression,int index_of_operator)
{
	int StartIndexOfLeftOperand=index_of_operator-1;
	for(;StartIndexOfLeftOperand>0&&IsPartOfNumber(expression[StartIndexOfLeftOperand-1])&&(!IsOperator(expression,StartIndexOfLeftOperand-1));)
	{
		StartIndexOfLeftOperand--;
	}
	return StartIndexOfLeftOperand;
}

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��Ҳ����������±�
int GetEndIndexOfRightOperand(char* expression,int index_of_operator)
{
	int len=StrLen(expression);
	int EndIndexOfRightOperand=index_of_operator+1;
	for(;(EndIndexOfRightOperand<len-1)&&IsPartOfNumber(expression[EndIndexOfRightOperand+1])&&(!IsOperator(expression,EndIndexOfRightOperand+1));)
	{
		EndIndexOfRightOperand++;
	}
	return EndIndexOfRightOperand;
}
#endif