#ifndef BigIntCal
#define BigIntCal

#include<stdlib.h>
#include"BigIntCalBase.h"

/*-----------------------------------------------------
定义大数结构：用一字符串Num表示大数,
整型数组bitSet将其按位存储(第一位为符号位,0为正,1为负),
bool型isP标记其正负,int型bits存储其位数(不包括符号位)
------------------------------------------------------*/
struct BigInt
{
	char* Num;
	int* bitSet;
	bool isP;
	int bits;
};

//从数字格式的字符串构建一个大数
BigInt CreatBigInt(char* str_BigInt)
{
	BigInt new_BigInt;
	int len=StrLen(str_BigInt);
	new_BigInt.Num=(char*)malloc(sizeof(char)*len);
	StrCpy(new_BigInt.Num,str_BigInt);
	new_BigInt.isP=str_BigInt[0]=='-'?false:true;
	new_BigInt.bits=new_BigInt.isP?len:len-1;
	new_BigInt.bitSet=(int*)malloc(sizeof(int)*(new_BigInt.bits+1));
	new_BigInt.bitSet[0]=new_BigInt.isP?0:1;
	if(new_BigInt.isP)
	{
		for(int i=1;i<new_BigInt.bits+1;i++)
		{
			new_BigInt.bitSet[i]=ParseDigit(str_BigInt[i-1]);
		}
	}
	else
	{
		for(int i=1;i<new_BigInt.bits+1;i++)
		{
			new_BigInt.bitSet[i]=ParseDigit(str_BigInt[i]);
		}
	}
	return new_BigInt;
}

//从表达式指定段解析出一个大数
BigInt ParseBigInt(char* expression,int start,int end)
{
	char* str_BigInt=(char*)malloc(sizeof(char)*(end-start+1));
	for(int i=start,j=0;i<=end;i++,j++)
	{
		str_BigInt[j]=expression[i];
	}
	return CreatBigInt(str_BigInt);
}

//大数克隆函数
BigInt CloneBigInt(BigInt bigInt)
{
	return CreatBigInt(bigInt.Num);
}

//取相反数
BigInt BigInt_opp(BigInt bigInt)
{
	if(bigInt.isP)
	{
		char* Num=(char*)malloc(sizeof(char)*(bigInt.bits+1));
		Num[0]='-';
		for(int i=1;i<bigInt.bits+1;i++)
		{
			Num[i]=bigInt.Num[i-1];
		}
		return CreatBigInt(Num);
	}
	else
	{
		return ParseBigInt(bigInt.Num,1,StrLen(bigInt.Num));
	}
}

//大数的绝对值函数
BigInt BigInt_abs(BigInt bigInt)
{
	if(bigInt.isP)
	{
		return CloneBigInt(bigInt);
	}
	else
	{
		return CloneBigInt(BigInt_opp(bigInt));
	}
}

//大数的绝对值大小比较|BigInt1|>=<|BigInt2|各返回1,0,-1
int BigIntCmpAbs(BigInt BigInt1,BigInt BigInt2)
{
	if(BigInt1.bits>BigInt2.bits)
	{
		return 1;
	}
	else if(BigInt1.bits<BigInt2.bits)
	{
		return -1;
	}
	else
	{
		int bits=BigInt1.bits;
		int* a=(int*)malloc(sizeof(int)*(bits+1));
		int* b=BigInt2.bitSet;
		for(int i=bits;i>=0;i--)
		{
			a[i]=BigInt1.bitSet[i];
		}
		bool equal=true;
		for(int j=bits;j>0;j--)
		{
			if(a[j]!=b[j])
			{
				equal=false;
				break;
			}
		}
		if(equal)
		{
			return 0;
		}
		else
		{
			bool borrow=false;
			for(int k=bits;k>0;k--)
			{
				if(borrow)
				{
					a[k]=a[k]>b[k]?(borrow=false,a[k]-b[k]-1):(a[k]+10-b[k]);
				}
				else
				{
					a[k]=a[k]<b[k]?(borrow=true,a[k]+10-b[k]):(a[k]-b[k]);
				}
			}
			if(borrow)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}
}

//大数的大小比较BigInt1>=<BigInt2各返回1,0,-1
int BigIntCmp(BigInt BigInt1,BigInt BigInt2)
{
	if(BigInt1.isP&&(!BigInt2.isP))
	{
		return 1;
	}
	else if((!BigInt1.isP)&&BigInt2.isP)
	{
		return -1;
	}
	else
	{
		return BigInt1.isP?BigIntCmpAbs(BigInt1,BigInt2):BigIntCmpAbs(BigInt2,BigInt1);
	}	
}

/*------------
大数的四则运算
-------------*/

//两个大数的绝对值之和
BigInt Add_abs(BigInt BigInt1,BigInt BigInt2)
{
	BigInt bigInt1=BigIntCmpAbs(BigInt1,BigInt2)?BigInt_abs(BigInt1):BigInt_abs(BigInt2);
	BigInt bigInt2=BigIntCmpAbs(BigInt1,BigInt2)?BigInt_abs(BigInt2):BigInt_abs(BigInt1);
	int bits_max=bigInt1.bits;
	int bits_min=bigInt2.bits;
	int* a=bigInt1.bitSet;
	int* b=bigInt2.bitSet;
	int* c=(int*)malloc(sizeof(int)*(bits_max+1));
	for(int s=bits_max;s>=0;s--)
	{
		c[s]=0;
	}
	for(int i=bits_max,j=bits_min;j>0;i--,j--)
		{
			c[i]=b[j];
		}
	int carry=0;
	for(int k=bits_max;k>=0;k--)
	{
		c[k]+=a[k]+carry;
		carry=c[k]/10;
		c[k]=c[k]%10;
	}
	char* Num=(char*)malloc(sizeof(char)*(bits_max+1));
	for(int m=0;m<bits_max+1;m++)
	{
		Num[m]=toChar(c[m]);
	}
	TrimRedundantZero(Num);
	return CreatBigInt(Num);
}

//两个大数的绝对值之差(大减小)
BigInt Minus_abs(BigInt BigInt1,BigInt BigInt2)
{
	BigInt bigInt1=BigIntCmpAbs(BigInt1,BigInt2)?BigInt_abs(BigInt1):BigInt_abs(BigInt2);
	BigInt bigInt2=BigIntCmpAbs(BigInt1,BigInt2)?BigInt_abs(BigInt2):BigInt_abs(BigInt1);
	int bits_max=bigInt1.bits;
	int bits_min=bigInt2.bits;
	int* a=bigInt1.bitSet;
	int* b=bigInt2.bitSet;
	int* c=(int*)malloc(sizeof(int)*(bits_max+1));
	for(int s=bits_max;s>=0;s--)
	{
		c[s]=0;
	}
	for(int i=bits_max,j=bits_min;j>0;i--,j--)
		{
			c[i]=b[j];
		}
	bool borrow=false;
	for(int k=bits_max;k>0;k--)
	{
		if(borrow)
		{
			a[k]=a[k]>c[k]?(borrow=false,a[k]+10-c[k]):(a[k]-c[k]);
		}
		else
		{
			a[k]=a[k]<c[k]?(borrow=true,a[k]+10-c[k]):(a[k]-c[k]);
		}
	}
	char* Num=(char*)malloc(sizeof(char)*(bits_max));
	for(int m=0;m<bits_max;m++)
	{
		Num[m]=toChar(a[m+1]);
	}
	TrimRedundantZero(Num);
	return CreatBigInt(Num);
}

//加
BigInt Add(BigInt BigInt1,BigInt BigInt2)
{
	if(BigInt1.isP&&BigInt2.isP)
	{
		return Add_abs(BigInt1,BigInt2);
	}
	else if(BigInt1.isP&&(!BigInt2.isP))
	{
		return BigIntCmpAbs(BigInt1,BigInt2)>0?Minus_abs(BigInt1,BigInt2):BigInt_opp(Minus_abs(BigInt1,BigInt2));
	}
	else if((!BigInt1.isP)&&BigInt2.isP)
	{
		return BigIntCmpAbs(BigInt1,BigInt2)>0?BigInt_opp(Minus_abs(BigInt2,BigInt1)):Minus_abs(BigInt2,BigInt1);
	}
	else
	{
		return BigInt_opp(Add_abs(BigInt1,BigInt2));
	}
}

//减
BigInt Minus(BigInt BigInt1,BigInt BigInt2)
{
	if(BigInt1.isP&&BigInt2.isP)
	{
		return BigIntCmpAbs(BigInt1,BigInt2)>0?Minus_abs(BigInt1,BigInt2):BigInt_opp(Minus_abs(BigInt1,BigInt2));
	}
	else if(BigInt1.isP&&(!BigInt2.isP))
	{
		return Add_abs(BigInt1,BigInt2);
	}
	else if((!BigInt1.isP)&&BigInt2.isP)
	{
		return BigInt_opp(Add_abs(BigInt1,BigInt2));
	}
	else
	{
		return Add(BigInt1,BigInt_opp(BigInt2));
	}
}

//大数的1
BigInt BigInt_0()
{
	char zero[]="0";
	return CreatBigInt(zero);
}

//大数的1
BigInt BigInt_1()
{
	char one[]="1";
	return CreatBigInt(one);
}

//比较取大者
BigInt Max(BigInt BigInt1,BigInt BigInt2)
{
	return BigIntCmp(BigInt1,BigInt2)?BigInt1:BigInt2;
}

//比较取小者
BigInt Min(BigInt BigInt1,BigInt BigInt2)
{
	return BigIntCmp(BigInt1,BigInt2)?BigInt2:BigInt1;
}

//绝对值相乘
BigInt Multiply_abs(BigInt BigInt1,BigInt BigInt2)
{
	BigInt max=Max(BigInt_abs(BigInt1),BigInt_abs(BigInt2));
	BigInt min=Min(BigInt_abs(BigInt1),BigInt_abs(BigInt2));
	int bits=max.bits+min.bits;
	int* a=max.bitSet;
	int* b=min.bitSet;
	int* c=(int*)malloc(sizeof(int)*bits);
	int* d=(int*)malloc(sizeof(int)*(max.bits+1));
	for(int m=0;m<bits;m++)c[m]=0;
	for(int i=min.bits,k=bits-1;i>0;i--,k--)
	{
		for(int j=max.bits,carry=0;j>0;j--)
		{
			d[j]=a[j]*b[i]+carry;
			carry=d[j]/10;
			d[j]%=10;
		}
		d[0]=carry;
		int car=0;
		for(j=max.bits;j>=0;j--)
		{
			int index=k-max.bits+j;
			c[index]+=d[j];
			car=c[index]/10;
			c[index]%=10;
		}
		//c[k-max.bits+j]+=car;
	}
	char* Num=(char*)malloc(sizeof(char)*bits);
	for(int s=0;s<bits;s++)
	{
		//DEBUG
		char ch=toChar(c[s]);
		if(ch!=0)Num[s]=ch;
		else printf("toChar(int) error!");
	}
	return CreatBigInt(Num);
}

//乘
BigInt Multiply(BigInt BigInt1,BigInt BigInt2)
{
	return (BigInt1.isP&&BigInt2.isP)||((!BigInt1.isP)&&(!BigInt2.isP))?Multiply_abs(BigInt1,BigInt2):BigInt_opp(Multiply_abs(BigInt1,BigInt2));
}

//除(只考虑整除)
BigInt Devide(BigInt BigInt1,BigInt BigInt2)
{
	if(BigIntCmpAbs(BigInt1,BigInt2)==0)
	{
		return BigInt_1();
	}
	else if(BigIntCmpAbs(BigInt1,BigInt2)<0)
	{
		return BigInt_0();
	}
	else
	{
		return BigInt1;
	}
}

//乘方
BigInt Pow(BigInt BigInt1,BigInt BigInt2)
{
	BigInt bigInt1=BigInt1;
	BigInt bigInt2=BigInt2;
	while(BigIntCmp(bigInt2,BigInt_1())>0)
	{
		bigInt1=Multiply(bigInt1,bigInt1);
		bigInt2=Minus(bigInt2,BigInt_1());
	}
	return bigInt1;
}

//阶乘
BigInt Fact(BigInt bigInt)
{
	BigInt bigint=bigInt;
	for(BigInt i=Minus(bigInt,BigInt_1());BigIntCmp(i,BigInt_1());Minus(i,BigInt_1()))
	{
		bigint=Multiply(bigint,i);
	}
	return bigint;
}

//输出
void BigIntOut(BigInt bigInt)
{
	printf("%s",bigInt.Num);
}
#endif