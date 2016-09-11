#ifndef MyUI
#define MyUI
#include"DoubleCal.h"
#include"BigIntCal.h"

//��ʾ���˵��
void ShowDocumentation();
//��ʾ��������
void ShowNavigation();
//���Ǻ�������
void AngleSettings();
//��������
void PrecisionSettings();
//�浵
void Archive(char* data);
//�������
void DoubleCalculation();
//��������
void BigIntCalculation();
//�û�ƫ������
void PreferenceSettings();
//��ʷ��¼
void ShowHistory();


//��ʾ���˵��
void ShowDocumentation()
{
	printf("��������ʽ������������\n");
	printf("������BY:ShuangLuo������\n\n");
	printf("----------Documentation---------\n\n");
	printf("��������ܡ�\n");
	printf("1���������ʽ�����Զ��徫��\n");
	printf("2���ɽ��д������㣨�ݲ�֧�ֺ�����\n");
	printf("3���ɽ����ʽ������浽�ĵ�����֧�ֶ�ȡ\n\n");
	printf("�����ʽ���塿\n");
	printf("����ʽ�����ǳ�������+����-����*����/��ƽ��^������()���Լ���ѧ��������ϡ�\n");
	printf("����ʽ�пɰ����ո��\n");
	printf("�ﵱʹ�����Ǻ���ʱ���û������õ�ǰ�����Ǻ��������ǻ��Ȼ��ǽǶ�(Ĭ��Ϊ����)��\n");
	printf("1����ֵ֧�֣��������������ʹ��������Զ�����\n");
	printf("2������֧�֣�()\n");
	printf("3������֧�֣�+  -  *  /  ^  !\n");
	printf("4������֧�֣�cos(), sin(), tg(), ctg(), abs(), sign(), sqrt(), ln(), sinh(), cosh(), tanh(), coth()\n");
	printf("5������֧�֣�PI��E\n\n");
}

//��ʾ��������
void ShowNavigation()
{
	printf("��������ʽ������������\n");
	printf("������BY:ShuangLuo������\n\n");
	printf("-----------Navigation-----------\n\n");
	printf("1:��������\n");
	printf("2:��������\n");
	printf("3:ƫ������\n");
	printf("4:��ʷ��¼\n");
	printf("0:�˳�����\n\n");
}

//���Ǻ�������
void AngleSettings()
{
	int flag;
	printf("���Ǻ���������ѡ��: 1.�Ƕ��� 2.�����ƣ�Ĭ�ϣ�\t");
	while(1)
	{
		setbuf(stdin,NULL);
		scanf("%d",&flag);
		if(flag==1)
		{
			IsRad=false;
			printf("���óɹ�!��ǰ���Ǻ���������ѡ��:�Ƕ���\n\n");
			break;
		}
		else if(flag==2)
		{
			IsRad=true;
			printf("���óɹ�!��ǰ���Ǻ���������ѡ��:������\n\n");
			break;
		}
		else
		{
			printf("��ѡ����Ӧ��������:\n");
		}
	}
}

//��������
void PrecisionSettings()
{
	while(1)
	{
		printf("�����뱣����С��λ��(0~16): \t");
		int precision;
		setbuf(stdin,NULL);
		scanf("%d",&precision);
		if(precision>=0&&precision<=16)
		{
			DoubleCalPrecision=precision;
			printf("���óɹ�!��ǰ����:%dλС��\n\n",precision);
			break;
		}
		else
		{
			printf("��������ֻ֧��0~16λ���㾫��!\n\n");
		}
	}
}

//�浵
void Archive(char *data)
{
	FILE *fp=fopen("c:\\ExpressionCalculator_OutData.txt","a");
	if(fp==NULL)
	{
		printf("�ļ��򿪳���!\n\n");
	}
	fputs(data,fp);
	fclose(fp);
	printf("�浵�ɹ�!�����ѱ�����c:\\ExpressionCalculator_OutData.txt\n\n");
}

//�������
void DoubleCalculation()
{
	printf("��������ʽ:\n");
	GetExpression();
	printf("������ı��ʽ��:\n%s\n",Expression);
	AnalyzeExpression(Expression);
	if(!CatchException())
	{
		printf("�������:%s\n",Expression);
		int flag;
		while(1)
		{
			printf("�Ƿ���Ҫ�浵? 1.YES 2.NO\t");
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

//��������
void BigIntCalculation()
{
	printf("�������㻹�ڵ��Ե���,�����ڴ�...\n\n");
}

//�û�ƫ������
void PreferenceSettings()
{
	int flag;
	while(1)
	{
		printf("1.���Ǻ�������\n");
		printf("2.��������\n");
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
			printf("��ѡ����Ӧ��������:\n");
		}
	}
}

//��ʷ��¼
void ShowHistory()
{
	char ch;
	FILE *fp=fopen("c:\\ExpressionCalculator_OutData.txt","r");
	if(fp==NULL)
	{
		printf("�ļ��򿪳���!\n\n");
	}
	else
	{
		printf("��ʷ��¼:\n");
		while(!feof(fp))
			if((ch=fgetc(fp))!=EOF)
				putchar(ch);
		fclose(fp);
		while(1)
		{
			printf("\n�Ƿ����? 1:YES 2:NO\t");
			int flag=0;
			setbuf(stdin,NULL);
			scanf("%d",&flag);
			if(flag==1)
			{
				fp=fopen("c:\\ExpressionCalculator_OutData.txt","w");
				if(fp==NULL)
				{
					printf("�ļ��򿪳���!\n\n");
				}
				else
				{
					printf("�ļ������!\n\n");
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