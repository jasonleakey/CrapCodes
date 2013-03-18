/*
 * 		文件名称:	print_directory.c
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

#include "link_list.h"

void print_file_info(FileLinkList L)
{
	static char* perm[] = {"---", "--x", "-w-",\
			"-wx", "r--", "r-x", "rw-", "rwx"};

	unsigned int mask = 0700;
	struct stat file_stat;
	FileLinkList p = L->next;

	//遍历单链表,获得每个元素的具体信息
	while (NULL != p)
	{
		mask = 0700;
		info file_info;
		if (-1 == stat(p->chFileName, &file_stat))
		{
			perror("无法获得文件信息!\n");
			p = p->next;
			continue;
		}

		//判断是文件还是目录
		if (S_ISREG(file_stat.st_mode))
		{
			file_info.permission[0] = '-';
		}
		if (S_ISDIR(file_stat.st_mode))
		{
			file_info.permission[0] = 'd';
		}

		int i = 3;
		int j = 0;

		//通过移位运算获得具体的权限
		while (i > 0)
		{
			file_info.permission[1 + j * 3] =\
				perm[(file_stat.st_mode & mask) >> (i - 1) * g_N_BITS][0];
			file_info.permission[2 + j * 3] =\
				perm[(file_stat.st_mode & mask) >> (i - 1) * g_N_BITS][1];
			file_info.permission[3 + j * 3] =\
				perm[(file_stat.st_mode & mask) >> (i - 1) * g_N_BITS][2];
			j++;
			i--;
			mask >>= g_N_BITS;
		}

		//获得其他的文件或目录信息
		file_info.permission[10] = '\0';
		file_info.owner = file_stat.st_uid;
		file_info.group = file_stat.st_gid;
		file_info.inode = file_stat.st_ino;
		file_info.size = file_stat.st_size;
		file_info.mod_time = file_stat.st_mtime;
		strcpy(file_info.name, p->chFileName);

		//输出所有信息
		printf("%lu  ", file_info.inode);
		printf("%s  ", file_info.permission);
		printf("%d  ", file_info.owner);
		printf("%d  ", file_info.group);
		printf("%ld  ", file_info.size);
		printf("%s  ", ctime(&file_info.mod_time));
		printf("%s\n", file_info.name);

		p = p->next;	//指向下一个元素
	}
}
