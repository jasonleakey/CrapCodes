/*
 * 		文件名称:	basic_op.c
 * 		创建时间:	2008-12-22
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
#include <assert.h>
#include <string.h>
#include "adjacency_matrix.h"

//Function use: 若图G中存在顶点u,则返回该顶点在图中位置,否则返回-1
int LocateVex(MGraph G, VertexType u)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
	{
		if (0 == strcmp(G.vexs[i], u))
		{
			return i;
		}
	}
	return -1;
}

//Function use: 采用邻接矩阵表示法,由文件构造没有相关信息的无向图G
Status CreateFAG(MGraph *pG)
{
	int i;
	int j;
	int k;
	char filename[15];
	VertexType va;
	VertexType vb;
	FILE *graphlist;
	printf("请输入数据文件名(graph.dat):");
	scanf("%s", filename);
	graphlist = fopen(filename, "r");
	if (NULL == graphlist)
	{
		perror("Open File Error!\n");
		exit(EXIT_FAILURE);
	}
	fscanf(graphlist, "%d", &(*pG).vexnum);	//顶点数
	fscanf(graphlist, "%d", &(*pG).arcnum);	//弧数
	//构造顶点向量
	for (i = 0; i < (*pG).vexnum; i++)
	{
		fscanf(graphlist, "%s", (*pG).vexs[i]);
	}
	//初始化邻接矩阵
	memset((*pG).arcs, '\0', (*pG).vexnum * (*pG).vexnum\
			* sizeof(ArcCell));
	//建立边, 无向图
	for (k = 0; k < (*pG).arcnum; k++)
	{
		fscanf(graphlist, "%s%s", va, vb);
		i = LocateVex(*pG, va);
		j = LocateVex(*pG, vb);
		(*pG).arcs[i][j].adj = 1;
	}
	fclose(graphlist);
	(*pG).kind = AG;

	return OK;
}

//Function use: 构造有向图
Status CreateDG(MGraph *pG)
{
	int i;
	int j;
	int k;
	int nLength;
	boolean bInfo;
	InfoType s[MAX_INFO];
	InfoType *info;
	VertexType va;
	VertexType vb;
	printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0):");
	scanf("%d%d%d", &(*pG).vexnum, &(*pG).arcnum, &bInfo);
	printf("请输入%d个顶点的值(<%d个字符):\n", (*pG).vexnum, MAX_NAME);
	//构造顶点向量
	for (i = 0; i < (*pG).vexnum; i++)
	{
		scanf("%s", (*pG).vexs[i]);
	}
	//初始化邻接矩阵
	memset((*pG).arcs, '\0', (*pG).vexnum * (*pG).vexnum\
			* sizeof(ArcCell));
	//有向图
	for (k = 0; k < (*pG).arcnum; k++)
	{
		scanf("%s%s%*c", va, vb);	//%*c吃掉回车符
		i = LocateVex(*pG, va);
		j = LocateVex(*pG, vb);
		(*pG).arcs[i][j].adj = 1;
		if (bInfo)
		{
			printf("请输入该弧相关信息(<%d个字符):", MAX_INFO);
			fgets(s, MAX_INFO, stdin);
			nLength = strlen(s);
			if (0 != nLength)
			{
				info = (InfoType *)malloc((nLength + 1) * sizeof(InfoType));
				strcpy(info, s);
				(*pG).arcs[i][j].info = info;
			}
		}
	}
	(*pG).kind = DG;

	return OK;
}


//Function use: 邻接矩阵表示法,构造有向网G
Status CreateDN(MGraph *pG)
{
	int i;
	int j;
	int k;
	VRType nWeight;
	int nLength;
	boolean bInfo;
	InfoType s[MAX_INFO];
	InfoType *info;
	VertexType va;
	VertexType vb;
	printf("请输入有向网G的顶点数,弧数,弧是否其它信息(是:1,否:0):");
	scanf("%d%d%d", &(*pG).vexnum, &(*pG).arcnum, &bInfo);
	printf("请输入%d个顶点的值(<%d个字符):\n", (*pG).vexnum, MAX_NAME);
	//构造顶点向量
	for (i = 0; i < (*pG).vexnum; i++)
	{
		scanf("%s", (*pG).vexs[i]);
	}
	//初始化邻接矩阵
	memset((*pG).arcs, INFINITY, (*pG).vexnum * (*pG).vexnum\
			* sizeof(ArcCell));
	//构造有向网
	printf("请输入%d条弧的弧尾 弧头 权值(空格隔开):", (*pG).arcnum);
	for (k = 0; k < (*pG).arcnum; k++)
	{
		scanf("%s%s%d%*c", va, vb, &nWeight);
		i = LocateVex((*pG), va);
		j = LocateVex((*pG), vb);
		(*pG).arcs[i][j].adj = nWeight;
		if (bInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符):", MAX_INFO);
			fgets(s, MAX_INFO, stdin);
			nLength = strlen(s);
			if (0 != nLength)
			{
				info = (char *)malloc((nLength + 1) * sizeof(char));
				strcpy(info, s);
				(*pG).arcs[i][j].info = info;
			}
		}
	}
	(*pG).kind = DN;

	return OK;
}


//Function use: 邻接矩阵创建无向图
Status CreateAG(MGraph *pG)
{
	int i;
	int j;
	int k;
	InfoType s[MAX_INFO];
	int nLength;
	boolean bInfo;	//是否带有相关信息的布尔变量
	VertexType va;	//顶点1和顶点2
	VertexType vb;
	printf("请输入无向图G的顶点数 边数 边是否带有相关信息:");
	scanf("%d%d%d", &(*pG).vexnum, &(*pG).arcnum, &bInfo);
	printf("请输入%d个顶点的值(<%d个字符):", (*pG).vexnum, MAX_VERTEX_NUM);
	//构造顶点向量
	for (i = 0; i < (*pG).vexnum; i++)
	{
		scanf("%s%*c", (*pG).vexs[i]);
	}
	//初始化邻接矩阵
	memset((*pG).arcs, '\0', (*pG).vexnum * (*pG).vexnum\
			* sizeof(ArcCell));
	//输入边信息
	for (k = 0; k < (*pG).arcnum; k++)
	{
		scanf("%s%s%*c", va, vb);
		i = LocateVex(*pG, va);
		j = LocateVex(*pG, vb);
		(*pG).arcs[i][j].adj = 1;
		if (bInfo)
		{
			printf("请输入该边的相关信息:");
			fgets(s, MAX_INFO, stdin);
			nLength = strlen(s);
			if (0 != nLength)
			{
				(*pG).arcs[i][j].info = (InfoType*)malloc(\
						(nLength + 1) * sizeof(InfoType));
				strcpy((*pG).arcs[i][j].info, s);
				(*pG).arcs[j][i].info = (*pG).arcs[i][j].info;
			}
		}
	}
	(*pG).kind = AG;

	return OK;
}

//Function use: 邻接矩阵构造无向网
Status CreateAN(MGraph *pG)
{
	int i;
	int j;
	int k;
	VRType nWeight;
	InfoType s[MAX_INFO];
	VertexType va;	//顶点1和顶点2
	VertexType vb;
	boolean bInfo;	//是否有相关信息
	int nLength;	//相关信息长度
	printf("请输入无向网的顶点数 边数 边是否有相关信息:");
	scanf("%d%d%d", &(*pG).vexnum, &(*pG).arcnum, &bInfo);
	//构造顶点向量
	printf("请输入%d个顶点值:", (*pG).vexnum);
	for (i = 0; i < (*pG).vexnum; i++)
	{
		scanf("%s%*c", (*pG).vexs[i]);
	}
	//初始化邻接矩阵
	memset((*pG).arcs, INFINITY, (*pG).vexnum * (*pG).vexnum\
			* sizeof(ArcCell));
	//构造边
	printf("请输入顶点1 顶点2 权值:");
	for (k = 0; k < (*pG).arcnum; k++)
	{
		scanf("%s%s%d%*c", va, vb, &nWeight);
		i = LocateVex(*pG, va);
		j = LocateVex(*pG, vb);
		(*pG).arcs[i][j].adj = nWeight;
		if (bInfo)
		{
			printf("请输入该边的相关信息:");
			fgets(s, MAX_INFO, stdin);
			nLength = strlen(s);
			if (0 != nLength)
			{
				(*pG).arcs[i][j].info = (InfoType*)malloc(\
						(nLength + 1) * sizeof(InfoType));
				strcpy((*pG).arcs[i][j].info, s);
				(*pG).arcs[j][i].info = (*pG).arcs[i][j].info;
			}
		}
	}
	(*pG).kind = AN;

	return OK;
}

//Function use: 选择创建各类图
Status CreateGraph(MGraph *pG)
{
	int nSel;
	printf("请输入图的类型:(0:有向图 1:有向网 2.无向图 3.无向网:");
	scanf("%d", &nSel);
	switch (nSel)
	{
		case 0:
			CreateDG(pG);
			break;
		case 1:
			CreateDN(pG);
			break;
		case 2:
			CreateAG(pG);
			break;
		case 3:
			CreateAN(pG);
			break;
		default:
			printf("输入有误!\n");
			return ERROR;
	}

	return OK;
}

//Function use: 销毁图
void DestroyGraph(MGraph *pG)
{
	int i;
	int j;
	if ((*pG).kind < 2)	 //对于有向
	{
		for (i = 0; i < (*pG).vexnum; i++)
		{
			for (j = 0; j < (*pG).vexnum; j++)
			{
				//判断该弧存在
				if ((0 == (*pG).kind\
					&& 1 == (*pG).arcs[i][j].adj)\
					|| (1 == (*pG).kind\
					&& INFINITY != (*pG).arcs[i][j].adj))
				{
					if (NULL != (*pG).arcs[i][j].info)
					{
						free((*pG).arcs[i][j].info);
						(*pG).arcs[i][j].info = NULL;
					}
				}
			}
		}
	}
	else	//无向
	{
		for (i = 0; i < (*pG).vexnum; i++)
		{
			for (j = 0; j < (*pG).vexnum; j++)
			{
				//判断边是否存在
				if ((2 == (*pG).kind\
					&& 1 == (*pG).arcs[i][j].adj)
					|| (3 == (*pG).kind
					&& INFINITY != (*pG).arcs[i][j].adj))
				{
					if (NULL != (*pG).arcs[i][j].info)
					{
						free((*pG).arcs[i][j].info);
						(*pG).arcs[i][j].info =\
							(*pG).arcs[j][i].info = NULL;
					}
				}
			}
		}
	}
	(*pG).vexnum = 0;
	(*pG).arcnum = 0;
}

//Function use: 根据某个顶点的序号nSeq, 返回nSeq的值
VertexType* GetVex(MGraph G, int nSeq)
{
	if (nSeq >= G.vexnum || nSeq < 0)
	{
		exit(EXIT_FAILURE);
	}
	return &G.vexs[nSeq];
}

//Function use:
Status PutVex(MGraph *pG, VertexType nOldValue, VertexType nNewValue)
{
	int i = 0;
	i = LocateVex(*pG, nOldValue);
	if (0 < i)
	{
		strcpy((*pG).vexs[i], nNewValue);
		return OK;
	}
	return ERROR;
}

//Function use: v为G中某个顶点,函数返回v的第一个邻接顶点的序号,若无,返回-1
int FirstAdjVex(MGraph G, VertexType v)
{
	int i = 0;
	int j = 0;
	int nSeq = 0;
	nSeq = LocateVex(G, v);
	if (0 < nSeq)
	{
		if (DN == G.kind || AN == G.kind)
		{
			j = INFINITY;
		}
		for (i = 0; i < G.vexnum; j++)
		{
			if (G.arcs[i][j].adj != j)
			{
				return i;
			}
		}
	}
	return -1;
}

//Function use: w是v的邻接顶点,返回v的(相对于w的)下一个邻接点的序号,若无,返回-1
int NextAdjVex(MGraph G, VertexType v, VertexType w)
{
	int i = 0;
	int j = 0;
	int nSeqV = 0;
	int nSeqW = 0;
	nSeqV = LocateVex(G, v);
	nSeqW = LocateVex(G, w);
	if (0 <= v && 0 <= w)
	{
		if (DN == G.kind || AN == G.kind)
		{
			j = INFINITY;
		}
		for (i = nSeqW; i < G.vexnum; i++)
		{
			if (G.arcs[i][j].adj != j)
			{
				return i;
			}
		}
	}
	return -1;
}

//Function use: 增加新顶点v(不增加相应的弧,等InsertArc做)
void InsertVex(MGraph *pG, VertexType v)
{
	int i = (*pG).vexnum++;
	int j = 0;
	if ((*pG).vexnum > MAX_VERTEX_NUM)
	{
		perror("Too vexnum!\n");
		exit(EXIT_FAILURE);
	}
	strcpy((*pG).vexs[i], v);
	if (DN == (*pG).kind || AN == (*pG).kind)
	{
		for (j = 0; j < (*pG).vexnum; j++)
		{
			(*pG).arcs[j][i].adj = INFINITY;
			(*pG).arcs[i][j].adj = INFINITY;
			(*pG).arcs[j][i].info = NULL;
			(*pG).arcs[i][j].info = NULL;
		}
	}
	else
	{
		for (j = 0; j < (*pG).vexnum; j++)
		{
			(*pG).arcs[j][i].adj = 0;
			(*pG).arcs[i][j].adj = 0;
			(*pG).arcs[j][i].info = NULL;
			(*pG).arcs[i][j].info = NULL;
		}
	}
}

//Function use: 删除G中顶点v及相关的弧
Status DeleteVex(MGraph *pG, VertexType v)
{
	int i;
	int j;
	int k;
	int m = 0;
	k = LocateVex(*pG, v);
	if (k < 0)
	{
		return ERROR;
	}
	if (DN == (*pG).kind || AN == (*pG).kind)
	{
		m = INFINITY;
	}
	for (j = 0; j < (*pG).vexnum; j++)
	{
		if ((*pG).arcs[j][k].adj != m)
		{
			if (NULL != (*pG).arcs[j][k].info)
			{
				free((*pG).arcs[j][k].info);
				(*pG).arcs[j][k].info = NULL;
			}
			(*pG).arcnum--;
		}
	}
	if (DG == (*pG).kind || AG == (*pG).kind)
	{
		for (j = 0; j < (*pG).vexnum; j++)
		{
			if (NULL != (*pG).arcs[k][j].info)
			{
				free((*pG).arcs[k][j].info);
				(*pG).arcs[k][j].info = NULL;
			}
			(*pG).arcnum--;
		}
	}
	for (j = k + 1; j < (*pG).vexnum; j++)
	{
		strcpy((*pG).vexs[j - 1], (*pG).vexs[j]);
	}
	for (i = 0; i < (*pG).vexnum; i++)
	{
		for (j = k + 1; j < (*pG).vexnum; j++)
		{
			(*pG).arcs[i][j - 1] = (*pG).arcs[i][j];
		}
	}
	for (i = 0; i < (*pG).vexnum; i++)
	{
		for (j = k + 1; j < (*pG).vexnum; j++)
		{
			(*pG).arcs[j - 1][i] = (*pG).arcs[j][i];
		}
	}
	(*pG).vexnum--;

	return OK;
}

//Function use: 在G中增加弧<v,w>, 若是无向的,另增加<w,v>
Status InsertArc(MGraph *pG, VertexType v, VertexType w)
{
	int i;
	int nLength;
	InfoType *info;
	InfoType s[MAX_INFO];
	int nSeqV = LocateVex(*pG, v);
	int nSeqW = LocateVex(*pG, w);
	if (nSeqV < 0 || nSeqW < 0)
	{
		perror("No such Vertex!\n");
		return ERROR;
	}
	else
	{
		(*pG).arcnum++;
		if (DN == (*pG).kind || AN == (*pG).kind)
		{
			printf("请输入此弧或边的权值:");
			scanf("%d", &(*pG).arcs[nSeqV][nSeqW].adj);
		}
		else
		{
			(*pG).arcs[nSeqV][nSeqW].adj = 1;
		}
		printf("是否有相关信息?(0:无 1:有):");
		scanf("%d%*c", &i);
		if (1 == i)
		{
			printf("请输入相关信息:");
			fgets(s, MAX_INFO, stdin);
			nLength = strlen(s);
			if (0 != nLength)
			{
				info = (InfoType*)malloc((nLength + 1) * sizeof(InfoType));
				strcpy(info, s);
				(*pG).arcs[nSeqV][nSeqW].info = info;
			}
		}
		if ((*pG).kind > 1)		//无向
		{
			(*pG).arcs[nSeqW][nSeqV].adj = (*pG).arcs[nSeqV][nSeqW].adj;
			(*pG).arcs[nSeqW][nSeqV].info = (*pG).arcs[nSeqV][nSeqW].info;
		}
	}

	return OK;
}

//Function use: G中删除弧<v,w>,若是无向,还删除<w,v>
Status DeleteArc(MGraph *pG, VertexType v, VertexType w)
{
	int nSeqV;
	int nSeqW;
	nSeqV = LocateVex(*pG, v);
	nSeqW = LocateVex(*pG, w);
	if (nSeqV < 0 || nSeqW < 0)
	{
		return ERROR;
	}
	else
	{
		if (DN == (*pG).kind || AN == (*pG).kind)
		{
			(*pG).arcs[nSeqV][nSeqW].adj = INFINITY;
		}
		else
		{
			(*pG).arcs[nSeqV][nSeqW].adj = 0;
		}
		if (NULL != (*pG).arcs[nSeqV][nSeqW].info)
		{
			free((*pG).arcs[nSeqV][nSeqW].info);
			(*pG).arcs[nSeqV][nSeqW].info = NULL;
		}
		if (AG == (*pG).kind || AN == (*pG).kind)
		{
			(*pG).arcs[nSeqW][nSeqV].adj = (*pG).arcs[nSeqV][nSeqW].adj;
			(*pG).arcs[nSeqW][nSeqV].info = NULL;
		}
		(*pG).arcnum--;
	}

	return OK;
}

boolean visited[MAX_VERTEX_NUM];	//访问标志数组(全局量)
Status (*VisitFunc)(VertexType);	//函数变量

//Function use: 从第nSeqV个顶点出发深度遍历图
void DFS(MGraph G, int nSeqV)
{
	VertexType v;
	VertexType w;
	int nSeqW;
	visited[nSeqV] = TRUE;
	VisitFunc(G.vexs[nSeqV]);
	strcpy(v, *GetVex(G, nSeqV));
	for (nSeqW = FirstAdjVex(G, v);\
		nSeqW >= 0; nSeqW = NextAdjVex(G, v, w))
	{
		if (!visited[nSeqW])
		{
			DFS(G, nSeqW);
		}
	}
}

//Function use: 从第1个顶点起,深度优先遍历图,并对每个顶点
//调用函数Visit,一次且仅一次,一旦Visit()失败,则操作失败
void DFSTraverse(MGraph G, Status (*Visit)(VertexType))
{
	int nSeqV;
	VisitFunc = Visit;	//使用全局变量VisitFunc,使DFS不必设函数指针参数
	for (nSeqV = 0; nSeqV < G.vexnum; nSeqV++)
	{
		if (!visited[nSeqV])
		{
			DFS(G, nSeqV);
		}
	}
	printf("\n");
}



//Function use: 输出邻接矩阵
void Display(MGraph G)
{
	int i;
	int j;
	char chSK[7];
	char chAdj[3];
	switch (G.kind)
	{
		case AG:
			strcpy(chSK, "无向图\0");
			strcpy(chAdj, "边\0");
			break;
		case DN:
			strcpy(chSK, "有向网\0");
			strcpy(chAdj, "弧\0");
			break;
		case AN:
			strcpy(chSK, "无向网\0");
			strcpy(chAdj, "弧\0");
			break;
		case DG:
			strcpy(chSK, "有向图\0");
			strcpy(chAdj, "边\0");
			break;
		default:
			perror("Error!unknown graph kind\n");
			exit(EXIT_FAILURE);
	}
	printf("%d个顶点%d条%s的%s\n", G.vexnum, G.arcnum, chAdj, chSK);
	//输出各顶点名称
	for (i = 0; i < G.vexnum; i++)
	{
		printf("G.vexs[%d]=%s\n", i, G.vexs[i]);
	}
	//输出G.arcs.adj
	printf("G.arcs.adj:\n");
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			printf("%6d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
	printf("G.arcs.info:\n");
	if (G.kind < 2)	//有向
	{
		for (i = 0; i < G.vexnum; i++)
		{
			for (j = 0; j < G.vexnum; j++)
			{
				if (NULL != G.arcs[i][j].info)
				{
					printf("%5s %11s    %s\n", G.vexs[i],\
							G.vexs[j], G.arcs[i][j].info);
				}
			}
			printf("\n");
		}
	}
	else
	{
		for (i = 0; i < G.vexnum; i++)
		{
			for (j = i + 1; j < G.vexnum; j++)
			{
				if (NULL != G.arcs[i][j].info)
				{
					printf("%5s %11s    %s\n", G.vexs[i],\
							G.vexs[j], G.arcs[i][j].info);
				}
			}
			printf("\n");
		}
	}
}
