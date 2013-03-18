/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-23
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

#define MAXSIZE 20
typedef char TElemType;

typedef struct BTNode {
	TElemType data;
	struct BTNode *lchild;
	struct BTNode *rchild;
	struct BTNode *parent;
} BTNode, *BiPTree;

void vi(TElemType e)
{
	printf("%c", e);
}
//Function use: 借助每个结点的空指针域,先序遍历整个树,不借助栈
void PreOrder(BiPTree T, void (*Visit)(TElemType))
{
	BiPTree pre = NULL;
	while (NULL != T)
	{
		while (NULL != T)
		{
			Visit(T->data);
			T->parent = pre;
			pre = T;
			T = T->lchild;
		}
		T = pre;
		while (NULL != T && NULL == T->rchild)
		{
			T = T->parent;
		}
		if (NULL != T)
		{
			pre = T->parent;		//此语句最关键
			T = T->rchild;
		}
	}
	printf("\n");
}


void CreateBiTree(BiPTree *pT)
{/*按先序次序输入二叉树的结点的值*/
	TElemType ch;
	scanf("%c", &ch);
	if (' ' == ch)
	{
		*pT = NULL;
	}
	else
	{
		(*pT) = (BiPTree)malloc(sizeof(BTNode));
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

void DestroyBiTree(BiPTree *T)
{/*销毁一棵二叉树*/
	if (*T)
	{
		if (NULL == (*T)->lchild)
		{
			DestroyBiTree(&(*T)->lchild);
		}
		if (NULL == (*T)->rchild)
		{
			DestroyBiTree(&(*T)->rchild);
		}
		free(*T);
		*T = NULL;

	}
}


int main(int argc, char **argv)
{
	BiPTree PT;
	printf("建立树,按先序输入:");
	CreateBiTree(&PT);
	printf("先序遍历结果:");
	PreOrder(PT, vi);
	DestroyBiTree(&PT);

	return EXIT_SUCCESS	;
}
