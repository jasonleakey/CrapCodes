/*
 *  Establishment date:  2009-4-10
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
#include <sys/time.h>
#include <unistd.h>
#include "sq_list.h"


//create a heap between (*p_L)[s] and (*p_L)[m]
static void adjust_heap(sq_list *p_L, int s, int m, MODE mode)
{
	int i = 2 * s;
	redcord_t temp = (*p_L).data[s]; //store the root
	if (ASCEND == mode)
	{
		while (i <= m)
		{
			//determine the bigger child
			if (i < m && (*p_L).data[i].key < (*p_L).data[i+1].key)
			{
				i++;
			}
			//found the position to insert.
			if (temp.key > (*p_L).data[i].key)
			{
				break;
			}
			(*p_L).data[s] = (*p_L).data[i];
			s = i;
			i <<= 1;	//go down to the left child
		}
		(*p_L).data[s] = temp;
	}
	if (DESCEND == mode)
	{
		while (i <= m)
		{
			if (i < m && (*p_L).data[i].key > (*p_L).data[i + 1].key)
			{
				i++;
			}
			if (temp.key < (*p_L).data[i].key)
			{
				break;
			}
			(*p_L).data[s] = (*p_L).data[i];
			s = i;
			i <<= 1; //go down to the left child
		}
		(*p_L).data[s] = temp;
	}
}


void heap_sort(sq_list *p_L, MODE mode)
{
	struct timeval time_start;
	struct timeval time_end;
	redcord_t temp;
	int i = 0;

	gettimeofday(&time_start, NULL);
	for (i = (*p_L).length / 2; i > 0; i--)
	{
		adjust_heap(p_L, i, (*p_L).length, mode); //create a heap [1..(*p_L).length]
	}

	//for every time pick up the max or min element, a heap adjustment is required.
	for (i = (*p_L).length; i > 0; i--)
	{
		temp = (*p_L).data[1];
		(*p_L).data[1] = (*p_L).data[i];
		(*p_L).data[i] = temp;
		adjust_heap(p_L, 1, i - 1, mode);
	}
	gettimeofday(&time_end, NULL);
	printf("(algo time:%lfs)\n", TIME_INTERVAL(time_start, time_end));
}
