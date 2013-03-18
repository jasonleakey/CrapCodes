#ifndef C3_2_H_
#define C3_2_H_

#include "CSTree.h"

typedef CSTree QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
	QueuePtr front, rear;
} LinkQueue;

#endif
