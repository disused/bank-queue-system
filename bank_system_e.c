/* Bank System */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_queue.c"

#define USE_LINE_QUEUE

#ifdef USE_LINE_QUEUE
#define MODE 0
#else
#define MODE 1
#endif
/////////////////////////////////////////////////////////////////
SqQueue sq,vip_sq;
int g_num = 0;
int v_num = 0;
#define BSYS_MAX_USER_NUM     1000

/***************************************************************
* Bank System Init
****************************************************************/
int Bank_Sys_Init(void)
{
	FILE *fp = NULL;	
	char buf[10];	

	QueueCreate(&sq);
	QueueClear(&sq);
	QueueCreate(&vip_sq);
	QueueClear(&vip_sq);
	
	fp = fopen("banklist.txt","r");
	if(fp == NULL)
	{
		return -1;
	}
	while(fgets(buf,10,fp) != NULL)
	{
		buf[strlen(buf)-1] = '\0';
		if(strncmp(buf,"uid",3) == 0)
		{
			QueueEnterL(&sq,atoi(&buf[3]));
		}
		else
			continue;
	}
	fclose(fp);
	
	fp = fopen("banklist_vip.txt","r");
	if(fp == NULL)
	{
		return -1;
	}
	while(fgets(buf,10,fp) != NULL)
	{
		buf[strlen(buf)-1] = '\0';
		if(strncmp(buf,"vip",3) == 0)
		{
			QueueEnterL(&vip_sq,atoi(&buf[3]));
		}
		else
			continue;
	}
	fclose(fp);

	g_num = (*(sq.queue))+1;
	v_num = (*(vip_sq.queue))+1;
    	return 0;
}

/***************************************************************
* Bank System Quit
****************************************************************/
int Bank_Sys_Term(void)
{
	QueueDestroy(&sq);
	QueueDestroy(&vip_sq);
	return 0;
}
/***************************************************************
*Bank Get One VIP ID
****************************************************************/
int Bank_Sys_Geg_VIPID(void)
{
	int ret;

#ifdef USE_LINE_QUEUE
	ret = QueueEnterL(&vip_sq,v_num);
#else
	ret = QueueEnterC(&vip_sq,v_num);
#endif
	if(ret == -1)
		return -1;
	printf("You VIP ID is %d\n",v_num);
	v_num++;

	FILE *fp = NULL;
	int i,count;
	fp = fopen("banklist_vip.txt","w");
	for(i =0 ,count=vip_sq.qcount ; i<vip_sq.qcount ; i++,count--)
	{
		fprintf(fp,"vip%d\n",(int)*(vip_sq.queue+count-1));
	}
	fclose(fp);
	return 0;
}

/***************************************************************
* Bank Get One ID
****************************************************************/
int Bank_Sys_Get_Id(void)
{
	int ret;

#ifdef USE_LINE_QUEUE
	ret = QueueEnterL(&sq,g_num);
#else
	ret = QueueEnterC(&sq,g_num);
#endif
	if(ret == -1)
		return -1;
	printf("You ID is %d\n",g_num);
	g_num++;

	FILE *fp = NULL;
	int i,count;
	fp = fopen("banklist.txt","w");
	for(i =0 ,count=sq.qcount ; i<sq.qcount ; i++,count--)
	{
		fprintf(fp,"uid%d\n",(int)*(sq.queue+count-1));
	}
	fclose(fp);

	return 0;
}

/***************************************************************
* Bank Call One ID
****************************************************************/
int Bank_Sys_Call_Id(void)
{
	int ret;
	int uid;

	if(!QueueEmpty(&vip_sq,MODE))
	{
#ifdef USE_LINE_QUEUE
		ret = QueueDeleteL(&vip_sq,&uid);
#else 
		ret = QueueDeleteC(&vip_sq,&uid);
#endif
		if(ret == -1)
			return -1;
		printf("VIP ID = %d\n",uid);
	
		FILE *fp = NULL;
		int i,count;
		fp = fopen("banklist_vip.txt","w");
		for(i =0 ,count=vip_sq.qcount ; i<vip_sq.qcount ; i++,count--)
		{
			fprintf(fp,"vip%d\n",(int)*(vip_sq.queue+count-1));
		}
		fclose(fp);

		return uid;
	}

#ifdef USE_LINE_QUEUE
	ret = QueueDeleteL(&sq,&uid);
#else 
	ret = QueueDeleteC(&sq,&uid);
#endif
	if(ret == -1)
		return -1;
	printf("ID = %d\n",uid);

	FILE *fp = NULL;
	int i,count;
	fp = fopen("banklist.txt","w");
	for(i =0 ,count=sq.qcount ; i<sq.qcount ; i++,count--)
	{
		fprintf(fp,"uid%d\n",(int)*(sq.queue+count-1));
	}
	fclose(fp);

	return uid;
}

/***************************************************************
* Bank Get All Users Number
****************************************************************/
unsigned int Bank_Get_User_Num(void)
{
	unsigned int num;
	num = QueueGetTag(&sq);
	num += QueueGetTag(&vip_sq);
	 printf("Users number is %d\n",num);
	return num;
}

/***************************************************************
* Bank Get All Users Number
****************************************************************/
int main(int argc, char**argv)
{
    	char virtkey = 0;
        //int g_num = 1;
	int uid;
    	unsigned int sum;
	Bank_Sys_Init();
	      	
	  for(;;)
	  {
        	scanf("%c", &virtkey); 
        
        	switch(virtkey)
        	{
			case 'v':Bank_Sys_Geg_VIPID();
				break;
        	   	case 'g':Bank_Sys_Get_Id();
        	     		break;
        	  	case 'c':uid = Bank_Sys_Call_Id();
				break;
        	   	case 'u':sum = Bank_Get_User_Num();
        	     		break;
        	     
        	   	case 'e':
	                	goto BSYSEXIT;
        	    		break;        	     
        	   
        	   	default:     	   	   
        	   	   	if(virtkey != 10) // "ENTER" Key Code (10)
        	   	   	{
        	          		 printf("Error Enter Key!! \n");
        	       		}
        	     		break;
        	}
	  }
	  
BSYSEXIT:
	  Bank_Sys_Term();
	  
    return 0;
}
