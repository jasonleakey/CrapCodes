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
#include "sq_list.h"

static void merge(redcord_t sr[], redcord_t tr[], int i, int m, int n, MODE mode)
{
	int x = 0;
	int y = 0;
	int k = 0;
	if (mode == DESCEND)
	{
		for (x = i, y = m + 1, k = i; x <= m && y <= n; k++)
		{
			if (sr[x].key >= sr[y].key)
			{
				tr[k] = sr[x++];
			}
			else
			{
				tr[k] = sr[y++];
			}
		}
		if (x > m)
		{
			while (y <= n)
			{
				tr[k++] = sr[y++];
			}
		}
		if (y > n)
		{
			while (x <= m)
			{
				tr[k++] = sr[x++];
			}
		}
	}
	if (mode == ASCEND)
	{
		for (x = i, y = m + 1, k = i; x <= m && y <= n; k++)
		{
			if (sr[x].key <= sr[y].key)
			{
				tr[k] = sr[x++];
			}
			else
			{
				tr[k] = sr[y++];
			}
		}
		if (x > m)
		{
			while (y <= n)
			{
				tr[k++] = sr[y++];
			}
		}
		if (y > n)
		{
			while (x <= m)
			{
				tr[k++] = sr[x++];
			}
		}
	}
}

static void m_sort(redcord_t sr[], redcord_t tr[], int s, int t, MODE mode)
{
	redcord_t temp[MAX_SIZE + 1];
	if (s == t)
	{
		tr[s] = sr[s];
	}
	else
	{
		int m = (s + t) / 2;
		m_sort(sr, temp, s, m, mode);
		m_sort(sr, temp, m + 1, t, mode);
		merge(temp, tr, s, m, t, mode);
	}
}

void merge_sort(sq_list *p_L, MODE mode)
{
	m_sort(p_L->data, p_L->data, 1, p_L->length, mode);
}
