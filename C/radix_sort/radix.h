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
 *  radix.h:
 */

#ifndef RADIX_H_
#define RADIX_H_

#define MAX_NUM_OF_KEY 8	//the max number of key
#define RADIX 10	//key radix,here is decimal
#define MAX_SPACE 50

typedef int key_t;
typedef struct {
	key_t keys[MAX_NUM_OF_KEY];	//key
	int next;	//the pointer in static linked list
} sl_cell_t; //the node type of static linked list

typedef struct {
	sl_cell_t r[MAX_SPACE]; //r[0] is the header
	int keynum; //amount of current keys
	int recnum; //length of static linked list
} sl_list;

typedef int array_t[RADIX]; //type of pointer array

extern void radix_sort(sl_list *p_SL);
extern int init_static_list(sl_list *p_SL, int red[], int n);

#endif /* RADIX_H_ */
