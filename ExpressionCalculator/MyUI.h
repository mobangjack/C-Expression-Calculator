#ifndef MyUI
#define MyUI
#include"DoubleCal.h"
#include"BigIntCal.h"

//显示软件说明
void ShowDocumentation();
//显示操作导航
void ShowNavigation();
//三角函数设置
void AngleSettings();
//精度设置
void PrecisionSettings();
//存档
void Archive(char* data);
//浮点计算
void DoubleCalculation();
//大数计算
void BigIntCalculation();
//用户偏好设置
void PreferenceSettings();
//历史记录
void ShowHistory();


//显示软件说明
void ShowDocumentation()
{
	printf("★★★★★表达式计算器★★★★★\n");
	printf("★★★★★BY:ShuangLuo★★★★★\n\n");
	printf("----------Documentation---------\n\n");
	printf("【软件功能】\n");
	printf("1、解析表达式，可自定义精度\n");
	printf("2、可进行大数运算（暂不支持函数）\n");
	printf("3、可将表达式结果保存到文档，并支持读取\n\n");
	printf("【表达式定义】\n");
	printf("★表达式可以是常数，加+、减-、乘*、除/、平方^、括号()，以及数学函数的组合★\n");
	printf("★表达式中可包含空格★\n");
	printf("★当使用三角函数时，用户可设置当前的三角函数输入是弧度还是角度(默认为弧度)★\n");
	printf("1、数值支持：整数、浮点数和大数，可自定精度\n");
	printf("2、括号支持：()\n");
	printf("3、运算支持：+  -  *  /  ^  !\n");
	printf("4、函数支持：cos(), sin(), tg(), ctg(), abs(), sign(), sqrt(), ln(), sinh(), cosh(), tanh(), coth()\n");
	printf("5、常量支持：PI、E\n\n");
}

//显示操作导航
void ShowNavigation()
{
	printf("★★★★★表达式计算器★★★★★\n");
	printf("★★★★★BY:ShuangLuo★★★★★\n\n");
	printf("-----------Navigation-----------\n\n");
	printf("1:浮点运算\n");
	printf("2:大数运算\n");
	printf("3:偏好设置\n");
	printf("4:历史记录\n");
	printf("0:退出程序\n\n");
}

//三角函数设置
void AngleSettings()
{
	int flag;
	printf("三角函数输入首选项: 1.角度制 2.弧度制（默认）\t");
	while(1)
	{
		setbuf(stdin,NULL);
		scanf("%d",&flag);
		if(flag==1)
		{
			IsRad=false;
			printf("设置成功!当前三角函数输入首选项:角度制\n\n");
			break;
		}
		else if(flag==2)
		{
			IsRad=true;
			printf("设置成功!当前三角函数输入首选项:弧度制\n\n");
			break;
		}
		else
		{
			printf("请选择相应的设置项:\n");
		}
	}
}

//精度设置
void PrecisionSettings()
{
	while(1)
	{
		printf("请输入保留的小数位数(0~16): \t");
		int precision;
		setbuf(stdin,NULL);
		scanf("%d",&precision);
		if(precision>=0&&precision<=16)
		{
			DoubleCalPrecision=precision;
			printf("设置成功!当前精度:%d位小数\n\n",precision);
			break;
		}
		else
		{
			printf("浮点运算只支持0~16位运算精度!\n\n");
		}
	}
}

//存档
void Archive(char *data)
{
	FILE *fp=fopen("c:\\ExpressionCalculator_OutData.txt","a");
	if(fp==NULL)
	{
		printf("文件打开出错!\n\n");
	}
	fputs(data,fp);
	fclose(fp);
	printf("存档成功!数据已保存至c:\\ExpressionCalculator_OutData.txt\n\n");
}

//浮点计算
void DoubleCalculation()
{
	printf("请输入表达式:\n");
	GetExpression();
	printf("您输入的表达式是:\n%s\n",Expression);
	AnalyzeExpression(Expression);
	if(!CatchException())
	{
		printf("解析结果:%s\n",Expression);
		int flag;
		while(1)
		{
			printf("是否需要存档? 1.YES 2.NO\t");
			scanf("%d",&flag);
			if(flag==1)
			{
				char data[500];
				MemSet(data,0,500);
				StrCat(data,OriginalExpression);
				StrCat(data," = ");
				StrCat(data,Expression);
				StrCat(data,"\n");
				Archive(data);
				break;
			}
			else if(flag==2)
			{
				printf("\n");
				break;
			}
		}
	}
}

//大数计算
void BigIntCalculation()
{
	printf("大数运算还在调试当中,敬请期待...\n\n");
}

//用户偏好设置
void PreferenceSettings()
{
	int flag;
	while(1)
	{
		printf("1.三角函数设置\n");
		printf("2.精度设置\n");
		setbuf(stdin,NULL);
		scanf("%d",&flag);
		if(flag==1)
		{
			AngleSettings();
			break;
		}
		else if(flag==2)
		{
			PrecisionSettings();
			break;
		}
		else
		{
			printf("请选择相应的设置项:\n");
		}
	}
}

//历史记录
void ShowHistory()
{
	char ch;
	FILE *fp=fopen("c:\\ExpressionCalculator_OutData.txt","r");
	if(fp==NULL)
	{
		printf("文件打开出错!\n\n");
	}
	else
	{
		printf("历史记录:\n");
		while(!feof(fp))
			if((ch=fgetc(fp))!=EOF)
				putchar(ch);
		fclose(fp);
		while(1)
		{
			printf("\n是否清空? 1:YES 2:NO\t");
			int flag=0;
			setbuf(stdin,NULL);
			scanf("%d",&flag);
			if(flag==1)
			{
				fp=fopen("c:\\ExpressionCalculator_OutData.txt","w");
				if(fp==NULL)
				{
					printf("文件打开出错!\n\n");
				}
				else
				{
					printf("文件已清空!\n\n");
					fclose(fp);
				}
				break;
			}
			else if(flag==2)
			{
				printf("\n");
				break;
			}
		}
	}
}

#endif