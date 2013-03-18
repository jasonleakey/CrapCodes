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

static void shell_insert_sort(sq_list *p_L, int inc, MODE mode)
{

	int i = 0;
	int j = 0;
	if (mode == DESCEND)
	{
		for (i = 1 + inc; i <= (*p_L).length; i += inc)
		{
			//if current key is more than the former one,then exchange.
			if ((*p_L).data[i].key > (*p_L).data[i - inc].key)
			{
				(*p_L).data[0] = (*p_L).data[i];// [0] a sentry.
				//search the right position to insert
				for (j = i - inc; j > 0 && (*p_L).data[j].key < (*p_L).data[0].key; j -= inc)
				{
					(*p_L).data[j + inc] = (*p_L).data[j];
				}
				(*p_L).data[j + inc] = (*p_L).data[0];
			}
		}
	}
	if (mode == ASCEND)
	{
		for (i = 1 + inc; i <= (*p_L).length; i += inc)
		{
			//if current key is less than the former one,then exchange.
			if ((*p_L).data[i].key < (*p_L).data[i - inc].key)
			{
				(*p_L).data[0] = (*p_L).data[i];// [0] a sentry.
				//search the right position to insert
				for (j = i - inc; j > 0 && (*p_L).data[j].key > (*p_L).data[0].key; j -= inc)
				{
					(*p_L).data[j + inc] = (*p_L).data[j];
				}
				(*p_L).data[j + inc] = (*p_L).data[0];
			}
		}
	}
}

void shell_sort(sq_list *p_L, int increasement[], int n, MODE mode)
{
	int i = 0;
	struct timeval time_start;
	struct timeval time_end;
	for (i = 0; i < n; i++)
	{
		gettimeofday(&time_start, NULL);
		shell_insert_sort(p_L, increasement[i], mode);
		gettimeofday(&time_end, NULL);
		printf("The %d time sorting result:(time = %lfs)\n",\
				i + 1, TIME_INTERVAL(time_start, time_end));
		display(*p_L);
	}
}
