/*
 *  Establishment date:  2009-3-4
 *  Author            :	 jasonleakey
 *  Copyleft (R) 2009-3-4 jasonleakey
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
 *  basic_op.c: basic operations of adjacency list graph.
 */

#include "adjcency_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//search for the serial number according to the vertex name,and return it
//if not found, return -1
int LocateVex(ALGraph G, VexType u)
{
	int i;

	for (i = 0; i < G.vexnum; i++)
	{
		if (0 == strcmp(G.vertices[i].data, u))
		{
			return i;
		}
	}
	return -1;
}

//create a graph without arc information
int CreateGraph(ALGraph *pG)
{
	int i;
	int j;
	int k;
	int nWeight;
	VexType chV;
	VexType chW;
	ArcNode* p;
	int gk;
	//select graph kind
	printf("Input Graph kind(0.DG 1.DN 2.AG 3.AN):");
	while (1 != scanf("%d", &gk) && gk != EOF)
	{
		fflush(NULL);	//clean up the standard input
	}
	(*pG).kind = gk;
	//vertex and arc account
	printf("Input vexnum and arcnum:");
	while (2 != scanf("%d%d", &i, &j) && i == EOF && j == EOF)
	{
		fflush(NULL);
	}
	(*pG).vexnum = i;
	(*pG).arcnum = j;
	//get vertex name
	printf("Input %d vertex name(<%d chars):",\
			(*pG).vexnum, MAX_VEX_INFO_LEN);
	for (i = 0; i < (*pG).vexnum; i++)
	{
		scanf("%s", (*pG).vertices[i].data);
		(*pG).vertices[i].firstarc = NULL;
	}
	if (1 == (*pG).kind || 3 == (*pG).kind)
	{//if network, get arc weight
		printf("Input every arc's weight,arc tailer,arc head In Order:\n");
	}
	else
	{
		printf("Input every arc's tailer and head In order:");
	}
	//create arc link list
	for (k = 0; k < (*pG).arcnum; k++)
	{
		if (1 == (*pG).kind || 3 == (*pG).kind)
		{
			scanf("%d%s%s", &nWeight, chV, chW);
		}
		else
		{
			scanf("%s%s", chV, chW);
		}
		i = LocateVex(*pG, chV);
		j = LocateVex(*pG, chW);
		p = (ArcNode*)malloc(sizeof(ArcNode));//create arc link list
		p->adjvex = j;
		if (1 == (*pG).kind || 3 == (*pG).kind)
		{
			p->info = (InfoType*)malloc(sizeof(InfoType));
			*(p->info) = nWeight;
		}
		else
		{
			p->info = NULL;
		}
		p->nextarc = (*pG).vertices[i].firstarc;
		(*pG).vertices[i].firstarc = p;
		//undirected graph or network,create another arc node
		if ((*pG).kind >= 2)
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if (AN == (*pG).kind) //undirected network
			{
				p->info = (InfoType*)malloc(sizeof(InfoType));
				*(p->info) = nWeight;
			}
			else
			{
				p->info = NULL;
			}
			p->nextarc = (*pG).vertices[j].firstarc;
			(*pG).vertices[j].firstarc = p;
		}
	}

	return 0;
}


//Destroy the graph and release resource
void DestroyGraph(ALGraph *pG)
{
	int i = 0;
	ArcNode *p;
	for (i = 0; i < (*pG).vexnum; i++)
	{
		//p points to the first arc node
		p = (*pG).vertices[i].firstarc;
		while (NULL != p)
		{
			(*pG).vertices[i].firstarc = p->nextarc;
			if (NULL != p->info)
			{
				free(p->info);
			}
			free(p);
			p = NULL;
			p = (*pG).vertices[i].firstarc;
		}
	}
	(*pG).vexnum = 0;
	(*pG).arcnum = 0;
}

//return the vertex's name according to the serial number
VexType* GetVex(ALGraph G, int nSeq)
{
	if (nSeq > G.vexnum || nSeq < 0)
	{
		return NULL;
	}
	return &G.vertices[nSeq].data;
}

//modify the 'v'-named vertex the name to be new name 'value'
int SetVex(ALGraph *pG, VexType v, VexType value)
{
	int i = 0;
	if (-1 == (i = LocateVex(*pG, v)))
	{
		return -1;
	}
	//replace it with new value
	strncpy((*pG).vertices[i].data, value, MAX_VEX_INFO_LEN);

	return 1;
}

//return the first adjacency vertex next to 'v'
//if the 'v' does not exist, return -2
//if 'v' has no adjacency vertex, return -1
int FirstAdjVex(ALGraph G, VexType v)
{
	int i = 0;
	if (-1 == (i = LocateVex(G, v)))
	{
		return -2;
	}
	if (NULL == G.vertices[i].firstarc)
	{
		return -1;
	}
	return (G.vertices[i].firstarc)->adjvex;
}

//return the next adjvex number with 'w'
int NextAdjVex(ALGraph G, VexType v, VexType w)
{
	ArcNode *p;
	int nSeqV;
	int nSeqW;
	nSeqV = LocateVex(G, v);
	nSeqW = LocateVex(G, w);
	if (-1 == nSeqV || -1 == nSeqW)
	{//'v' or 'w' is not existed.
		return -2;
	}
	//search the 'v'2'w' arc node
	p = G.vertices[nSeqV].firstarc;
	while (NULL != p && p->adjvex != nSeqW)
	{
		p = p->nextarc;
	}
	//not found.
	if (NULL == p || NULL == p->nextarc)
	{
		return -1;
	}
	//found it
	return p->nextarc->adjvex;
}

//insert a vertex into the graph
int InsertVex(ALGraph *pG, VexType v)
{
	if ((*pG).vexnum >= MAX_VEX_NUM)
	{
		printf("No more vertex can be inserted\n");
		return -1;
	}
	//create a new vertex vector
	strcpy((*pG).vertices[(*pG).vexnum].data, v);
	(*pG).vertices[(*pG).vexnum].firstarc = NULL;
	(*pG).vexnum++;

	return 0;
}

//find the 'v' vertex and delete it from the graph
int DeleteVex(ALGraph *pG, VexType v)
{
	int nSeq = 0;
	int j = 0;
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	//cannot find this vertex
	if (-1 == (nSeq = LocateVex(*pG, v)))
	{
		printf("No such vertex!\n");
		return -1;
	}
	//delete arcs which's out-degree is 'v'
	p = (*pG).vertices[nSeq].firstarc;
	while (NULL != p)
	{
		if (0 != (*pG).kind % 2)
		{
			free(p->info);
		}
		(*pG).vertices[nSeq].firstarc = p->nextarc;
		free(p);
		p = NULL;
		p = (*pG).vertices[nSeq].firstarc;
		//decrease arc account in one
		(*pG).arcnum--;
	}
	//the following vertex move up
	for (j = nSeq; j < (*pG).vexnum; j++)
	{
		(*pG).vertices[nSeq] = (*pG).vertices[nSeq + 1];
	}
	//delete arcs which's in-degree is 'v'
	//if necessary, modify arc's information
	for (j = 0; j < (*pG).vexnum; j++)
	{
		q = p = (*pG).vertices[j].firstarc;
		//if this vertex has adjacency arc
		while (NULL != p)
		{
			if (p->adjvex == nSeq)
			{
				//if the deleted target is the first node
				if (p == (*pG).vertices[j].firstarc)
				{
					(*pG).vertices[j].firstarc = (*pG).vertices[j].firstarc->nextarc;
					//if network,delete the arc info
					if (DN == (*pG).kind || AN == (*pG).kind)
					{
						free(p->info);
						p->info = NULL;
					}
					free(p);
					p = NULL;
					p = (*pG).vertices[j].firstarc;
					//directed graph or directed network
					if ((*pG).kind == DN || (*pG).kind == DG)
					{
						(*pG).arcnum--;
					}
				}
				else
				{
					q->nextarc = p->nextarc;
					if (DN == (*pG).kind || AN == (*pG).kind)
					{
						free(p->info);
						p->info = NULL;
					}
					free(p);
					p = NULL;
					p = q->nextarc;
					//directed graph or directed network
					if ((*pG).kind == DN || (*pG).kind == DG)
					{
						(*pG).arcnum--;
					}
				}
			}
			else
			{
				if (p->adjvex > nSeq)
				{
					p->adjvex--;
				}
				q = p;
				p = p->nextarc;
			}
		}
	}

	(*pG).vexnum--;
	return 0;
}

//insert an arc between v and w
int InsertArc(ALGraph *pG, VexType v, VexType w)
{
	int nSeqV = 0;
	int nSeqW = 0;
	int n_weight = 0;
	ArcNode *p = NULL;
	ArcNode *q = NULL;
	nSeqV = LocateVex(*pG, v);
	nSeqW = LocateVex(*pG, w);
	if (-1 == nSeqV || -1 == nSeqW)
	{
		return -1;
	}

	//check the existence of the arc <v,w>
	for (p = (*pG).vertices[nSeqV].firstarc;\
		NULL != p && p->adjvex != nSeqW; p = p->nextarc)
	{
		;
	}
	if (NULL != p)
	{
		printf("the arc <%s,%s> has existed!\n", v, w);
		return -1; //has existed.
	}

	//the arc <v,w> doesn't exist and the current pointer p=null
	if (NULL == (p = (ArcNode *)malloc(sizeof(ArcNode))))
	{
		perror("No memory!\n");
		return -1;
	}
	//insert the new arc.
	p->nextarc = (*pG).vertices[nSeqV].firstarc;
	(*pG).vertices[nSeqV].firstarc = p;
	p->adjvex = nSeqW;
	//network needs have a weight
	if (DN == (*pG).kind || AN == (*pG).kind)
	{
		printf("Input Weight:");
		while (1 != scanf("%d", &n_weight) && n_weight != EOF)
		{
			while (getchar())
			{
				;
			}
		}
		if (NULL == (p->info = (InfoType*)malloc(sizeof(InfoType))))
		{
			perror("No memory!\n");
			return -1;
		}
		*(p->info) = n_weight;
	}
	//anti-directed graph or network needs create the symmetrical arc
	if (AG == (*pG).kind || AN == (*pG).kind)
	{
		if (NULL == (q = (ArcNode*)malloc(sizeof(ArcNode))))
		{
			perror("No memory!\n");
			return -1;
		}
		q->nextarc = (*pG).vertices[nSeqW].firstarc;
		(*pG).vertices[nSeqW].firstarc = q;
		q->adjvex = nSeqV;
		if (AN == (*pG).kind)
		{
			if (NULL == (q->info = (InfoType*)malloc(sizeof(InfoType))))
			{
				perror("No memory!\n");
				return -1;
			}
			*(q->info) = n_weight;
		}
	}

	(*pG).arcnum++;
	return 0;
}

int DeleteArc(ALGraph *pG, VexType v, VexType w)
{
	int n_seq_v = 0;
	int n_seq_w = 0;
	ArcNode *p = NULL;
	ArcNode *q = NULL;

	if (-1 == (n_seq_v = LocateVex(*pG, v))\
			|| -1 == (n_seq_w = LocateVex(*pG, w)))
	{
		printf("No such vex!\n");
		return -1;
	}

	//check the existence of the arc <v,w>
	for (p = (*pG).vertices[n_seq_v].firstarc,\
			q = (*pG).vertices[n_seq_v].firstarc;\
			NULL != p && p->adjvex != n_seq_w;
			q = p, p = p->nextarc)
	{
		;
	}
	if (NULL == p)
	{
		printf("No such arc!\n");
		return -1;
	}

	//delete <v,w>
	if (p == (*pG).vertices[n_seq_v].firstarc)
	{
		(*pG).vertices[n_seq_v].firstarc = p->nextarc;
		if (NULL != p->info)
		{
			free(p->info);
			p->info = NULL;
		}
		free(p);
		p = NULL;
	}
	else
	{
		q->nextarc = p->nextarc;
		if (NULL != p->info)
		{
			free(p->info);
			p->info = NULL;
		}
		free(p);
		p = NULL;
	}

	if (AN == (*pG).kind || AG == (*pG).kind)
	{
		//if anti-directed graph or network,it needs delete <w,v>
		for (p = (*pG).vertices[n_seq_w].firstarc,\
		       q = (*pG).vertices[n_seq_w].firstarc;\
		       NULL != p && p->adjvex != n_seq_v; q = p, p = p->nextarc)
		{
			;
		}
		if (NULL == p)
		{
			printf("No such arc!\n");
			return -1;
		}

		if (p == (*pG).vertices[n_seq_w].firstarc)
		{
			(*pG).vertices[n_seq_w].firstarc = p->nextarc;
			if (NULL != p->info)
			{
				free(p->info);
				p->info = NULL;
			}
			free(p);
			p = NULL;
		}
		else
		{
			q->nextarc = p->nextarc;
			if (NULL != p->info)
			{
				free(p->info);
				p->info = NULL;
			}
			free(p);
			p = NULL;
		}
	}

	(*pG).arcnum--;

	return 0;
}

static int gb_visited[MAX_VEX_NUM] = {False};
static void (*VisitFunc)(VexType);

extern void visit(VexType v);

//visit node from v recursively
static void DFS(ALGraph G, VexType v)
{
	int n_seq_v = 0;
	int n_seq_w = 0;
	ArcNode *p = NULL;
	n_seq_v = LocateVex(G, v);

	VisitFunc(v);//visit the node
	gb_visited[n_seq_v] = True;//note the node visited
	for (p = G.vertices[n_seq_v].firstarc;\
		NULL != p; p = p->nextarc)
	{
		n_seq_w = p->adjvex;
		if (!gb_visited[n_seq_w])
		{
			//visit the adjacent of v w recursively
			DFS(G, G.vertices[n_seq_w].data);
		}
	}
}

//traverse the whole graph by depth-first
void DFSTraverse(ALGraph G, void (*Visit)(VexType))
{
	int n_seq = 0;

	//initialize the global flag
	memset(gb_visited, '\0', MAX_VEX_NUM);
	VisitFunc = Visit;
	for (n_seq = 0; n_seq < G.vexnum; n_seq++)
	{
		if (!gb_visited[n_seq])
		{
			DFS(G, G.vertices[n_seq].data);
		}
	}
	printf("\n");
}

//define a auxiliary queue
static int queue[MAX_VEX_NUM];

//traverse the whole graph by breadth-first
void BFSTraverse(ALGraph G, void (*Visit)(VexType))
{
	int n_head = 0; //the pointer to head of the queue
	int n_tail = 0; //the pointer to tail of the queue
	int n_seq_v = 0; //the current vex sequence
	int n_seq_w = 0; //the adjacent vex sequence
	int u = 0;
	ArcNode *p = NULL;
	memset(gb_visited, '\0', MAX_VEX_NUM);
	memset(queue, '\0', MAX_VEX_NUM);

	for (n_seq_v = 0; n_seq_v < G.vexnum; n_seq_v++)
	{
		//not visited
		if (!gb_visited[n_seq_v])
		{
			//enqueue current node
			queue[n_tail++] = n_seq_v;
			while (n_tail != n_head) //if the queue is not empty
			{
				u = queue[n_head++];
				if (!gb_visited[u])
				{
					Visit(G.vertices[u].data);
					gb_visited[u] = True;
					for (p = G.vertices[u].firstarc;\
						NULL != p; p = p->nextarc)
					{
						n_seq_w = p->adjvex;
						if (!gb_visited[n_seq_w])
						{
							queue[n_tail++] = n_seq_w;
						}
					}
				}
			}
		}
	}
}

//output the whole graph
void Display(ALGraph G)
{
	int i = 0;
	ArcNode *p = NULL;
	switch (G.kind)
	{
		case DG:
			printf("Directed Graph:\n");
			for (i = 0; i < G.vexnum; i++)
			{
				for (p = G.vertices[i].firstarc;\
					NULL != p; p = p->nextarc)
				{
					printf("%s->%s\n", G.vertices[i].data, G.vertices[p->adjvex].data);
				}
			}
			break;
		case DN:
			printf("Directed Network:\n");
			for (i = 0; i < G.vexnum; i++)
			{
				for (p = G.vertices[i].firstarc;\
					NULL != p; p = p->nextarc)
				{
					printf("%s->%s\t%d\n", G.vertices[i].data,\
							G.vertices[p->adjvex].data, *(p->info));
				}
			}
			break;
		case AG:
			printf("unDirected Graph:\n");
			for (i = 0; i < G.vexnum; i++)
			{
				for (p = G.vertices[i].firstarc;\
					NULL != p; p = p->nextarc)
				{
					if (i < p->adjvex)
					{
						printf("%s-%s\n", G.vertices[i].data,\
							G.vertices[p->adjvex].data);
					}
				}
			}
			break;
		case AN:
			printf("unDirected Network:\n");
			for (i = 0; i < G.vexnum; i++)
			{
				for (p = G.vertices[i].firstarc;\
					NULL != p; p = p->nextarc)
				{
					if (i < p->adjvex)
					{
						printf("%s-%s\t%d\n", G.vertices[i].data,\
							G.vertices[p->adjvex].data, *(p->info));
					}
				}
			}
			break;
		default:
			printf("Unknown Graph kind!\n");
	}
}

