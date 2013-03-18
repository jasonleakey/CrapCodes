/*
 * 		文件名称:	threaded_tree.h
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

#ifndef THREADED_TREE_H_
#define THREADED_TREE_H_

typedef char Elemtype;
typedef enum {Link, Thread} PointerThr;

typedef struct BiThrNode {
	PointerThr LTag, RTag;
	Elemtype data;
	struct BiThrNode *lchild, *rchild;
}BiThrNode, *BiThrTree;

typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

/*按先序输入线索二叉树的结点,建立二叉树*/
extern Status Create_BiThrTree(BiThrTree *T);

/*递归中序遍历二叉树并建立线索*/
extern void InThreading(BiThrTree p);

/*建立中序线索二叉树*/
extern Status InOrderThreading(BiThrTree *Thrt, BiThrTree T);

/*中序遍历二叉线索树的非递归算法*/
extern	Status InOrderTraverse_Thr(BiThrTree T, Status (*Visit)(Elemtype));

extern Status vi(Elemtype c);

extern void DestroyBiTree(BiThrTree *pT);

extern void DestroyBiThrTree(BiThrTree *pThrt);
#endif /* THREADED_TREE_H_ */
