/* queue queue */

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE  1024

//////////////////////////////////////////////////////////////////////
typedef struct
{
    int *queue;
    int front;
    int rear;
    int qsize;
    int qcount;
 }SqQueue;

/*********************************************************************
* Create Queue
**********************************************************************/
int QueueCreate(SqQueue *sq)
{
    sq->queue = (int*)malloc(QUEUE_SIZE*sizeof(int));
    if(!sq->queue)
    {
    	  printf("QueueCreate()->malloc() failure! \n");
        exit(0);
    }

    sq->front = sq->rear = 0;
    sq->qcount = 0;
    sq->qsize = QUEUE_SIZE;
    return 0;
}

/*********************************************************************
* Check Queue Empty
**********************************************************************/
int QueueEmpty(SqQueue *sq, int mode)
{
	  if(mode == 0)         // Line Mode
	  {
	      if(sq->qcount < 1)
	      {
	          return 1;
	      }
	  }
	  else                  // Circle Mode
	  {
	      if((sq->front == sq->rear)&&(sq->qcount < 1))
	      {
	          return 1;
	      }	  	
	  }
	  
    return 0;
}

/*********************************************************************
* Check Queue Full
**********************************************************************/
int QueueFull(SqQueue *sq, int mode)
{
	  if(mode == 0)         // Line Mode
	  {
	      if(sq->qcount == QUEUE_SIZE)
	      {
	          return 1;
	      }
	  }
	  else                  // Circle Mode
	  {
	      if((sq->front == sq->rear)&&(sq->qcount == QUEUE_SIZE))
	      {
	          return 1;
	      }	  	
	  }
    
    return 0;
}

/*********************************************************************
* Delete Queue (Line Mode)
**********************************************************************/
int QueueEnterL(SqQueue *sq, int qdata)
{
	   if(QueueFull(sq, 0))
	   {
         	printf("The queue is full!\n");
         	return -1;
	   }
	   
	   if(sq->qcount >= 1)
	   {
         memmove((sq->queue + 1), sq->queue, sq->qcount*sizeof(int));
     }
     sq->queue[sq->rear] = qdata;
     if( sq->qcount < QUEUE_SIZE)         // overflow limit
     {
         sq->qcount++;     	
     }
     return 0;
}

/*********************************************************************
* Enter Queue (Circle Mode)
**********************************************************************/
int QueueEnterC(SqQueue *sq, int qdata)
{
	   if(QueueFull(sq, 1))
	   {
         printf("The queue is full!\n");
         return -1;
	   }
	   
	   sq->rear = (sq->rear + 1) % QUEUE_SIZE;
     sq->queue[sq->rear] = qdata;
     sq->qcount ++;    
     
     return 0;
}

/*********************************************************************
* Delete Queue (Line Mode)
**********************************************************************/
int QueueDeleteL(SqQueue *sq, int *qdata)
{
	   if(QueueEmpty(sq, 0))
	   {
         printf("The queue is empty!\n");
         return -1;
	   }
	   
     sq->qcount --;
     *qdata = sq->queue[sq->qcount];
     
     return 0;
}

/*********************************************************************
* Delete Queue (Circle Mode)
**********************************************************************/
int QueueDeleteC(SqQueue *sq, int *qdata)
{
	   if(QueueEmpty(sq, 1))
	   {
         printf("The queue is empty!\n");
         return -1;
	   }
	   
	   sq->front = (sq->front + 1) % QUEUE_SIZE;
     *qdata = sq->queue[sq->front];
     sq->qcount --;
     
     return 0;
}

/*********************************************************************
* Clear Stack (Set Null)
**********************************************************************/
int QueueClear(SqQueue *sq)
{
    sq->front = sq->rear = 0;
    sq->qcount = 0;
    memset(sq->queue, 0, sizeof(QUEUE_SIZE*sizeof(int)));
    
    return 0;
}

/*********************************************************************
* Get Queue Count
**********************************************************************/
int QueueGetTag(SqQueue *sq)
{
    return (sq->qcount);
}

/*********************************************************************
* Destory Queue
**********************************************************************/
int QueueDestroy(SqQueue *sq)
{
    free(sq->queue);
    
    return 0;
} 
