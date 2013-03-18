/*
 * basic_operation_BiTree.c
 *
 *  Created on: 2008-11-13
 *      Author: jasonleakey
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BiTree.h"
#include "LinkQueue.h"
#include "SqStack.h"

Status visitT(TElemType const e)
{
	printf("%c", e);
	return OK;
}

Status InitBiTree(BiTree *pT)
{/*构造空二叉树*/
	assert(NULL == *pT);
	*pT = NULL;
	return OK;
}

void CreateBiTree(BiTree *pT)
{/*按先序次序输入二叉树的结点的值*/
	TElemType ch;
	scanf("%c", &ch);
	if (' ' == ch)
	{
		*pT = NULL;
	}
	else
	{
		(*pT) = (BiTree)malloc(sizeof(BiTNode));
		if (NULL == (*pT))
		{
			printf("No memory for CreateBiTree!\n");
			exit(EXIT_FAILURE);
		}
		(*pT)->data = ch;
		CreateBiTree(&(*pT)->lchild);
		CreateBiTree(&(*pT)->rchild);
	}
}


void DestroyBiTree(BiTree *pT)
{/*销毁一棵二叉树*/
	if (*pT)
	{
		if (NULL == (*pT)->lchild)
		{
			DestroyBiTree(&(*pT)->lchild);
		}
		if (NULL == (*pT)->rchild)
		{
			DestroyBiTree(&(*pT)->rchild);
		}
		free(*pT);
		*pT = NULL;
	}
}

int BiTreeDepth(BiTree const T)
{/*求二叉树深的递归算法*/
	if (NULL == T)
	{
		return 0;
	}
	else
	{
		int lchildepth = 0;
		int rchildepth = 0;
		if (NULL != T->lchild)
		{
			lchildepth = BiTreeDepth(T->lchild);
		}
		if (NULL != T->rchild)
		{
			rchildepth = BiTreeDepth(T->rchild);
		}
		return ((lchildepth > rchildepth) ? (lchildepth + 1)\
				: (rchildepth + 1));
	}
}

TElemType Parent(BiTree const T, const TElemType e)
{/*返回值为e的结点的双亲结点的值,若e是根结点,则返回空*/
	LinkQueue Q;
	QElemType a;
	if (NULL != T)
	{
		InitQueue(&Q);
		EnQueue(&Q, T);
		while (!QUEUEEMPTY(Q))
		{
			DeQueue(&Q, &a);
			if (((NULL != a->lchild) && (a->lchild->data == e))\
					|| ((NULL != a->rchild) && (a->rchild->data == e)))
			{
				return a->data;
			}
			else
			{
				if (NULL != a->lchild)
				{
					EnQueue(&Q, a->lchild);
				}
				if (NULL != a->rchild)
				{
					EnQueue(&Q, a->rchild);
				}
			}
		}
	}
	return ' ';
}

BiTree Point(BiTree const T, const TElemType s)
{/*返回二叉树中指向元素值为s的结点的指针,若找不到该元素,返回空指针*/
	LinkQueue Q;
	QElemType a;
	if (NULL != T)
	{
		InitQueue(&Q);
		EnQueue(&Q, T);
		while (!QUEUEEMPTY(Q))
		{
			DeQueue(&Q, &a);
			if (s == a->data)
			{
				return a;
			}
			else
			{
				if (NULL != a->lchild)
				{
					EnQueue(&Q, a->lchild);
				}
				if (NULL != a->rchild)
				{
					EnQueue(&Q, a->rchild);
				}
			}
		}
	}
	return NULL;
}

TElemType LeftChild(BiTree const T, TElemType const e)
{/*如果元素值为e的结点有左孩子结点,则返回左孩子的元素值,否则返回空*/
	BiTree a;
	if (NULL != T)
	{
		a = Point(T, e);
		if (a && (NULL != a->lchild))
		{
			return a->lchild->data;
		}
	}
	return ' ';
}

TElemType RightChild(BiTree const T, const TElemType e)
{/*如果元素值为e的结点有右孩子结点,则返回右孩子的元素值,否则返回空*/
	BiTree a;
	if (NULL != T)
	{
		a = Point(T, e);
		if (a && (NULL != a->rchild))
		{
			return a->rchild->data;
		}
	}
	return ' ';
}

TElemType LeftSibling(BiTree const T, const TElemType e)
{/*如果元素值为e的结点有左兄弟结点,则返回左兄弟的元素值,否则返回空*/
	TElemType parentValue;
	BiTree p_parent;
	if (NULL != T)
	{
		parentValue = Parent(T, e);
		if (' ' != parentValue)
		{
			p_parent = Point(T, parentValue);
			if ((NULL != p_parent->lchild) && (NULL != p_parent->rchild)\
					&& (p_parent->rchild->data == e))
			{
				return p_parent->lchild->data;
			}
		}
	}
	return ' ';
}

TElemType RightSibling(BiTree const T, const TElemType e)
{/*如果元素值为e的值的结点有右兄弟结点,则返回右兄弟的元素值,否则返回空*/
	BiTree p_parent;
	if (NULL != T)
	{
		p_parent = Point(T, Parent(T, e));
		if (' ' != p_parent->data)
		{
			if ((NULL != p_parent->lchild) && (NULL != p_parent->rchild)\
					&& (p_parent->lchild->data == e))
			{
				return p_parent->rchild->data;
			}
		}
	}
	return ' ';
}

Status InsertChild(BiTree p, int const LR, BiTree const c)
{/*指针p指向二叉树中某一结点,LR为0-插入左子树,LR为1-插入右子树,如果
* p指向的原有子树成为c的右子树*/
	if (NULL != p)
	{
		if (0 == LR)
		{
			if (NULL != p->lchild)
			{
				c->rchild = p->lchild;
			}
			p->lchild = c;
		}
		else if (1 == LR)
		{
			if (NULL != p->rchild)
			{
				c->rchild = p->rchild;
			}
			p->rchild = c;
		}
		else
		{
			printf("LR输入有误!\n");
			return ERROR;
		}
		return OK;
	}
	return ERROR;
}

Status DeleteChild(BiTree const p, int const LR)
{/*p指向二叉树某个结点,LR==0为左子树,LR==1为右子树,递归算法*/
	if (NULL != p)
	{
		if (0 == LR && NULL != p->lchild)
		{
			DestroyBiTree(&(p->lchild));
		}
		else
		{
			DestroyBiTree(&(p->rchild));
		}
		return OK;
	}
	return ERROR;
}

void PreOrderTraverse(BiTree const T, Status (*Visit)(TElemType const))
{/*递归法先序遍历,注意回调函数的使用*/
	if (NULL != T)
	{
		Visit(T->data);		//先访问根结点
		PreOrderTraverse(T->lchild, Visit);	//再访问左子树
		PreOrderTraverse(T->rchild, Visit);//最后访问右子树
	}
}

//Function use: 第一种非递归先序遍历算法
void PreOrderUnrec1(BiTree T, Status (*Visit)(TElemType const))
{
	SqStack S;
	InitStack(&S);
	while (NULL != T || !STACKEMPTY(S))
	{
		while (NULL != T)
		{
			Visit(T->data);
			if (NULL != T->rchild)
			{
				Push_SqStack(&S, T->rchild);
			}
			T = T->lchild;
		}
		if (!STACKEMPTY(S))
		{
			Pop_SqStack(&S, &T);
		}
	}
	printf("\n");
	DestroyStack(&S);
}

void PreOrderUnrec2(BiTree T, Status (*Visit)(TElemType const))
{
	SqStack S;
	InitStack(&S);
	while (NULL != T || !STACKEMPTY(S))
	{
		if (NULL != T)
		{
			Visit(T->data);
			Push_SqStack(&S, T);
			T = T->lchild;
		}
		else
		{
			do
			{
				Pop_SqStack(&S, &T);
			} while (!STACKEMPTY(S) && NULL == T->rchild);
			T = T->rchild;
		}
	}
	printf("\n");
	DestroyStack(&S);
}

void PreOrderUnrec3(BiTree T, Status (*Visit)(TElemType const))
{
	SqStack S;
	InitStack(&S);
	while (NULL != T || !STACKEMPTY(S))
	{
		while (NULL != T)
		{
			Visit(T->data);
			Push_SqStack(&S, T);
			T = T->lchild;
		}
		if (!STACKEMPTY(S))
		{
			Pop_SqStack(&S, &T);
			T = T->rchild;
		}
	}
	printf("\n");
	DestroyStack(&S);
}

void InOrderTraverse(BiTree const T, Status (*Visit)(TElemType const))
{/*递归中序遍历二叉树*/
	if (NULL != T)
	{
		InOrderTraverse(T->lchild, Visit);	//先访问左子树
		Visit(T->data);		//再访问根结点
		InOrderTraverse(T->rchild, Visit);	//最后访问右子树
	}
}

Status InOrderTraverse1_nonrecursive(BiTree const T, Status (*Visit)(TElemType const))
{/*非递归中序遍历二叉树,似乎跟递归法非常相似*/
	SqStack S;
	BiTree p = T;
	InitStack(&S);
	while ((NULL != p) || !STACKEMPTY(S))
	{
		if (NULL != p)
		{
			Push_SqStack(&S, p);
			p = p->lchild;
		}
		else
		{
			Pop_SqStack(&S, &p);
			if (!Visit(p->data))
			{
				return ERROR;
			}
			p = p->rchild;
		}
	}
	printf("\n");
	return OK;
}

Status InOrderTraverse2_nonrecursive(BiTree const T, Status (*Visit)(TElemType))
{/*另一种非递归中序遍历二叉树*/
	SqStack S;
	InitStack(&S);
	Push_SqStack(&S, T);
	BiTree p = T;
	while (!STACKEMPTY(S))
	{
		//从当前结点起走到左子树尽头
		while (GetTop_SqStack(S, &p) && NULL != p)
		{
			Push_SqStack(&S, p->lchild);
		}
		/*弹出空指针*/
		Pop_SqStack(&S, &p);
		if (!STACKEMPTY(S))
		{
			/*访问结点,向右走一步*/
			Pop_SqStack(&S, &p);
			if (!Visit(p->data))
			{
				return ERROR;
			}
			Push_SqStack(&S, p->rchild);
		}
	}
	printf("\n");
	return OK;
}

void PostOrderTraverse(BiTree const T, Status (*Visit)(TElemType))
{/*后序遍历二叉树*/
	if (NULL != T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T->data);
	}
}

void LevelOrderTraverse(BiTree const T, Status (*Visit)(TElemType))
{/*层序遍历二叉树,需要辅助队列*/
	LinkQueue Q;
	BiTree p = T;
	InitQueue(&Q);
	if (NULL != p)
	{
		EnQueue(&Q, p);
	}
	while (!QUEUEEMPTY(Q))
	{
		DeQueue(&Q, &p);
		Visit(p->data);
		if (NULL != p->lchild)
		{
			EnQueue(&Q, p->lchild);
		}
		if (NULL != p->rchild)
		{
			EnQueue(&Q, p->rchild);
		}
	}
	printf("\n");
	return;
}


