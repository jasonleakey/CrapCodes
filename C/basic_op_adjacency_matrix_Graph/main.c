/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-31
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
#include "adjacency_matrix.h"

//Function use: 输出顶点向量
Status vi(VertexType i)
{
	printf("%s", i);
	return OK;
}

int main(int argc, char **argv)
{
	int i;
	int j;
	int k;
	int n;
	VertexType v;
	VertexType w;
	MGraph G;
	CreateFAG(&G);
	Display(G);
	printf("修改顶点的值, 请输入原值 新值:");
	scanf("%s%s", v, w);
	PutVex(&G, v, w);
	printf("深度优先搜索的结果:\n");
	DFSTraverse(G, vi);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(G, vi);
	printf("删除一条边或弧,请输入待删除边或弧的弧尾 弧头:");
	scanf("%s%s", v, w);
	DeleteArc(&G, v, w);
	Display(G);
	DestroyGraph(&G);
	printf("请顺序选择有向图,有向图,无向图,无向网\n");
	for (i = 0; i < 4; i++)
	{
		CreateGraph(&G);
		Display(G);
		printf("插入新顶点, 输入其值:");
		scanf("%s", v);
		InsertVex(&G, v);
		printf("插入与新顶点有关的弧或边, 请输入边或弧数:");
		scanf("%d", &n);
		for (k = 0; k < n; k++)
		{
			printf("请输入另一顶点的值:");
			scanf("%s", w);
			if (G.kind <= 1)
			{
				printf("对于有向图或网, 请输入另一顶点的方向(0:弧头 1:弧尾):");
				scanf("%d", &j);
				if (0 == j)
				{
					InsertArc(&G, v, w);
				}
				else
				{
					InsertArc(&G, w, v);
				}
			}
			else
			{
				InsertArc(&G, v, w);
			}
		}
		Display(G);
		printf("删除顶点及相关的弧或边,请输入顶点的值:");
		scanf("%s", v);
		DeleteVex(&G, v);
		Display(G);
		DestroyGraph(&G);
	}

	return EXIT_SUCCESS;
}


