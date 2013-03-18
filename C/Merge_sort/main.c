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
 *  main.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "sq_list.h"

#define SIZE 18

void display(sq_list L)
{
	int i = 0;
	printf("   No.");
	for (i = 1; i < L.length + 1; i++)
	{
		printf("%6d", i);
	}
	printf("\nvalue:");
	for (i = 1; i < L.length + 1; i++)
	{
		printf("%6d", L.data[i].key);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	redcord_t d[SIZE] = {{1, "one"}, {3, "three"}, {2, "two"}, {-9, "neg-nine"},\
			{28, "twenty-eight"}, {-100, "neg-hundred"}, {44, "forty-four"},\
			{0, "zero"}, {12, "twelve"}, {99, "gogo"}, {28, "gona"}, {0, "home"},\
			{-1, "bit"}, {-9, "44"}, {8, "99"}, {3, "ff"}, {5, "lk"}, {11, "wish"}};
	sq_list L;
	char ch_sel;
	int i = 0;

	for (i = 1; i < SIZE + 1; i++)
	{
		L.data[i] = d[i - 1];
	}
	L.length = SIZE;
	printf("initial sq_list:\n");
	display(L);
	printf("Input sorting mode(y:ascend or n:descend):");
	while (1 != scanf("%c%*c", &ch_sel) && ch_sel != EOF)
	{
		while (getchar())
		{
			;
		}
	}
	if (ch_sel == 'y' || ch_sel == 'Y')
	{
		merge_sort(&L, ASCEND);
		printf("merge sorting result:\n");
		display(L);
	}
	else if (ch_sel == 'n' || ch_sel == 'N')
	{
		merge_sort(&L, DESCEND);
		printf("merge sorting result:\n");
		display(L);
	}
	else
	{
		printf("Invalid Input!\n");
	}
	return 0;
}
