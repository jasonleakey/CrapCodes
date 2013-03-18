/*
 *  Establishment date:  2009-3-3
 *  Author            :	 jasonleakey
 *  Copyleft (R) 2009-3-3 jasonleakey
 *  <jasonleakey2005@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 *  adjcency_list.h: the definition of graph in the form of adjacency list
 */

#ifndef ADJCENCY_LIST_H_
#define ADJCENCY_LIST_H_

#define MAX_VEX_INFO_LEN 10
#define MAX_VEX_NUM 20
#define True 1
#define False 0

typedef enum {
	DG, DN, AG, AN	/* directed graph, directed network, undirected graph,
					undirected network in sequence */
} GraphKind;

typedef int InfoType;	//define the type of arc information is 'char'
typedef char VexType[MAX_VEX_INFO_LEN];

//the structure of arc
typedef struct ArcNode {
	int adjvex;	//the value of vertex the arc points to
	struct ArcNode *nextarc; //the pointer to next arc
	InfoType *info;	//store arc information
} ArcNode;

//structure of the vertex
typedef struct VNode {
	VexType data;	//the information of the vertex
	ArcNode *firstarc;	//the pointer of the first arc
} VNode, AdjList[MAX_VEX_NUM];

typedef struct {
	AdjList vertices;
	int vexnum;
	int arcnum;
	GraphKind kind;
} ALGraph;

extern int LocateVex(ALGraph G, VexType u);
extern int CreateGraph(ALGraph *pG);
extern void DestroyGraph(ALGraph *pG);
extern VexType* GetVex(ALGraph G, int nSeq);
extern int SetVex(ALGraph *pG, VexType v, VexType value);
extern int FirstAdjVex(ALGraph G, VexType v);
extern int NextAdjVex(ALGraph G, VexType v, VexType w);
extern int InsertVex(ALGraph *pG, VexType v);
extern int DeleteVex(ALGraph *pG, VexType v);
extern int InsertArc(ALGraph *pG, VexType v, VexType w);
extern int DeleteArc(ALGraph *pG, VexType v, VexType w);
//static void DFS(ALGraph G, VexType v)
extern void DFSTraverse(ALGraph G, void (*Visit)(VexType));
extern void BFSTraverse(ALGraph G, void (*Visit)(VexType));
extern void Display(ALGraph G);

#endif /* ADJCENCY_LIST_H_ */
