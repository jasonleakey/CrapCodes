/*
 * 		文件名称:	main.c
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

const int g_N_BITS = 3;

int main(int argc, char **argv)
{
	if (2 != argc)
	{
		printf("Usage: %s directory-name\n", argv[0]);
		return 1;
	}

	FileLinkList L = get_dir_detail(argv[1]);
	print_file_info(L);
	DestoryList(&L);

	return 0;
}
