/*
 * SqStack.h
 *
 *  Created on: 2008-11-11
 *      Author: jasonleakey
 */

#ifndef SQSTACK_H_
#define SQSTACK_H_

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 3

typedef BiTree SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack *S);

Status DestroyStack(SqStack *S);

Status ClearStack(SqStack *S);

#define STACKEMPTY(S) (((S).top == (S).base) ? (TRUE) : (FALSE))

int StackLength(SqStack const S);

Status GetTop_SqStack(SqStack const S, SElemType *e);

Status Push_SqStack(SqStack *S, SElemType const e);

Status Pop_SqStack(SqStack *S, SElemType *e);

Status StackTraverse(SqStack const S);

#endif /* SQSTACK_H_ */
