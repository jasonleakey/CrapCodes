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
 *  sq_list.h:
 */

#ifndef SQ_LIST_H_
#define SQ_LIST_H_

#define MAX_SIZE 20
#define MAX_STR_SIZE 20
//calculate time interval between time_start and time_end
#define TIME_INTERVAL(time_start, time_end)\
	time_end.tv_sec + time_end.tv_usec / 1000000.0\
	- time_start.tv_sec - time_start.tv_usec /1000000.0


typedef enum {
	DESCEND,
	ASCEND
} MODE;

typedef int key_t;	/* key type */
typedef char info_t[MAX_STR_SIZE];	// information type
typedef struct {
	key_t key;
	info_t info;
} redcord_t;

typedef struct {
	redcord_t data[MAX_SIZE + 1];
	int length;
} sq_list;

extern void heap_sort(sq_list *p_L, MODE mode);

#endif /* SQ_LIST_H_ */
