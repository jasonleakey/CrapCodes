/*
 * 		文件名称:	CSTree_op.c
 * 		创建时间:	2008-12-14
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
#include "CSTree.h"
#include "Queue.h"
/*
 * Function
 * name  	: InitTree
 * use	  	: Init a CStree
 * @param 	: CSTree *pT, pointer of CSTree
 * @return	: Status
 */
Status InitTree(CSTree *pT)
{
	*pT = NULL;
	return OK;
}

/*
 * Function
 * name  	: DestroyTree
 * use	  	: Destroy a cstree
 * @param 	: CSTree *pT, pointer of CSTree
 * @return	: void
 */
void DestroyTree(CSTree *pT)
{
	if (NULL != *pT)
	{
		if (NULL != (*pT)->firstchild)
		{
			DestroyTree(&(*pT)->firstchild);
		}
		if (NULL != (*pT)->nextsibling)
		{
			DestroyTree(&(*pT)->nextsibling);
		}
		free(*pT);
		*pT = NULL;
	}
}



/*
 * Function
 * name  	: CreateTree
 * use	  	: Create a cstree
 * @param 	: CSTree *pT, pointer of cstree
 * @return	: Status
 */
Status CreateTree(CSTree *pT)
{
	char c[20];
	CSTree p, p1;
	LinkQueue Q;
	int i;
	int l;
	InitQueue(&Q);
	printf("Input data of Root:");
	scanf("%c%*c", &c[0]);
	if (Nil != c[0])
	{
		*pT = (CSTree)malloc(sizeof(CSNode));
		(*pT)->data = c[0];
		(*pT)->nextsibling = NULL;
		EnQueue(&Q, *pT);
		while (!QueueEmpty(Q))
		{
			DeQueue(&Q, &p);
			printf("Input child data of %c from left to right:", p->data);
			gets(c);
			l = strlen(c);		//not conclude '\n'
			if (l > 0)
			{
				p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode));
				p1->data = c[0];
				for (i = 1; i < l; i++)
				{
					p1->nextsibling = (CSTree)malloc(sizeof(CSNode));
					EnQueue(&Q, p1);		//EnQueue the previous node
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;
				EnQueue(&Q, p1);		//EnQueue the last
			}
			else
			{
				p->firstchild = NULL;
			}
		}
	}
	else
	{
		*pT = NULL;
	}
	return OK;
}

#define ClearTree DestroyTree

/*
 * Function
 * name  	: TreeEmpty
 * use	  	: determine whether the CSTree is empty
 * @param 	: CSTree T
 * @return	: Status, FALSE or TRUE
 */
Status TreeEmpty(CSTree const T)
{
	if (NULL != T)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
 * Function
 * name  	: TreeDepth
 * use	  	: return the depth of cstree, if none, return 0
 * @param 	: CSTree T, CStree name
 * @return	: int
 */
int TreeDepth(CSTree const T)
{
	CSTree p;
	int depth;
	int max = 0;
	if (NULL == T)
	{
		return 0;
	}
	if (NULL != T->firstchild)
	{
		return 1;
	}
	for (p = T->firstchild; NULL != p; p = p->nextsibling)
	{
		depth = TreeDepth(p);
		if (depth > max)
		{
			max = depth;
		}
	}
	return max + 1;
}

/*
 * Function
 * name  	: Value
 * use	  	: return the data of the cstree node
 * @param 	: CSTree p, pointer of a cstree node
 * @return	: TElemType
 */
inline TElemType Value(CSTree const p)
{
	return p->data;
}

/*
 * Function
 * name  	: Root
 * use	  	: return data of root, if none, return ' '
 * @param 	: CSTree T, pointer of cstree
 * @return	: TElemType, data of root
 */
TElemType Root(CSTree const T)
{
	if (NULL != T)
	{
		return Value(T);
	}
	else
	{
		return Nil;
	}
}

/*
 * Function
 * name  	: Point
 * use	  	: return cstree node pointer with data 'e' by non-recurssion
 * @param 	: CSTree const T, cstree name
 * 			  TElemType const e, node data
 * @return	: CSTree
 */
CSTree Point_non_recurssion(CSTree const T, TElemType const e)
{
	LinkQueue Q;
	QElemType a;
	if (NULL != T)
	{
		InitQueue(&Q);
		EnQueue(&Q, T);
		while (!QueueEmpty(Q))
		{
			DeQueue(&Q, &a);
			//树的先根遍历
			if (e == a->data)
			{
				DestroyQueue(&Q);
				return a;
			}
			if (NULL != a->firstchild)
			{
				EnQueue(&Q, a->firstchild);
			}
			if (NULL != a->nextsibling)
			{
				EnQueue(&Q, a->nextsibling);
			}
		}
	}
	return NULL;
}


/*
 * Function
 * name  	: Assign
 * use	  	: replace node with data cur_e with value
 * @param 	: CSTree *pT, pointer of cstree
 * @return	: Status, if succeed, return OK, else return ERROR
 */
Status Assign(CSTree *pT, TElemType const cur_e, TElemType const value)
{
	CSTree p;
	if (NULL != *pT) 	//树不空
	{
		p = Point_non_recurssion(*pT, cur_e);
		if (NULL != p)
		{
			p->data = value;
			return OK;
		}
	}
	else
	{
		return ERROR;
	}
}

//Function use: cur_e is a nonterminal node, function return
//its parent's data, if not exist, return ' '
TElemType Parent(CSTree const T, TElemType const cur_e	)
{
	CSTree p;
	CSTree s;
	LinkQueue Q;
	if (NULL != T)
	{
		InitQueue(&Q);
		if (cur_e == Value(T))		//根结点值为cur_e
		{
			DestroyQueue(&Q);
			return Nil;
		}
		else
		{
			EnQueue(&Q, T);
			while (!QueueEmpty(Q))
			{
				DeQueue(&Q, &p);
				if (NULL != p->firstchild)
				{
					if (cur_e == Value(p->firstchild))
					{
						DestroyQueue(&Q);
						return Value(p);
					}
					s = p;		//双亲指针保存于s
					p = p->firstchild;
					EnQueue(&Q, p);		//入队长子
					while (NULL != p->nextsibling)
					{
						p = p->nextsibling;
						if (cur_e == Value(p))
						{
							return Value(s);
						}
						EnQueue(&Q, p);
					}
				}
			}
		}
	}
	return Nil;
}

//Function use: cur_e is data of a nonterminal node, return data of its
//leftchild node, if none, return ' '
TElemType LeftChild(CSTree const T, TElemType const cur_e)
{
	CSTree p;
	if (NULL != T)
	{
		p = Point_non_recurssion(T, cur_e);
		if (NULL != p && NULL != p->firstchild)
		{
			return Value(p->firstchild);
		}
		else
		{
			return Nil;
		}
	}
	else
	{
		return Nil;
	}
}

//Function use: cur_e is data of a nonterminal node, return data of its
//rightsibling node, if none, return ' '
TElemType RightSibling(CSTree const T, TElemType const cur_e)
{
	CSTree p;
	if (NULL != T)
	{
		p = Point_non_recurssion(T, cur_e);
		if (NULL != p && NULL != p->nextsibling)	//找到此结点且其有右兄弟
		{
			return Value(p->nextsibling);
		}
		else
		{
			return Nil;
		}
	}
	else	//树空
	{
		return Nil;
	}
}



//Function use: preorder traverse the whole cstree
void PreOrderTraverse(CSTree T, void(*Visit)(TElemType))
{
	if (NULL != T)
	{
		Visit(Value(T));
		PreOrderTraverse(T->firstchild, Visit);
		PreOrderTraverse(T->nextsibling, Visit);
	}
}

//Function use: postorder traverse the entire cstree with the method
//equal with Bitree InOrdertraverse
void PostOrderTraverse_recurssion1(CSTree T, void(*Visit)(TElemType))
{
	if (NULL != T)
	{
		PostOrderTraverse_recurssion1(T->firstchild, Visit);
		Visit(Value(T));
		PostOrderTraverse_recurssion1(T->nextsibling, Visit);
	}
}

//Function use: postorder traverse the entire cstree by recurssion
void PostOrderTraverse_recurssion2(CSTree const T, void (*Visit)(TElemType))
{
	CSTree p;
	if (NULL != T)
	{
		if (T->firstchild)
		{
			PostOrderTraverse_recurssion2(T->firstchild, Visit);
			p = T->firstchild->nextsibling;
			while (NULL != p)
			{
				PostOrderTraverse_recurssion2(p, Visit);
				p = p->nextsibling;
			}
		}
		Visit(Value(T));
	}
}

//Function use: levelorder traverse the whole cstree
void LevelOrderTraverse(CSTree const T, void(*Visit)(TElemType))
{
	CSTree p;
	LinkQueue Q;
	if (NULL != T)
	{
		InitQueue(&Q);
		EnQueue(&Q, T);
		while (!QueueEmpty(Q))
		{
			DeQueue(&Q, &p);
			Visit(Value(p));
			for (p = p->firstchild; NULL != p; p = p->nextsibling)
			{
				EnQueue(&Q, p);
			}
		}
	}
}


