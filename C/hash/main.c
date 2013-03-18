/*
 *  Establishment date:  2009-4-12
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
#include "hash.h"

#define N 10
#define INIT_SIZE 17

void print_hash(element_t element)
{
	printf("  (%d,%s)", element.key, element.info);
}

int main(int argc, char **argv)
{
	int i = 0;
	key_t srch_key = 0;
	int position = 0; //
	int times = 0;
	element_t d[N] = {{8, "eight"}, {18, "eighteen"}, {89, "eighty-nine"},\
			{122, "a"}, {51, "b"}, {4, "four"}, {1, "po"}, {12, "hoho"},\
			{8, "seven"}, {7, "who"}};
	hash_table HT;
	init_hash_table(&HT, INIT_SIZE);
	for (i = 0; i < N - 1; i++)
	{
		//insert the first N-1 record.
		if (-1 == insert_hash(&HT, d[i]))
		{
			printf("an key %d has existed in hash table,cannot insert "\
					"(%d,%s)!\n", d[i].key, d[i].key, d[i].info);
		}
	}

	printf("hash traverse result:\n");
	hash_traverse(HT, &print_hash);
	printf("input the key to search:");
	scanf("%d", &srch_key);
	if (-1 == search_hash(HT, srch_key, &position, &times))
	{
		printf("Not Found!\n");
	}
	else
	{
		printf("Found!address = %d, (%d,%s)\n", position,\
				HT.elem[position].key, HT.elem[position].info);
	}

	insert_hash(&HT, d[N - 1]); // insert the last element,it will
							//leads to a rearrange of hash table
	printf("after rebuilding hash table,traverse result:\n");
	hash_traverse(HT, &print_hash);
	destroy_hash_tabel(&HT);

	return 0;
}
