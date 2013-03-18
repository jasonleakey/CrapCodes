/*
 *  Establishment date:  2009-4-9
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
#include "sq_list.h"

static int partition(sq_list *p_L, int low, int high, MODE mode)
{
	int pivot_loc = low;
	(*p_L).data[0] = (*p_L).data[low];
	if (mode == ASCEND)
	{
		while (low < high)
		{
			for (; low < high && (*p_L).data[high].key >= (*p_L).data[0].key; high--)
			{
				;
			}
			(*p_L).data[low] = (*p_L).data[high];
			for (; low < high && (*p_L).data[low].key <= (*p_L).data[0].key; low++)
			{
				;
			}
			(*p_L).data[high] = (*p_L).data[low];
		}
		(*p_L).data[low] = (*p_L).data[0];
	}
	else
	{
		while (low < high)
		{
			for (; low < high && (*p_L).data[high].key <= (*p_L).data[0].key; high--)
			{
				;
			}
			(*p_L).data[low] = (*p_L).data[high];
			for (; low < high && (*p_L).data[low].key >= (*p_L).data[0].key; low++)
			{
				;
			}
			(*p_L).data[high] = (*p_L).data[low];
		}
		(*p_L).data[low] = (*p_L).data[0];
	}

	pivot_loc = low;
	return pivot_loc;
}

void quick_sort(sq_list *p_L, int low, int high, MODE mode)
{
	int pivot_loc = 0;
	if (low < high)
	{
		pivot_loc = partition(p_L, low, high, mode);
		quick_sort(p_L, low, pivot_loc - 1, mode);
		quick_sort(p_L, pivot_loc + 1, high, mode);
	}
}
