#include"MyUI.h"

void main()
{
	
	ShowDocumentation();
	while(1)
	{
		ShowNavigation();
		int flag=0;
		setbuf(stdin,NULL);
		scanf("%d",&flag);
		if(flag==0)break;
		else if(flag==1)
		{
			DoubleCalculation();
		}
		else if(flag==2)
		{
			BigIntCalculation();
		}
		else if(flag==3)
		{
			PreferenceSettings();
		}
		else if(flag==4)
		{
			ShowHistory();
		}
		else
		{
			printf("\n�밴��������˵�!\n\n");
		}
	}
}

