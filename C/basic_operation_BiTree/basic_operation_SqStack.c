/*
 * basic_operation_SqStack.c
 *
 *  Created on: 2008-11-12
 *      Author: jasonleakey
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BiTree.h"
#include "SqStack.h"

Status InitStack(SqStack *S)
{/*初始化一个顺序栈*/
	(*S).base = (SElemType *)malloc(\
			STACK_INIT_SIZE * sizeof(SElemType));
	if (NULL == (*S).base)
	{
		printf("fail to initStac;!\n");
		exit(EXIT_FAILURE);
	}
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S)
{/*销毁一个顺序栈*/
	free((*S).base);
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return OK;
}

Status ClearStack(SqStack *S)
{/*清空一个顺序栈*/
	memset((*S).base, '\0', (*S).stacksize);
	(*S).top = (*S).base;
	return OK;
}

int StackLength(SqStack S)
{/*求栈的长度*/
	return S.top - S.base;
}

Status GetTop_SqStack(SqStack const S, SElemType *e)
{/*取栈顶元素,若栈为空,则返回错误*/
	if (S.top <= S.base)
	{
		return ERROR;
	}
	*e = *(S.top - 1);
	return OK;
}

Status Push_SqStack(SqStack *S, SElemType const e)
{/*将值为e的元素压入栈中*/
	if (((*S).top - (*S).base) >= (*S).stacksize)/*栈满,追加存储空间*/
	{
		(*S).base = (SElemType *)realloc((*S).base,\
				((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (NULL == (*S).base)
		{
			printf("No memory!\n");
			exit(EXIT_FAILURE);
		}
		(*S).top = (*S).base + (*S).stacksize;/*有问题???*/
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop_SqStack(SqStack *S, SElemType *e)
{/*从栈中弹出一个元素,并将值赋给e,如果栈为空,则返回错误*/
	if ((*S).top == (*S).base)
	{
		return ERROR;
	}
	*e = *--(*S).top;
	return OK;
}

Status StackTraverse(SqStack const S)
{/*从栈底到栈顶依次遍历*/
	SElemType *p = S.base;
	while (S.top > p)
	{
		printf("%p", *p++);
	}
	printf("\n");
	return OK;
}
