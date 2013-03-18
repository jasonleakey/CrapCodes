/*
 * 		文件名称:	CSTree.h
 * 		创建时间:	2008-12-12
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


#ifndef CSTREE_H_
#define CSTREE_H_

typedef char TElemType;

/* data structure of child-sibling tree */
typedef struct CSNode {
	TElemType data;
	struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

typedef int Status;
typedef int boolean;
#define Nil ' '
#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

/* init a child-sibling tree */
extern Status InitTree(CSTree *pT);

/* destroy a child-sibling tree */
extern void DestroyTree(CSTree *pT);

/* Create a child-sibling tree */
extern Status CreateTree(CSTree *pT);

extern Status TreeEmpty(CSTree const T);

extern int TreeDepth(CSTree const T);

extern TElemType Root(CSTree const T);

extern CSTree Point_non_recurssion(CSTree const T, TElemType const e);

extern CSTree Point_recurssion(CSTree const T, TElemType const e);

extern Status Assign(CSTree *pT, TElemType const cur_e, TElemType const value);

extern TElemType Parent(CSTree const T, TElemType const cur_e	);

extern TElemType LeftChild(CSTree const T, TElemType const cur_e);

extern TElemType RightSibling(CSTree const T, TElemType const cur_e);

extern void PreOrderTraverse(CSTree T, void(*Visit)(TElemType));

extern void PostOrderTraverse_recurssion1(CSTree T, void(*Visit)(TElemType));

extern void PostOrderTraverse_recurssion2(CSTree const T, void (*Visit)(TElemType));

extern void LevelOrderTraverse(CSTree const T, void(*Visit)(TElemType));

#endif /* CSTREE_H_ */
