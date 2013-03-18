/*
 * 		文件名称:	basic_operate_BiThrTree.c
 * 		创建时间:	2008-10-19
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


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "threaded_tree.h"

inline Status vi(Elemtype c)
{
	printf("%c", c);
	return OK;
}

Status Create_BiThrTree(BiThrTree *pT)
{/*按先序输入线索二叉树的结点,建立二叉树*/
	Elemtype ch;
	scanf("%c", &ch);
	if (ch == ' ')
	{
		*pT = NULL;
	}
	else
	{
		*pT = (BiThrTree)malloc(sizeof(BiThrNode));
		if (*pT == NULL)
		{
			exit(OVERFLOW);
		}
		(*pT)->data = ch;
		Create_BiThrTree(&((*pT)->lchild));
		if ((*pT)->lchild != NULL)
		{
			(*pT)->LTag = Link;
		}
		Create_BiThrTree(&((*pT)->rchild));
		if ((*pT)->rchild != NULL)
		{
			(*pT)->RTag = Link;
		}
	}
	return OK;
}

BiThrTree g_pre;
void InThreading(BiThrTree p)
{/*递归中序遍历二叉树并建立线索*/
	if (NULL != p)
	{
		InThreading(p->lchild);
		if (NULL == p->lchild)
		{
			p->LTag = Thread;
			p->lchild = g_pre;
		}
		if (NULL == g_pre->rchild)
		{
			g_pre->RTag = Thread;
			g_pre->rchild = p;
		}
		g_pre = p;
		InThreading(p->rchild);
	}
}


/*函数有误*/
Status InOrderThreading(BiThrTree *pThrt, BiThrTree T)
{/*建立中序线索二叉树*/
	*pThrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (NULL == *pThrt)
	{
		puts("No memory for pThrt!\n");
		exit(OVERFLOW);
	}
	(*pThrt)->LTag = Link;
	(*pThrt)->RTag = Thread;
	(*pThrt)->rchild = *pThrt;
	if (NULL == T)
	{
		(*pThrt)->lchild = *pThrt;
	}
	else
	{
		(*pThrt)->lchild = T;
		g_pre = *pThrt;
		InThreading(T);
		g_pre->rchild = *pThrt;
		g_pre->RTag = Thread;
		(*pThrt)->rchild = g_pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree pThrt, Status (*Visit)(Elemtype))
{/*中序遍历二叉线索树的非递归算法*/
	assert(NULL != pThrt->lchild);
	BiThrTree p;
	p = pThrt->lchild;
	while (pThrt != p)
	{
		//走到左子树尽头
		while (Link == p->LTag)
		{
			p = p->lchild;
		}
		//访问结点
		if (OK != Visit(p->data))
		{
			return ERROR;
		}
		//访问后继结点
		while (p->RTag == Thread && p->rchild != pThrt)
		{
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}

void DestroyBiTree(BiThrTree *pT)
{
	if (NULL != *pT)
	{
		if (Link == (*pT)->LTag)
		{
			DestroyBiTree(&(*pT)->lchild);
		}
		if (Link == (*pT)->RTag)
		{
			DestroyBiTree(&(*pT)->rchild);
		}
		printf("销毁%c\n", (*pT)->data);
		free(*pT);
		*pT = NULL;
	}
}


void DestroyBiThrTree(BiThrTree *pThrt)
{//连头结点和二叉线索树一同销毁
	assert(NULL != *pThrt);
	if (NULL != (*pThrt)->lchild)
	{
		DestroyBiTree(&(*pThrt)->lchild);
		printf("销毁pThrt!\n");
		free(*pThrt);
		*pThrt = NULL;
	}
	printf("销毁完成!\n");
}
