#ifndef BigIntCalBase
#define BigIntCalBase

#include"Base.h"

/*--------------------------------
�����Ǳ�ͷ�ļ��������ĸ�����������
--------------------------------*/

//�ڴ��������У����ַ����еķ����ֳɷݽ��й��˴���
void Filter(char* str_BigInt);

//�ڴ��������У��޼��ַ�����ʾ�Ĵ�������Ч����
void TrimRedundantZero(char* str_BigInt);

/*--------------------------------
�����Ǳ�ͷ�ļ��������ĸ�������ʵ��
--------------------------------*/

//�ڴ��������У����ַ����еķ����ֳɷݽ��й��˴���
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

//�ڴ��������У��޼��ַ�����ʾ�Ĵ�������Ч����
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