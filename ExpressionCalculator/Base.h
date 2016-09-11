#ifndef Base
#define Base

#include<stdio.h>

/*---------------------------------------
 此头文件中定义了一些项目中用到的变量和函数
----------------------------------------*/

/**
**全局变量：表达式错误类型枚举：
**0:未发现异常[no exception]
**1:非法的表达式[invalid expression]
**2:不支持的函数[unsupported function]
**3:括号不匹配[unmatched bracket]
**4:数学逻辑错误[logic error]
**5:数据溢出错误[data overflow]
**/
enum ErrorType{no_exception,invalid_expression,unsupported_function,unmatched_bracket,logic_error,data_overflow}Error=no_exception;

//异常捕捉
bool CatchException();

//抛出异常
void ThrowException();

//得到字符串长度
int StrLen(char* str);

//字符串copy
char* StrCpy(char* to,const char* from);

//自己写的memset
char* MemSet(char* p,const char ch,int index);

//自己写的strcat
char* StrCat(char* to,const char* from);

//判断一个字符是否是一个数字（0~9）
bool IsDigit(char ch_digit);

//解析字符形式的数字,如果返回-1,说明解析有误,即ch_digit为非数字格式
int ParseDigit(char ch_digit);

//把数字0~9转换为相应字符,默认为空字符
char toChar(int digit);

//把str中索引为index的字符移除
void RemoveCharAt(char* str,int index);

//把字符串中的字母全部换成小写
void toLowercase(char* str);

//字符串插入:把frag插入到body中索引为index的位置（body的空间一定要足够，否则会出错）
void InsertString(char* body,int index,char* frag);

//判断一个字符是否是一个数的组成部分（0~9或小数点“.”或“-”）
bool IsPartOfNumber(char ch);

//判断一个字符是否是操作符（+、-、*、/、^、!）
bool IsOperator(char* expression,int index);

//得到最内层括号的下标,无括号时返回-1
int GetIndexOfInnermostLeftBracket(char* expression);
int GetIndexOfInnermostRightBracket(char* expression);

//判断最内层括号是函数括号还是一般括号
bool IsBracketOfFun(char* expression,int IndexOfInnermostLeftBracket,int IndexOfInnermostRightBracket);

//判断表达式从start到end片段是否是只含运算符和操作数，不含函数和括号的简单表达式
bool IsSimpleExpression(char* expression,int start,int end);

//对简单表达式片段中的二元运算符，得到左操作数最左下标
int GetStartIndexOfLeftOperand(char* expression,int index_of_operator);

//对简单表达式片段中的二元运算符，得到右操作数最右下标
int GetEndIndexOfRightOperand(char* expression,int index_of_operator);

/*--------------------------------
以下是本头文件所包含的各函数的实现
--------------------------------*/

//异常捕捉
bool CatchException()
{
	return Error!=no_exception;
}

//抛出异常
void ThrowException()
{
	switch(Error)
	{
	case invalid_expression:
		printf("错误:非法的表达式![invalid expression]\n");
		break;
	case unsupported_function:
		printf("错误:不支持的函数![unsupported function]\n");
		break;
	case unmatched_bracket:
		printf("错误:括号不匹配![unmatched bracket]\n");
		break;
	case logic_error:
		printf("错误:数学逻辑错误![logic error]\n");
		break;
	case data_overflow:
		printf("错误:数据溢出错误![data overflow]\n");
		break;
	}
}

//得到字符串长度(以'\0'为结束标志)
int StrLen(char* str)
{
	int len=0;
	while(str[len]!=0)len++;
	return len;
}

//字符串copy
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

//自己写的memset
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

//自己写的strcat
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

//判断一个字符是否是一个数字（0~9）
bool IsDigit(char ch_digit)
{
	if(ch_digit>='0'&&ch_digit<='9')
	{
		return true;
	}
	else
		return false;
}

//解析字符形式的数字。如果返回-1，说明解析有误
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

//把数字0~9转换为相应字符,默认为空字符
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

//把str中索引为index的字符移除
void RemoveCharAt(char* str,int index)
{
	int len=StrLen(str);
	for(int i=index;i<len-1;i++)
	{
		str[i]=str[i+1];
	}
	str[len-1]=0;
}

//把字符串中的字母全部换成小写
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

//字符串插入:把frag插入到body中索引为index的位置（body的空间一定要足够，否则会出错）
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

//判断一个字符是否是一个数的组成部分（0~9或小数点“.”或“-”）
bool IsPartOfNumber(char ch)
{
	if(ch=='.'||ch=='-'||(ch>='0'&&ch<='9'))
	{
		return true;
	}
	else
		return false;
}

//对于一个简单表达式，判断一个字符是否是操作符（+、-、*、/、^、!）
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
		//简单表达式中不含括号，所以操作符前面一定是数或'!'
		if((ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='!')&&(IsDigit(ch_former)||ch_former=='!'))
		{
			return true;
		}
		else return false;
	}
}

//得到最内层左括号的下标,无括号时返回-1
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

//得到最内层右括号的下标,无括号时返回-1
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

//判断最内层括号是函数括号还是一般括号(函数括号的左括号前一定是字母)
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

//判断表达式从start到end片段是否是只含运算符和操作数，不含函数和括号的简单表达式
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

//对简单表达式片段中的二元运算符，得到左操作数最左下标
int GetStartIndexOfLeftOperand(char* expression,int index_of_operator)
{
	int StartIndexOfLeftOperand=index_of_operator-1;
	for(;StartIndexOfLeftOperand>0&&IsPartOfNumber(expression[StartIndexOfLeftOperand-1])&&(!IsOperator(expression,StartIndexOfLeftOperand-1));)
	{
		StartIndexOfLeftOperand--;
	}
	return StartIndexOfLeftOperand;
}

//对简单表达式片段中的二元运算符，得到右操作数最右下标
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