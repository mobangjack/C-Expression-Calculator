#ifndef DoubleCalBase
#define DoubleCalBase

#include"Base.h"

/*--------------------------------
�����Ǳ�ͷ�ļ��������ĸ�����������
--------------------------------*/

//�����ȣ�С��λ���������ݴ�ӡ���ַ��������16λ��Ч����
void sprintf_by_precision(char* buffer,double data,int precision);

//�����ȣ�С��λ���������ݴ�ӡ������̨�����16λ��Ч����
void printf_by_precision(double data,int precision);

/*--------------------------------
�����Ǳ�ͷ�ļ��������ĸ�������ʵ��
--------------------------------*/

//�����ȣ�С��λ���������ݴ�ӡ���ַ��������16λ��Ч����
void sprintf_by_precision(char* buffer,double data,int precision)
{
	switch(precision)
	{
	case 0:
		sprintf(buffer,"%.0lf",data);
		break;
	case 1:
		sprintf(buffer,"%.1lf",data);
		break;
	case 2:
		sprintf(buffer,"%.2f",data);
		break;
	case 3:
		sprintf(buffer,"%.3lf",data);
		break;
	case 4:
		sprintf(buffer,"%.4lf",data);
		break;
	case 5:
		sprintf(buffer,"%.5lf",data);
		break;
	case 6:
		sprintf(buffer,"%.6lf",data);
		break;
	case 7:
		sprintf(buffer,"%.7lf",data);
		break;
	case 8:
		sprintf(buffer,"%.8lf",data);
		break;
	case 9:
		sprintf(buffer,"%.9lf",data);
		break;
	case 10:
		sprintf(buffer,"%.10lf",data);
		break;
	case 11:
		sprintf(buffer,"%.11lf",data);
		break;
	case 12:
		sprintf(buffer,"%.12lf",data);
		break;
	case 13:
		sprintf(buffer,"%.13lf",data);
		break;
	case 14:
		sprintf(buffer,"%.14lf",data);
		break;
	case 15:
		sprintf(buffer,"%.15lf",data);
		break;
	case 16:
		sprintf(buffer,"%.16lf",data);
		break;
	default:
		sprintf(buffer,"%lf",data);
	}
}

//�����ȣ�С��λ���������ݴ�ӡ������̨�����16λ��Ч����
void printf_by_precision(double data,int precision)
{
	switch(precision)
	{
	case 0:
		printf("%.0lf",data);
		break;
	case 1:
		printf("%.1lf",data);
		break;
	case 2:
		printf("%.2f",data);
		break;
	case 3:
		printf("%.3lf",data);
		break;
	case 4:
		printf("%.4lf",data);
		break;
	case 5:
		printf("%.5lf",data);
		break;
	case 6:
		printf("%.6lf",data);
		break;
	case 7:
		printf("%.7lf",data);
		break;
	case 8:
		printf("%.8lf",data);
		break;
	case 9:
		printf("%.9lf",data);
		break;
	case 10:
		printf("%.10lf",data);
		break;
	case 11:
		printf("%.11lf",data);
		break;
	case 12:
		printf("%.12lf",data);
		break;
	case 13:
		printf("%.13lf",data);
		break;
	case 14:
		printf("%.14lf",data);
		break;
	case 15:
		printf("%.15lf",data);
		break;
	case 16:
		printf("%.16lf",data);
		break;
	default:
		printf("%lf",data);
	}
}
#endif