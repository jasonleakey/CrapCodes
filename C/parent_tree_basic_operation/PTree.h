/*
 * 		文件名称:	PTree.h
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

#ifndef PTREE_H_
#define PTREE_H_

#define MAX_TREE_SIZE 100

typedef char TElemType;
#define Nil ' '
typedef int boolean;
typedef int Status;
#define TRUE 1
#define FALSE 0

typedef struct {
	TElemType data;
	int parent;
} PTNode;

typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int node_count;
} PPTree, *PTree;

/*init a parent tree*/
extern void InitPTree(PTree *pT);

/* destroy a parent tree */
extern void DestroyPTree(PTree *pT);

/* create a parent tree */
extern Status CreatePTree(PTree *pT);

/* determine whether the parent tree is empty*/
extern boolean PTreeEmpty(PTree const T);

/* calculate the depth of parent tree*/
extern int PTreeDepth(PTree const T);

/* return data of root node*/
extern TElemType Root(PTree const T);

/* return data of the i-numth node value */
extern TElemType Value(PTree const T, int i);

/* replace the current value with new value*/
extern Status Assign(PTree *pT, TElemType const cur_e, TElemType const value);

/* return data of parent node */
extern TElemType Parent(PTree const T, TElemType const cur_e);

/* return data of lefechild node */
extern TElemType LeftChild(PTree const T, TElemType const cur_e);

/* return data of rightsibiling node */
extern TElemType RightSibling(PTree const T, TElemType const cur_e);

/* ??? */
extern void Print(PTree const T);

/* Print e*/
extern void vi(TElemType const e);

/* traverse the whole parent tree */
extern void Traverse(PTree const T, void(*Visit)(TElemType const));

#endif /* PTREE_H_ */
