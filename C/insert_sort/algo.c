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
 *  algo.c: three inserting sort algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include "red.h"

//mode specifies the arrange way,involving DESCEND, ASCEND
void direct_insert_sort(sq_list *p_L, MODE mode)
{
	int i = 0;
	int j = 0;
	if (mode == DESCEND)
	{
		for (i = 2; i <= (*p_L).length; i++)
		{
			//if current key is more than the former one,then exchange.
			if ((*p_L).data[i].key > (*p_L).data[i - 1].key)
			{
				(*p_L).data[0] = (*p_L).data[i];// [0] a sentry.
				//search the right position to insert
				for (j = i - 1; (*p_L).data[j].key < (*p_L).data[0].key; j--)
				{
					(*p_L).data[j + 1] = (*p_L).data[j];
				}
				(*p_L).data[j + 1] = (*p_L).data[0];
			}
		}
	}
	if (mode == ASCEND)
	{
		for (i = 2; i <= (*p_L).length; i++)
		{
			//if current key is less than the former one,then exchange.
			if ((*p_L).data[i].key < (*p_L).data[i - 1].key)
			{
				(*p_L).data[0] = (*p_L).data[i];// [0] a sentry.
				//search the right position to insert
				for (j = i - 1; (*p_L).data[j].key > (*p_L).data[0].key; j--)
				{
					(*p_L).data[j + 1] = (*p_L).data[j];
				}
				(*p_L).data[j + 1] = (*p_L).data[0];
			}
		}
	}
}

//binary insertion sort.
void binary_insert_sort(sq_list *p_L, MODE mode)
{
	int i = 0;
	int j = 0;
	int high = 0;
	int low = 0;
	int mid = 0;

	if (mode == DESCEND)
	{
		for (i = 2; i <= (*p_L).length; i++)
		{
			if ((*p_L).data[i].key > (*p_L).data[i - 1].key)
			{
				(*p_L).data[0] = (*p_L).data[i];
				low = 1;
				high = i - 1;
				while (low <= high)
				{
					mid = (low + high) / 2;
					if ((*p_L).data[0].key >= (*p_L).data[mid].key)
					{
						high = mid - 1;
					}
					else
					{
						low = mid + 1;
					}
				}
				for (j = i - 1; j > high; j--)
				{
					(*p_L).data[j + 1] = (*p_L).data[j];
				}
				(*p_L).data[j + 1] = (*p_L).data[0];
			}
		}
	}
	if (mode == ASCEND)
	{
		for (i = 2; i <= (*p_L).length; i++)
		{
			if ((*p_L).data[i].key < (*p_L).data[i - 1].key)
			{
				(*p_L).data[0] = (*p_L).data[i];
				low = 1;
				high = i - 1;
				while (low <= high)
				{
					mid = (low + high) / 2;
					if ((*p_L).data[0].key <= (*p_L).data[mid].key)
					{
						high = mid - 1;
					}
					else
					{
						low = mid + 1;
					}
				}
				for (j = i - 1; j > high; j--)
				{
					(*p_L).data[j + 1] = (*p_L).data[j];
				}
				(*p_L).data[j + 1] = (*p_L).data[0];
			}
		}
	}
}
