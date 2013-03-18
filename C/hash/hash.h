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
 *  hash.h:
 */

#ifndef HASH_H_
#define HASH_H_

#define MAX_INFO_SIZE 20

typedef int key_t;
typedef char info_t[MAX_INFO_SIZE];

//node information
typedef struct {
	key_t key;
	info_t info;
} element_t;

typedef struct {
	element_t *elem;	//base pointer of elements
	int count; //current amount of data elements
	int size; //current capacity
} hash_table;

extern int init_hash_table(hash_table *p_H, int size);
extern void destroy_hash_tabel(hash_table *p_H);
//extern unsigned hash(hash_table *p_H, key_t key);
extern void collision(hash_table H, int *p_position, int d);
extern int search_hash(hash_table H, key_t key, int *p_position, int *p_times);
//extern void recreate_hash_table(hash_table *p_H);
extern int insert_hash(hash_table *p_H, element_t element);
extern void hash_traverse(hash_table H, void (*visit)(element_t));
//extern int find(hash_table H, key_t key, int *p_position);

#endif /* HASH_H_ */
