/*
 *  Establishment date:  2009-4-11
 *  Author            :	 jasonleakey
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
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
 *  algo.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "radix.h"


//create RADIX tables.for each table, p_start point to the table head, while
//p_end point to the tail.in each table, the keys[i] is identical.
static void distribute(sl_list *p_SL, int i, array_t start, array_t end)
{
	int j = 0;
	//initialize the table
	for (j = 0; j < RADIX; j++)
	{
		start[j] = end[j] = 0;
	}

	//for each number, distribute it to the table according corresponding keys[i]
	//j indicates current number
	for (j = (*p_SL).r[0].next; 0 != j; j = (*p_SL).r[j].next)
	{

		int i_key = (*p_SL).r[j].keys[i]; //the value of the i-th key.
		if (0 == start[i_key])
		{
			start[i_key] = end[i_key] = j; //the keys[i] table has no element
		}
		else
		{
			(*p_SL).r[end[i_key]].next = j;
			end[i_key] = j;
		}
	}
}

//chain the tables to a linked list man and boy
static void collect(sl_list *p_SL, int i, array_t start, array_t end)
{
	int j = 0;
	sl_cell_t *p_t = &((*p_SL).r[0]);
	for (j = 0; j < RADIX; j++)
	{
		if (0 != start[j])
		{
			p_t->next = start[j]; //link the head of table
			p_t = &((*p_SL).r[end[j]]); //store the tail of table
		}
		start[j] = end[j] = 0;
	}
	p_t->next = 0;	//the sl_list tail's next field should be 0;
}

extern void display(sl_list SL);

//radix sort start from here.
void radix_sort(sl_list *p_SL)
{
	int i = 0;
	array_t start;
	array_t end;
	for (i = 0; i < (*p_SL).keynum; i++)
	{
		distribute(p_SL, i, start, end);
		collect(p_SL, i, start, end);
		printf("the %d time sorting,result:\n", i + 1);
		display(*p_SL);
	}
}

int init_static_list(sl_list *p_SL, int red[], int n)
{
	int i = 0;
	int j = 0;
	char ch[MAX_NUM_OF_KEY + 1];
	int max_num = red[0];

	for (i = 0; i < n; i++)
	{
		if (max_num < red[i])
		{
			max_num = red[i];
		}
	}
	if (8 < ((*p_SL).keynum = (int)(ceil(log10(max_num)))))
	{
		printf("invalid number!\n");
		return -1;
	}

	(*p_SL).recnum = n;	//length of numbers.
	(*p_SL).r[0].next = 1;
	for (i = 1; i <= (*p_SL).recnum; i++)
	{
		sprintf(ch, "%d", red[i - 1]);
		int len = strlen(ch);

		for (j = 0; j < len; j++)
		{
			(*p_SL).r[i].keys[j] = ch[len - j - 1] - 48; // change type of ch[j] from char to int
		}
		for (; j < (*p_SL).keynum; j++)
		{
			(*p_SL).r[i].keys[j] = 0;
		}
		(*p_SL).r[i].next = i + 1;
	}
	(*p_SL).r[(*p_SL).recnum].next = 0;

	return 0;
}
