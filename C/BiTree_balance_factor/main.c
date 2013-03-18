/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-26
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

typedef char TElemType;

typedef struct BiTNode {		//带平衡因子的二叉链表
	TElemType data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
	int bf;			//平衡因子
}BiTNode, *BiTree;

//Function use: 递归法求平衡因子,注意返回的是树的高度
int cal_balance(BiTree T)
{
	int nLcDepth = 0;
	int nRcDepth = 0;
	if (NULL == T)
	{
		return 0;
	}
	else
	{
		nLcDepth = cal_balance(T->lchild);
		nRcDepth = cal_balance(T->rchild);
		T->bf = nLcDepth - nRcDepth;
		return (nLcDepth > nRcDepth) ?\
				(nLcDepth + 1) : (nRcDepth + 1);
	}
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

//Function use: 输出结点值和平衡因子值
void vi(TElemType const e, int bf)
{
	printf("%4c%4d\n", e, bf);
}
void PreOrderTraverse(BiTree const T, void (*Visit)(TElemType const e, int bf))
{/*递归法先序遍历,注意回调函数的使用*/
	if (NULL != T)
	{
		Visit(T->data, T->bf);		//先访问根结点
		PreOrderTraverse(T->lchild, Visit);	//再访问左子树
		PreOrderTraverse(T->rchild, Visit);//最后访问右子树
	}
}

int main(int argc, char **argv)
{
	BiTree BT;
	printf("先序输入结点值,建立带平衡因子的二叉树:");
	CreateBiTree(&BT);
	cal_balance(BT);
	printf("结点值--平衡因子:\n");
	PreOrderTraverse(BT, vi);
	printf("\n");
	DestroyBiTree(&BT);

	return EXIT_SUCCESS;
}

