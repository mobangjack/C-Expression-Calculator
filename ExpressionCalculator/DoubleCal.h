#ifndef DoubleCal
#define DoubleCal

#include"DoubleCalBase.h"
#include<math.h>

#define PI 3.1415926
#define E 2.71828

//ȫ�ֱ�����ԭʼ���ʽ
char OriginalExpression[500];
//ȫ�ֱ���������������̵ı��ʽ
char Expression[500];

//ȫ�ֱ���������
int DoubleCalPrecision=3;

//ȫ�ֱ��������ȱ�־
bool IsRad=true;

/***************************************************/
/*********��ͷ�ļ��а��������к�����������**********/
/***************************************************/

//�õ����ʽ
void GetExpression();

//��ʽ����ȥ�����ʽ�еĿո�
void Format(char* expression);

//�ѱ��ʽ�еĳ����滻����
void ReplaceConstSym(char* expression);

//�����ַ�����ʽ������:start��end�ֱ�Ϊstr����Ҫ��������ʼλ�ú���ֹλ��
long ParseInt(char* str,int start,int end);

//�����ַ�����ʽ��С��:start��end�ֱ�Ϊstr����Ҫ��������ʼλ�ú���ֹλ��
double ParseDouble(char* str,int start,int end);

//������ʽ�еļ򵥺���������ֵ�滻ԭ���ĺ���
void SolveFun(char* expression,int LeftBracketIndex,int RightBracketIndex);

//�жϱ��ʽָ�����Ƿ���ֻ��������Ͳ��������������������ŵļ򵥱��ʽ
bool IsSimpleExpression(char* expression,int start,int end);

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��������
double GetLeftOperand(char* expression,int index_of_operator);

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��Ҳ�����
double GetRightOperand(char* expression,int index_of_operator);

//�����򵥱��ʽ��ֻ��������Ͳ��������������������ţ�
void AnalyzeSimpleExpression(char* expression,int start,int end);

//�������ʽ
void AnalyzeExpression(char* expression);

/***************************************************/
/********************������ʵ��*********************/
/***************************************************/

//�õ����ʽ
void GetExpression()
{
	//��ջ�����
	setbuf(stdin,NULL);
	gets(Expression);
	StrCpy(OriginalExpression,Expression);
	Format(Expression);
}

//��ʽ����ȥ�����ʽ�еĿո�
void Format(char* expression)
{
	int len=StrLen(expression);
	for(int i=0;i<len;i++)
	{
		if(expression[i]==' ')
		{
			RemoveCharAt(expression,i);
			i--;
			len--;
		}
	}
}

//�ѱ��ʽ�еĳ����滻������֧�ֵĳ�����E,PI
void ReplaceConstSym(char* expression)
{
	int len=StrLen(expression);
	for(int i=0;i<len;i++)
	{
		if(expression[i]=='E')
		{
			expression[i]=' ';
			InsertString(expression,i,"2.71828");
			Format(expression);
		}
		if(expression[i]=='P'&&expression[i+1]=='I')
		{
			expression[i]=' ';
			expression[i+1]=' ';
			InsertString(expression,i,"3.1415926");
			Format(expression);
		}
		len=StrLen(expression);
	}
}

//�����ַ�����ʽ������:start��end�ֱ�Ϊstr����Ҫ��������ʼλ�ú���ֹλ��
long ParseInt(char* str,int start,int end)
{
	long result=0;
	int weight=1;
	if(str[start]=='-')
	{
		for(int i=end;i>start;i--)
		{
			int digit=ParseDigit(str[i]);
			if(digit<0)
			{
				Error=invalid_expression;
				ThrowException();
				break;
			}
			else
			{
				result+=digit*weight;
				weight*=10;
			}
		}
		return (-1)*result;
	}
	else
	{
		for(int i=end;i>=start;i--)
		{
			int digit=ParseDigit(str[i]);
			if(digit<0)
			{
				Error=invalid_expression;
				ThrowException();
				break;
			}
			else
			{
				result+=digit*weight;
				weight*=10;
			}
		}
		return result;
	}
	
}

//�����ַ�����ʽ��С��:start��end�ֱ�Ϊstr����Ҫ��������ʼλ�ú���ֹλ��
double ParseDouble(char* str,int start,int end)
{
	long Integer=0;
	double Decimal=0;
	double result=0;
	int IndexOfDot=start;
	for(int index=start;index<=end;index++)
	{
		if(str[index]=='.')
		{
			IndexOfDot=index;
			break;
		}
	}
	if(IndexOfDot==start)
	{
		Integer=ParseInt(str,start,end);
		result=Integer+Decimal;
	}
	else
	{
		int i=0;
		int int_weight=1;
		double double_weight=0.1;
		if(str[start]=='-')
		{
			for(i=IndexOfDot-1;i>start;i--)
			{
				int digit=ParseDigit(str[i]);
				if(digit<0)
				{
					Error=invalid_expression;
					ThrowException();
					break;
				}
				else
				{
					Integer+=digit*int_weight;
					int_weight*=10;
				}
			}
			for(i=IndexOfDot+1;i<=end;i++)
			{
				int digit=ParseDigit(str[i]);
				if(digit<0)
				{
					Error=invalid_expression;
					ThrowException();
					break;
				}
				else
				{
					Decimal+=double_weight*digit;
					double_weight*=0.1;
				}
			}
			result=(-1)*(Integer+Decimal);
		}
		else
		{
			for(i=IndexOfDot-1;i>=start;i--)
			{
				int digit=ParseDigit(str[i]);
				if(digit<0)
				{
					Error=invalid_expression;
					ThrowException();
					break;
				}
				else
				{
					Integer+=digit*int_weight;
					int_weight*=10;
				}
			}
			for(i=IndexOfDot+1;i<=end;i++)
			{
				int digit=ParseDigit(str[i]);
				if(digit<0)
				{
					Error=invalid_expression;
					ThrowException();
					break;
				}
				else
				{
					Decimal+=double_weight*digit;
					double_weight*=0.1;
				}
			}
			result=Integer+Decimal;
		}
		
	}
	return result;
}

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��������
double GetLeftOperand(char* expression,int index_of_operator)
{
	return ParseDouble(expression,GetStartIndexOfLeftOperand(expression,index_of_operator),index_of_operator-1);
}

//�Լ򵥱��ʽƬ���еĶ�Ԫ��������õ��Ҳ�����
double GetRightOperand(char* expression,int index_of_operator)
{
	return ParseDouble(expression,index_of_operator+1,GetEndIndexOfRightOperand(expression,index_of_operator));
}

/**************����򵥱��ʽ�еĺ���ֵ������ֵ�滻ԭ���ĺ���*******************/
/*֧�ֵĺ���:sin(),cos(),tg(),ctg(),sinh(),cosh(),tanh(),coth(),abs(),sign(),sqrt(),ln()*/
void SolveFun(char* expression,int LeftBracketIndex,int RightBracketIndex)
{
	bool isFunRecognized=true;
	int fun_start=LeftBracketIndex-1;
	int fun_end=RightBracketIndex;
	double para=ParseDouble(expression,LeftBracketIndex+1,RightBracketIndex-1);
	double value=0;
	
	//�ҵ���������ʼ�±�
	for(int i=fun_start;i>=0;i--)
	{
		if(expression[i]>'a'&&expression[i]<'z')
		{
			fun_start=i;
		}
		else break;
	}
	//sin
	if(expression[fun_start]=='s'&&expression[fun_start+1]=='i'&&expression[fun_start+2]=='n')
	{
		if(!IsRad)
		{
			para=para*3.141592653589793/180;
		}
		value=sin(para);
	}
	//cos
	else if(expression[fun_start]=='c'&&expression[fun_start+1]=='o'&&expression[fun_start+2]=='s')
	{
		if(!IsRad)
		{
			para=para*3.141592653589793/180;
		}
		value=cos(para);
	}	
	//tg
	else if(expression[fun_start]=='t'&&expression[fun_start+1]=='g')
	{
		if(!IsRad)
		{
			para=para*3.141592653589793/180;
		}
		value=tan(para);
	}
	//ctg
	else if(expression[fun_start]=='c'&&expression[fun_start+1]=='t'&&expression[fun_start+2]=='g')
	{
		if(!IsRad)
		{
			para=para*3.141592653589793/180;
		}
		if(para==0)
		{
			Error=data_overflow;
			ThrowException();
		}
		else value=1/tan(para);
	}
	//cosh
	else if(expression[fun_start]=='c'&&expression[fun_start+1]=='o'&&expression[fun_start+2]=='s'&&expression[fun_start+3]=='h')
	{
		value=cosh(para);
	}
	//sinh
	else if(expression[fun_start]=='s'&&expression[fun_start+1]=='i'&&expression[fun_start+2]=='n'&&expression[fun_start+3]=='h')
	{
		value=sinh(para);
	}
	//tanh
	else if(expression[fun_start]=='t'&&expression[fun_start+1]=='a'&&expression[fun_start+2]=='n'&&expression[fun_start+3]=='h')
	{
		value=tanh(para);
	}
	//coth
	else if(expression[fun_start]=='c'&&expression[fun_start+1]=='o'&&expression[fun_start+2]=='t'&&expression[fun_start+3]=='h')
	{
		if(para==0)
		{
			Error=data_overflow;
			ThrowException();
		}
		else value=cosh(para)/sinh(para);
	}
	//abs
	else if(expression[fun_start]=='a'&&expression[fun_start+1]=='b'&&expression[fun_start+2]=='s'&&expression[fun_start+3]=='s')
	{
		value=fabs(para);
	}
	//sign
	else if(expression[fun_start]=='s'&&expression[fun_start+1]=='i'&&expression[fun_start+2]=='g'&&expression[fun_start+3]=='n')
	{
		if(para>0)
		{
			value=1;
		}
		else if(para==0)
		{
			value=0;
		}
		else
		{
			value=-1;
		}
	}
	//sqrt
	else if(expression[fun_start]=='s'&&expression[fun_start+1]=='q'&&expression[fun_start+2]=='r'&&expression[fun_start+3]=='t')
	{
		if(para<0)
		{
			Error=logic_error;
			ThrowException();
		}
		else value=sqrt(para);
	}
	//ln
	else if(expression[fun_start]=='l'&&expression[fun_start+1]=='n')
	{
		if(para<=0)
		{
			Error=logic_error;
			ThrowException();
		}
		else value=log(para);
	}
	else
	{
		isFunRecognized=false;
		Error=unsupported_function;
		ThrowException();
	}
	if(isFunRecognized&&!CatchException())
	{
		char buffer[50];
		sprintf_by_precision(buffer,value,DoubleCalPrecision);
		for(int k=fun_start;k<=RightBracketIndex;k++)
		{
			expression[k]=' ';
		}
		InsertString(expression,fun_start,buffer);
		Format(expression);
	}
}

//�����򵥱��ʽ��ֻ��������Ͳ��������������������ţ�
void AnalyzeSimpleExpression(char* expression,int start,int end)
{
	char buffer[50];
	int new_start=start;
	int new_end=end;
	for(int i=start;i<=new_end;i++)
	{
		if(IsOperator(expression,i))
		{
			if(expression[i]=='!')
			{
				int start_index_of_operand=GetStartIndexOfLeftOperand(expression,i);
				int end_index_of_operand=i-1;
				double n=ParseInt(expression,start_index_of_operand,end_index_of_operand);
				if(n<0)
				{
					Error=logic_error;
					ThrowException();
					printf("The operand of \'!\' must be none-negative!");
				}
				else
				{
					double value=1;
					while(n>1)
					{
						value*=n;
						n--;
					}
					sprintf_by_precision(buffer,value,DoubleCalPrecision);
					for(int j=start_index_of_operand;j<=i;j++)
					{
						expression[j]=' ';
					}
					InsertString(expression,start_index_of_operand,buffer);
					Format(expression);
					/**DEBUG
					**printf("expression=%s\n",expression);
					**/
					i=start;
					new_end=new_end+StrLen(buffer)-(i-start_index_of_operand+1);
				}
			}
		}
	}
	for(i=start;i<=new_end;i++)
	{
		if(IsOperator(expression,i))
		{
			if(expression[i]=='^')
			{
				int start_index_of_left_operand=GetStartIndexOfLeftOperand(expression,i);
				int end_index_of_right_operand=GetEndIndexOfRightOperand(expression,i);
				double LeftOperand=GetLeftOperand(expression,i);
				double RightOperand=GetRightOperand(expression,i);
				double value=pow(LeftOperand,RightOperand);
				sprintf_by_precision(buffer,value,DoubleCalPrecision);
				if(LeftOperand==0,RightOperand<0)
				{
					Error=logic_error;
					ThrowException();
				}
				if(!CatchException())
				{
					for(int j=start_index_of_left_operand;j<=end_index_of_right_operand;j++)
					{
						expression[j]=' ';
					}
					InsertString(expression,start_index_of_left_operand,buffer);
					Format(expression);
					printf("expression=%s\n",expression);
					i=start;
					new_end=new_end+StrLen(buffer)-(end_index_of_right_operand-start_index_of_left_operand+1);
				}
			}
		}
	}
	for(i=start;i<=new_end;i++)
	{
		if(IsOperator(expression,i))
		{
			if(expression[i]=='*'||expression[i]=='/')
			{
				int start_index_of_left_operand=GetStartIndexOfLeftOperand(expression,i);
				int end_index_of_right_operand=GetEndIndexOfRightOperand(expression,i);
				double LeftOperand=GetLeftOperand(expression,i);
				double RightOperand=GetRightOperand(expression,i);
				double value=0;
				if(expression[i]=='*')
				{
					value=LeftOperand*RightOperand;
				}
				if(expression[i]=='/')
				{
					if(RightOperand==0)
					{
						Error=logic_error;
						ThrowException();
						printf("Zero can not be a divider!\n");
					}
					else value=LeftOperand/RightOperand;
				}
				/**DEBUG
				printf("LeftOperand=%lf\n",LeftOperand);
				printf("RightOperand=%lf\n",RightOperand);
				printf("value=%lf\n",value);
				*/
				sprintf_by_precision(buffer,value,DoubleCalPrecision);
				if(!CatchException())
				{
					for(int j=start_index_of_left_operand;j<=end_index_of_right_operand;j++)
					{
						expression[j]=' ';
					}
					InsertString(expression,start_index_of_left_operand,buffer);
					Format(expression);
					i=start;
					new_end=new_end+StrLen(buffer)-(end_index_of_right_operand-start_index_of_left_operand+1);
				}
			}
		}
	}
	for(i=start;i<=new_end;i++)
	{
		if(IsOperator(expression,i))
		{
			if(expression[i]=='+'||expression[i]=='-')
			{
				int start_index_of_left_operand=GetStartIndexOfLeftOperand(expression,i);
				int end_index_of_right_operand=GetEndIndexOfRightOperand(expression,i);
				double LeftOperand=GetLeftOperand(expression,i);
				double RightOperand=GetRightOperand(expression,i);
				double value=0;
				if(expression[i]=='+')
				{
					value=LeftOperand+RightOperand;
				}
				if(expression[i]=='-')
				{
					value=LeftOperand-RightOperand;
				}
				/**DEBUG
				printf("LeftOperand=%lf\n",LeftOperand);
				printf("RightOperand=%lf\n",RightOperand);
				printf("value=%lf\n",value);
				*/

				sprintf_by_precision(buffer,value,DoubleCalPrecision);
				for(int j=start_index_of_left_operand;j<=end_index_of_right_operand;j++)
				{
					expression[j]=' ';
				}
				InsertString(expression,start_index_of_left_operand,buffer);
				Format(expression);
				//printf("expression=%s\n",expression);
				i=start;
				new_end=new_end+StrLen(buffer)-(end_index_of_right_operand-start_index_of_left_operand+1);
			}
		}
	}
}

//�������ʽ
void AnalyzeExpression(char* expression)
{
	Format(expression);
	ReplaceConstSym(expression);
	toLowercase(expression);
	while(!IsSimpleExpression(expression,0,StrLen(expression)-1))
	{
		//���Ų�ƥ��
		if(GetIndexOfInnermostLeftBracket(expression)*GetIndexOfInnermostRightBracket(expression)<0)
		{
			Error=unmatched_bracket;
			ThrowException();
			break;
		}
		//���ʽ�Ƿ�
		if(GetIndexOfInnermostLeftBracket(expression)<0&&GetIndexOfInnermostRightBracket(expression)<0)
		{
			Error=invalid_expression;
			ThrowException();
			printf("It seems that you\'ve made some mistakes.Please check it!\n");
			break;
		}
		
		AnalyzeSimpleExpression(expression,GetIndexOfInnermostLeftBracket(expression)+1,GetIndexOfInnermostRightBracket(expression)-1);
		if(!IsSimpleExpression(expression,GetIndexOfInnermostLeftBracket(expression)+1,GetIndexOfInnermostRightBracket(expression)-1))
		{
			Error=invalid_expression;
			ThrowException();
			break;
		}
		if(IsBracketOfFun(expression,GetIndexOfInnermostLeftBracket(expression),GetIndexOfInnermostRightBracket(expression)))
		{
			SolveFun(expression,GetIndexOfInnermostLeftBracket(expression),GetIndexOfInnermostRightBracket(expression));
			if(CatchException())break;
		}
		else
		{
			expression[GetIndexOfInnermostLeftBracket(expression)]=' ';
			expression[GetIndexOfInnermostRightBracket(expression)]=' ';
			Format(expression);
		}
	}
	if(!CatchException())
	{
		AnalyzeSimpleExpression(expression,0,StrLen(expression)-1);
	}
	else
	{
		printf("���ʽ����,����ʧ��!\n\n");;
	}
}

#endif
