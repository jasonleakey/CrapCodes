/*
 * LinkQueue.h
 *
 *  Created on: 2008-11-11
 *      Author: jasonleakey
 */

#ifndef LINKQUEUE_H_
#define LINKQUEUE_H_

#include "PTree.h"
typedef struct {
	int num;
	TElemType name;
} QElemType;


typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front, rear;
}LinkQueue;
#define OK 1
#define ERROR 0

Status InitQueue(LinkQueue *Q);

Status DestroyQueue(LinkQueue *Q);

Status ClearQueue(LinkQueue *Q);

#define QUEUEEMPTY(Q) ((((Q).front == (Q).rear) ? (TRUE) : (FALSE)))

int QueueLength(LinkQueue const Q);

Status GetHead_Queue(LinkQueue const Q, QElemType *e);

Status EnQueue(LinkQueue *Q, QElemType const e);

Status DeQueue(LinkQueue *Q, QElemType *e);

#endif /* LINKQUEUE_H_ */
