/*
 * basic_operation_LinkQueue.c
 *
 *  Created on: 2008-11-11
 *      Author: jasonleakey
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "LinkQueue.h"

Status InitQueue(LinkQueue *Q)
{/*构造一个空队列*/
	((*Q).front) = (QueuePtr)malloc(sizeof(QNode));
	if (NULL == (*Q).front)		//分配失败
	{
		printf("fail to InitQueue!\n");
		exit(EXIT_FAILURE);
	}
	(*Q).front->data = '\0';
	(*Q).rear = (*Q).front;
	(*Q).front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue *Q)
{/*销毁一个链队列,包括删除头结点*/
	QueuePtr p = (*Q).front->next;
	while (NULL != p)	//从队头第一个元素逐个删除
	{
		QueuePtr q = p->next;
		free(p);
		p = NULL;
		p = q;
	}
	free((*Q).front);
	(*Q).front = (*Q).rear = NULL;
	return OK;
}

Status ClearQueue(LinkQueue *Q)
{/*清空队列中所有元素,保留头结点*/
	QueuePtr p = (*Q).front->next;
	while (NULL != p)
	{
		QueuePtr q = p->next;
		free(p);
		p = NULL;
		p = q;
	}
	(*Q).rear = (*Q).front;
	(*Q).front->next = NULL;
	return OK;
}

int QueueLength(LinkQueue const Q)
{/*求队列中元素个数*/
	int count = 0;
	QueuePtr p = Q.front;
	while (Q.rear != p)
	{
		count++;
		p = p->next;
	}
	return count;
}

Status GetHead_Queue(LinkQueue const Q, QElemType *e)
{/*取得队头元素并将其赋于e*/
	if (Q.front == Q.rear)
	{
		return ERROR;
	}
	*e = Q.front->next->data;
	return OK;
}

Status EnQueue(LinkQueue *Q, QElemType const e)
{/*在队尾中插入一个元素,其值赋为e*/
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (NULL == p)
	{
		printf("fail to EnQueue,No Memory!\n");
		exit(EXIT_FAILURE);
	}
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e)
{/*在队头中删除一个元素*/
#if 0
	if ((*Q).front == (*Q).rear)
	{
		return ERROR;
	}
#endif
	assert((*Q).front != (*Q).rear);
	QueuePtr p = (*Q).front->next;
	if ((*Q).rear == p)
	{
		(*Q).rear = (*Q).front;
	}
	(*Q).front->next = p->next;
	*e = p->data;
	free(p);
	p = NULL;
	return OK;
}

Status QueueTraverse(LinkQueue const Q)
{/*从队头遍历到队尾*/
	QueuePtr p = Q.front->next;
	while (NULL != p)
	{
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}

