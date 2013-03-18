/*
 * 		文件名称:	get_directory.c
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

//Function use: 根据目录名chDirName,读取该目录下的文件名,并将其组成单链表
FileLinkList get_dir_detail(const char* chDirName)
{
	DIR* dir;
	struct dirent* pDrt;
	//打开目录
	if (NULL == (dir = opendir(chDirName)))
	{
		perror("无法打开目录!\n");
		return NULL;
	}

	//读取目录,建立链表
	FileLinkList pDirHead = (FileLinkList)malloc(sizeof(LNode));
	FileLinkList pDirTail = pDirHead;
	pDirHead->next = NULL;
	while (NULL != (pDrt = readdir(dir)))
	{
		if ((0 == strcmp(pDrt->d_name, "."))\
				|| (0 == strcmp(pDrt->d_name, "..")))
		{
			continue;		//忽略"."和".."目录
		}
		if (NULL == (pDirTail->next\
				= (FileLinkList)malloc(sizeof(LNode))))
		{
			perror("内存不足!\n");
			return NULL;
		}
		//保存目录名到链表中
		strcpy(pDirTail->next->chFileName, pDrt->d_name);
		pDirTail->next->next = NULL;
		pDirTail = pDirTail->next;
	}
	closedir(dir);		//关闭打开的目录

	return pDirHead;
}

//Function use: 销毁链表
int DestoryList(FileLinkList *pL)
{
	FileLinkList p = *pL;
	FileLinkList q = p;
	while (NULL != p)
	{
		q = p->next;
		free(p);
		p = NULL;
		p = q;
	}

	return 0;
}
