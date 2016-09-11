#ifndef BigIntCalBase
#define BigIntCalBase

#include"Base.h"

/*--------------------------------
以下是本头文件所包含的各函数的声明
--------------------------------*/

//在大数运算中，对字符串中的非数字成份进行过滤处理
void Filter(char* str_BigInt);

//在大数运算中，修剪字符串表示的大数的无效的零
void TrimRedundantZero(char* str_BigInt);

/*--------------------------------
以下是本头文件所包含的各函数的实现
--------------------------------*/

//在大数运算中，对字符串中的非数字成份进行过滤处理
void Filter(char* str_BigInt)
{
	int len=StrLen(str_BigInt);
	int start=0;
	if(str_BigInt[0]=='-')
	{
		start=1;
	}
	for(int i=start;i<len;i++)
	{
		if(!IsDigit(str_BigInt[i]))
		{
			RemoveCharAt(str_BigInt,i);
		}
	}
}

//在大数运算中，修剪字符串表示的大数的无效的零
void TrimRedundantZero(char* str_BigInt)
{
	int start=str_BigInt[0]=='-'?1:0;
	while(1)
	{
		if(str_BigInt[start]=='0')RemoveCharAt(str_BigInt,start);
		else break;
	}
}
#endif