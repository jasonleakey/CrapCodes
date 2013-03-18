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
 *  main.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include "radix.h"

#define N 18

void display(sl_list SL)
{
	int i = 0;
	int j = 0;
	for (i = SL.r[0].next; 0 != i; i = SL.r[i].next)
	{
		printf("   ");
		for (j = SL.keynum - 1; j >= 0; j--)
		{
			printf("%d", SL.r[i].keys[j]);
		}
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int nums[N] = {833, 989, 87, 2, 189, 374, 0, 10, 221, 911,\
			121, 989, 777, 413, 012, 68, 541, 0x10};
	sl_list SL;
	if (-1 == init_static_list(&SL, nums, N))
	{
		perror("Error:");
		return -1;
	}
	printf("before sorting,result:\n");
	display(SL);
	radix_sort(&SL);
	printf("after sorting,result:\n");
	display(SL);

	return 0;
}
