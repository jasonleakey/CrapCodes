/*
 * Bithread.h
 *
 *  Created on: 2008-11-10
 *      Author: jasonleakey
 */

#ifndef BITREE_H_
#define BITREE_H_

typedef char TElemType;
typedef int Status;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

#define TRUE 1
#define FALSE 0
#ifndef OK
#define OK 1
#endif
#define ERROR -1

Status InitBiTree(BiTree *T);

void CreateBiTree(BiTree *T);

void DestroyBiTree(BiTree *T);

/*判断二叉树是否为空的宏*/
#define BITREEEMPTY(T)	((NULL == (T)) ? TRUE : FALSE)

int BiTreeDepth(BiTree const T);

/*此宏返回根结点的值(类型为TElemType),若根结点为空,则返回空格*/
#define ROOT(T) ((NULL != (T)) ? ((T)->data) : ' ')
/*此宏返回p指针所指向结点的值*/
#define VALUE(p) ((NULL != (p)) ? ((p)->data) : ' ')
/*此宏将p指针所指向结点的值赋为value*/
#define ASSIGN(p, value) ((p)->data = (value))

TElemType Parent(BiTree const T, TElemType const e);

BiTree Point(BiTree const T, TElemType const s);

TElemType LeftChild(BiTree const T, TElemType const e);

TElemType RightChild(BiTree const T, TElemType const e);

TElemType LeftSibling(BiTree const T, TElemType const e);

TElemType RightSibling(BiTree const T, TElemType const e);

Status InsertChild(BiTree p, const  int LR, BiTree const c);

Status DeleteChild(BiTree p, const  int LR);

void PreOrderTraverse(BiTree const T, Status (*Visit)(TElemType));

void PreOrderUnrec1(BiTree T, Status (*Visit)(TElemType));

void PreOrderUnrec2(BiTree T, Status (*Visit)(TElemType));

void PreOrderUnrec3(BiTree T, Status (*Visit)(TElemType));

void InOrderTraverse(BiTree const T, Status (*Visit)(TElemType));

Status InOrderTraverse1_nonrecursive(BiTree const T, Status (*Visit)(TElemType));

Status InOrderTraverse2_nonrecursive(BiTree const T, Status (*Visit)(TElemType));

void InOrderUnrec(BiTree T, Status (*Visit)(TElemType const));

void PostOrderTraverse(BiTree const T, Status (*Visit)(TElemType));

void LevelOrderTraverse(BiTree T, Status (*Visit)(TElemType));


inline Status visitT(TElemType const e);
#endif /* BITHREAD_H_ */
