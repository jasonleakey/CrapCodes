/*
 * 		文件名称:	basic_operation.c
 * 		创建时间:	2008-12-1
 * 		程序作者:	jasonleakey
 * 		当前版本:	1.0
 * 		Copyright 2008 jasonleakey
 * 		<jasonleakey@sohu.com>
 * 		<QQ:174481438>
 * 		--------------------------------------------------------------------
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "PTree.h"

#include "LinkQueue.h"
/*
 * Function
 * name  	: InitPTree
 * use	  	: initiate a parentTree
 * @param 	: PTree *pT
 * @return	: void
 */
void InitPTree(PTree *pT)
{
	assert(NULL != *pT);
	(*pT)->node_count = 0;
}

/*
 * Function
 * name  	: DestroyPTree
 * use	  	: Destroy a parentTree
 * @param 	: PTree *pT
 * @return	: void
 */
void DestroyPTree(PTree *pT)
{
	assert(NULL != *pT);
}

/*
 * Function
 * name  	: CreatePTree
 * use	  	: Create a parentTree
 * @param 	: PTree *pT
 * @return	: void
 */
Status CreatePTree(PTree *pT)
{ /* 操作结果: 构造树T */
	LinkQueue q;
	QElemType p, qq;
	int i = 1, j, l;
	char c[MAX_TREE_SIZE]; /* 临时存放孩子结点数组 */
	InitQueue(&q); /* 初始化队列 */
	printf("请输入根结点: ");
	scanf("%c", &((*pT)->nodes[0].data)); /* 根结点序号为0,%*c吃掉回车符 */
	while (getchar() != '\n'){NULL;}	//清空标准输入流
	if ((*pT)->nodes[0].data != Nil) /* 非空树 */
	{
		(*pT)->nodes[0].parent = -1; /* 根结点无双亲 */
		qq.name = (*pT)->nodes[0].data;
		qq.num = 0;
		EnQueue(&q, qq); /* 入队此结点 */
		while (i < MAX_TREE_SIZE && !QUEUEEMPTY(q)) /* 数组未满且队不空 */
		{
			DeQueue(&q, &qq); /* 出队一个结点 */
			printf("请按长幼顺序输入结点%c的所有孩子: ", qq.name);
			fgets(c, MAX_TREE_SIZE, stdin);
			l = strlen(c);
			for (j = 0; j < l - 1; j++)	 //多读入了一个换行符
			{
				(*pT)->nodes[i].data = c[j];
				(*pT)->nodes[i].parent = qq.num;
				p.name = c[j];
				p.num = i;
				EnQueue(&q, p); /* 入队此结点 */
				i++;
			}
		}
		if (i > MAX_TREE_SIZE)
		{
			printf("结点数超过数组容量\n");
			exit(-1);
		}
		(*pT)->node_count = i;
	}
	else
	{
		(*pT)->node_count = 0;
	}
	return OK;
}
/*
 * Function
 * name  	: PTreeEmpty
 * use	  	: determine if the tree is empty
 * @param 	: PTree T
 * @return	: boolean, if non-empty, return FALSE
 * 					else return TRUE
 */
boolean PTreeEmpty(PTree const T)
{
	return (0 == T->node_count) ? (TRUE) : (FALSE);
}

/*
 * Function
 * name  	: PTreeDepth
 * use	  	: calculate the depth of tree
 * @param 	: PTree T
 * @return	: int.if tree is empty,return 0
 */
int PTreeDepth(PTree const T)
{
	int curnum;
	int curdepth = 0; //depth of current node
	int maxdepth = 0; //max depth of all
	boolean hasChild[MAX_TREE_SIZE] = { FALSE};
	for (curnum = T->node_count; curnum > 0; curnum--)
	{
		if (!hasChild[curnum])
		{
			curdepth = 1;
			int m = curnum;
			//traverse from leaf to root and calculate depth
			while (-1 != T->nodes[m].parent)
			{
				curdepth++;
				m = T->nodes[m].parent;
				hasChild[m] = TRUE;
			}
			if (curdepth > maxdepth)
			{
				maxdepth = curdepth;
			}
		}
	}
	return maxdepth;
}

/*
 * Function
 * name  	: Root
 * use	  	: return the value of Root node
 * @param 	: PTree T
 * @return	: TElemType,if tree is empty, return ' '
 */
TElemType Root(PTree const T)
{
	assert(NULL != T);
	return T->nodes[0].data;
}

/*
 * Function
 * name  	: Value
 * use	  	: return the i-numth node value
 * @param 	: PTree T
 * 			  int i
 * @return	: TElemType
 */
TElemType Value(PTree const T, int i)
{
	return (i < T->node_count) ? (T->nodes[i].data) : (Nil);
}

/*
 * Function
 * name  	: Assign
 * use	  	: replace the current value with new value
 * @param 	: PTree *pT, pointer of the tree
 *            TElemType cur_e, the value you want to modify
 *            TElemType value, new value replaced
 * @return	: void
 */
Status Assign(PTree *pT, TElemType const cur_e, TElemType const value)
{
	int curnum;
	//Make the last addition node as a sentry
	(*pT)->nodes[(*pT)->node_count + 1].data = cur_e;
	for (curnum = 0; cur_e != (*pT)->nodes[curnum].data; ++curnum)
	{
		NULL;
	}
	//if not found, then return error
	if (curnum == (*pT)->node_count + 1)
	{
		printf("No such element!\n");
		return -1;
	}
	(*pT)->nodes[curnum].data = value;
	return 0;
}

/*
 * Function
 * name  	: Parent
 * use	  	: return data of parent of target node
 * @param 	: PTree const T, parent tree
 * 			  TElemType const cur_e, target node
 * @return	: TElemType, data of parent of the cur_e
 */
TElemType Parent(PTree const T, TElemType const cur_e)
{
	int k;
	for (k = 0; k < T->node_count && cur_e != T->nodes[k].data; ++k)
	{
		NULL;
	}
	if (k >= T->node_count)
	{
		return Nil; //not found
	}
	else
	{
		return T->nodes[T->nodes[k].parent].data; //found
	}
}

/*
 * Function
 * name  	: LeftChild
 * use	  	:
 * @param 	: PTree const T, pointer of parent tree
 * 			  TElemType const cur_e, target node
 * @return	: TElemType, data of target node's parent
 */
TElemType LeftChild(PTree const T, TElemType const cur_e)
{
	int j;
	if (1 >= T->node_count)
	{
		return Nil;
	}
	for (j = 1; j < T->node_count && cur_e != T->nodes[T->nodes[j].parent].data; j++)
	{
		NULL;
	}
	if (j >= T->node_count)
	{
		return Nil;
	}
	return T->nodes[j].data;
}

/*
 * Function
 * name  	: RightSiling
 * use	  	: if current node has rightsibling node, return its data
 * 			  else return Nil
 * @param 	: PTree const T, pointer of parent tree
 * 			  TElemType const cur_e, data of current node
 * @return	: TElemType, data of Rightsibling node of current node
 */
TElemType RightSibling(PTree const T, TElemType const cur_e)
{
	int j;
	for (j = 0; j < T->node_count && cur_e != T->nodes[j].data; j++)
	{
		NULL;
	}
	if (j >= T->node_count\
 || T->nodes[j].parent != T->nodes[j + 1].parent)
	{
		return Nil;
	}
	return T->nodes[j + 1].data;
}

/*
 * Function
 * name  	: Print
 * use	  	: print data of every node,and its' parent's data if haven
 * @param 	: PTree const T, pointer of parent tree
 * @return	: void
 */
void Print(PTree const T)
{
	assert(NULL != T && Nil != T->nodes[0].data);
	int i;
	printf("Total node count:%d\n", T->node_count);
	printf("Current Node**Parent Node\n");
	printf("Root:%8c\n", T->nodes[0].data);
	for (i = 1; i < T->node_count; i++)
	{
		printf("%8c%8c\n", T->nodes[i].data, T->nodes[T->nodes[i].parent].data);
	}
}

void vi(TElemType const e)
{
	printf("%c", e);
}

void Traverse(PTree const T, void(*Visit)(TElemType const))
{
	int i;
	for (i = 0; i < T->node_count; i++)
	{
		Visit(T->nodes[i].data);
	}
	printf("\n");
}
