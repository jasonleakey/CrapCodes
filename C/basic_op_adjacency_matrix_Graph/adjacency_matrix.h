/*
 * 		文件名称:	adjacency_matrix.h
 * 		创建时间:	2008-12-21
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

#ifndef ADJACENCY_MATRIX_H_
#define ADJACENCY_MATRIX_H_

#include <limits.h>
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define MAX_INFO 20
#define MAX_NAME 5		//顶点字符串的最大长度+1

typedef enum {
	DG, DN, AG, AN	//依次为有向图,有向网,无向图,无向网
} GraphKind;

typedef int VRType;
typedef char InfoType;
typedef struct {
	VRType adj;		//顶点关系类型.对无权图,,用1/0表示相邻否;带权图,则为权值
	InfoType *info;	//弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType[MAX_NAME];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];	//顶点向量
	AdjMatrix arcs;	//邻接矩阵
	int vexnum;	//顶点数
	int arcnum;	//弧数
	GraphKind kind;
} MGraph;

//c1.h
#define OK 0
#define ERROR 1
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int boolean;

extern int LocateVex(MGraph G, VertexType u);
extern Status CreateFAG(MGraph *pG);
extern Status CreateDG(MGraph *pG);
extern Status CreateDN(MGraph *pG);
extern Status CreateAG(MGraph *pG);
extern Status CreateAN(MGraph *pG);
extern VertexType* GetVex(MGraph G, int nSeq);
extern void DestroyGraph(MGraph *pG);
extern Status PutVex(MGraph *pG, VertexType nOldValue, VertexType nNewValue);
extern int FirstAdjVex(MGraph G, VertexType v);
extern int NextAdjVex(MGraph G, VertexType v, VertexType w);
extern void InsertVex(MGraph *pG, VertexType v);
extern Status DeleteVex(MGraph *pG, VertexType v);
extern Status InsertArc(MGraph *pG, VertexType v, VertexType w);
extern Status DeleteArc(MGraph *pG, VertexType v, VertexType w);
extern void DFS(MGraph G, int nSeqV);
extern void DFSTraverse(MGraph G, Status (*Visit)(VertexType));
extern void BFSTraverse(MGraph G, Status (*Visit)(VertexType));
extern void Display(MGraph G);
extern Status CreateGraph(MGraph *pG);

#endif /* ADJACENCY_MATRIX_H_ */
