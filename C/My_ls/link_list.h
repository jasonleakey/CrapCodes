/*
 * 		文件名称:	link_list.h
 * 		创建时间:	2009-1-18
 * 		程序作者:	jasonleakey
 * 		当前版本:	1.0
 * 		Copyright 2008 jasonleakey
 * 		<jasonleakey@sohu.com>
 * 		<QQ:174481438>
 * 		--------------------------------------------------------------------
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */


#ifndef LINK_LIST_H_
#define LINK_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX_FILE_NAME_LENGTH 255

//将目录名或文件名链接成一个链表
typedef struct LNode {
	char chFileName[MAX_FILE_NAME_LENGTH];		//数组存放文件名
	struct LNode *next;
} LNode, *FileLinkList;

//存放文件具体信息
typedef struct item_info {
	unsigned long inode;
	char permission[11];
	uid_t owner;//uid_t <=> int
	gid_t group;//gid_t <=> int
	off_t size;	//off_t <=> long
	time_t mod_time;
	char name[256];
} info;

extern const int g_N_BITS;

extern FileLinkList get_dir_detail(const char* chDirName);

extern int DestoryList(FileLinkList *pL);

extern void print_file_info(FileLinkList L);

#endif /* LINK_LIST_H_ */
