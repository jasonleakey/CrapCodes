/*
 *  Establishment date:  2009-4-8
 *  Author            :	 jasonleakey
 *  Copyleft(R) by jasonleakey
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
 *  main.c: main module
 */

#include <stdio.h>
#include <stdlib.h>
#include "adjcency_list.h"

void visit(VexType v)
{
	printf("%s", v);
}

int main(int argc, char **argv)
{
	ALGraph G;
	VexType u;
	VexType w;

	CreateGraph(&G);
	printf("Output Result:\n");
	Display(G);

	printf("Input a vertex name to modify:");
	scanf("%s%*c", &u);
	printf("Input new value:");
	scanf("%s%*c", &w);
	SetVex(&G, u, w);
	Display(G);

	printf("Input a new vertex to insert:");
	scanf("%s%*c", &u);
	InsertVex(&G, u);
	Display(G);

	printf("Input a new arc to insert(format:u w):");
	scanf("%s%*c", &u);
	scanf("%s%*c", &w);
	InsertArc(&G, u, w);
	Display(G);

	printf("Input an arc to delete:");
	scanf("%s%*c", &u);
	scanf("%s%*c", &w);
	DeleteArc(&G, u, w);
	Display(G);

	printf("Input a vertex name to delete:");
	scanf("%s%*c", &u);
	DeleteVex(&G, u);
	Display(G);

	printf("DFS result:\n");
	DFSTraverse(G, &visit);
	printf("BFS result:\n");
	BFSTraverse(G, &visit);

	DestroyGraph(&G);

	return 0;
}
