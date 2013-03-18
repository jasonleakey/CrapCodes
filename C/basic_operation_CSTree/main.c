/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-16
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
#include "CSTree.h"

void vi(TElemType c)
{
	printf("%c", c);
}

int main(int argc, char **argv)
{
	CSTree T;
	TElemType e;
	TElemType e1;
	InitTree(&T);
	printf("构造空树后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",\
			TreeEmpty(T), Root(T), TreeDepth(T));
	CreateTree(&T);
	printf("构造空树后,树空否? %d(1:是 0:否) 树根为%c 树的深度为%d\n",\
				TreeEmpty(T), Root(T), TreeDepth(T));
	printf("先根遍历树T:\n");
	PreOrderTraverse(T, vi);
	printf("\n请输入等修改的结点的值 新值:");
	scanf("%c%*c%c%*c", &e, &e1);
	Assign(&T, e, e1);
	printf("后根遍历修改后的树T:\n");
	PostOrderTraverse_recurssion1(T, vi);
	printf("\n");
	printf("PostOrderTraverse_recurssion1 complete!\n");
	PostOrderTraverse_recurssion2(T, vi);
	printf("\n");
	printf("PostOrderTraverse_recurssion2 complete!\n");
	printf("\n%c的双亲是%c, 长子是%c,下一个兄弟是%c\n", e1, Parent(T, e1),\
			LeftChild(T, e1), RightSibling(T, e1));
	printf("层序遍历树:\n");
	LevelOrderTraverse(T, vi);
	DestroyTree(&T);
	return EXIT_SUCCESS;
}


