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
 *  algo.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

//initialize hash table with size specified with the second parameter
int init_hash_table(hash_table *p_H, int size)
{
	int i = 0;
	(*p_H).size = size;
	(*p_H).count = 0;
	if (NULL == ((*p_H).elem = (element_t*)malloc(size * sizeof(element_t))))
	{
		perror("No memory for init hash table!\n");
		return -1;
	}
	for (i = 0; i < (*p_H).size; i++)
	{
		(*p_H).elem[i].key = 0;
	}
	return 0;
}

void destroy_hash_tabel(hash_table *p_H)
{
	if (NULL != (*p_H).elem)
	{
		free((*p_H).elem);
		(*p_H).elem = 0;
	}
	(*p_H).count = 0;
	(*p_H).size = 0;
}

//calculate hash value
static unsigned hash(hash_table H, key_t key)
{
	return key % H.size;
}

//when collision occurred, how to calculate the new position
//open addressing method to solve collision.
void collision(hash_table H, int *p_position, int d)
{
	*p_position = (*p_position + d) % H.size;
}

//*p_times give the collision times
int search_hash(hash_table H, key_t key, int *p_position, int *p_times)
{
	int i = 0;
	*p_position = hash(H, key);

	while (0 != H.elem[*p_position].key && H.elem[*p_position].key != key)
	{
		(*p_times)++;
		if (*p_times > H.size)
		{
			return -1; //No such key
		}
		collision(H, p_position, ++i); //linear detecting rehash
	}
	if (0 == H.elem[*p_position].key)
	{
		return -1;
	}
	return 0;
}

static void recreate_hash_table(hash_table *p_H);

int insert_hash(hash_table *p_H, element_t element)
{
	int n_position = 0;
	int n_times = 0;
	if (0 == search_hash(*p_H, element.key, &n_position, &n_times))
	{
		return -1; //found the same element in the hash table
	}
	if ((*p_H).count < (*p_H).size / 2)
	{
		(*p_H).elem[n_position] = element;
		(*p_H).count++;
		return 0;
	}
	else
	{
		recreate_hash_table(p_H);
		insert_hash(p_H, element);
	}
}

//determine if d is a prime,if yes,return 1
//else, return 0
static int is_prime(int d)
{
	int i = 0;
	if (0 == d % 2)
	{
		return 0;
	}
	for (i = 3; i < d / 2; i += 2)
	{
		if (0 == d % i)
		{
			return 0;
		}
	}
	return 1;
}

static void recreate_hash_table(hash_table *p_H)
{
	int i = 0;
	int j = 0;
	int old_size = (*p_H).size;
	int old_count = (*p_H).count;
	int n_next_prime = (*p_H).size + 1;
	//get next prime to be new hash table capacity
	while (!is_prime(n_next_prime))
	{
		n_next_prime++;
	}


	element_t temp[old_size]; //to store elements in old hash table
	for (i = 0; i < (*p_H).size; i++)
	{
		if (0 != (*p_H).elem[i].key)
		{
			temp[j++] = (*p_H).elem[i];
		}
	}

	//reallocate the hash table, new size is n_next_prime
	if (NULL == ((*p_H).elem = (element_t*)realloc((*p_H).elem,\
			n_next_prime * sizeof(element_t))))
	{
		printf("No memory!\n");
		exit(-1);
	}

	//initialize the new table
	(*p_H).size = n_next_prime;
	(*p_H).count = 0;
	for (i = 0; i < (*p_H).size; i++)
	{
		(*p_H).elem[i].key = 0;
	}

	//insert elements into the new table.
	for (i = 0; i < old_count; i++)
	{
		insert_hash(p_H, temp[i]);
	}
}

void hash_traverse(hash_table H, void (*visit)(element_t))
{
	int i = 0;
	for (i = 0; i < H.size; i++)
	{
		//has data
		if (0 != H.elem[i].key)
		{
			visit(H.elem[i]);
		}
	}
	printf("\n");
}
