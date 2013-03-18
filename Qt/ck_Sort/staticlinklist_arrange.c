/*
 * 		文件名称:	staticlinklist_arrange.c
 * 		创建时间:	2008-12-14
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
#include <stdlib.h>
#include <limits.h>
#include "SLinkList.h"

/*
 * Function
 * name  	: TableInsert
 * use	  	: insert_sort_static_linklist
 * @param 	: SLinkList *pSL, pointer of SL
 * 			  RedType D[], array
 * 			  int n, size of array D
 * @return	: void
 */
void TableInsert(SLinkList *pSL, RedType D[], int n)
{
	int i;
	int p;
	int q;
	(*pSL).r[0].rc.key = INT_MAX;
	(*pSL).r[0].next = 0;		//initialize empty list
	for (i = 0; i < n; i++)
	{
		(*pSL).r[i + 1].rc = D[i];		//将数组的值赋给静态链表
		q = 0;
		p = (*pSL).r[0].next;
		//static linklist moves forward
		while ((*pSL).r[p].rc.key <= (*pSL).r[i + 1].rc.key)
		{
			q = p;
			p = (*pSL).r[p].next;
		}
		(*pSL).r[i + 1].next = p;
		(*pSL).r[q].next = i + 1;
	}
	(*pSL).length = n;
}


