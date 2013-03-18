/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-1
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

#include <stdio.h>
#include <stdlib.h>
#include "PTree.h"

#define PRINT_MENU \
	printf("1. Init a Parent Tree\n\
2. Create a Parent Tree\n\
3. PTreeEmtpy\n\
4. Ptreedepth\n\
5. Root\n\
6. Value\n\
7. Assign\n\
8. Parent\n\
9. LeftChlid\n\
10. RightSibling\n\
11. Print\n\
12. Traverse\n\
0. Exit\n\
Please Select:")
#define CLEAR_STDIN while (getchar() != '\n'){;}

int main(int argc, char **argv)
{
	printf("*************************************************\n");
	printf("程序名称: Parent Tree\t作者:jasonleakey\n");
	printf("*************************************************\n");
	int menu_sel_num;
	int i;
	char cur_ch;		//current node value
	char newValue;
	PPTree TT;
	PTree T = &TT;
	PRINT_MENU;
	while (scanf("%d", &menu_sel_num) == 1 && menu_sel_num != EOF)
	{
		switch(menu_sel_num)
		{
			case 1:
				InitPTree(&T);
				printf("Init parent tree complete!\n");
				break;
			case 2:
				CLEAR_STDIN;
				CreatePTree(&T);
				printf("Create parent tree complete!\n");
				break;
			case 3:
				printf("T is %s\n",\
						(PTreeEmpty(T)) ? ("Empty") : ("Not Empty"));
				break;
			case 4:
				printf("Parent Tree depth:%d\n", PTreeDepth(T));
				break;
			case 5:
				printf("Root data:%c\n", Root(T));
				break;
			case 6:
				CLEAR_STDIN;
				printf("Input i(0-?):");
				while (scanf("%d", &i) != 1)
				{
					CLEAR_STDIN;
				}
				printf("the i-th node data:%c\n", Value(T, i));
				break;
			case 7:
				CLEAR_STDIN;
				printf("Input data you want to modify:");
				scanf("%c", &cur_ch);
				CLEAR_STDIN;
				printf("Input new data after modification:");
				scanf("%c", &newValue);
				Assign(&T, cur_ch, newValue);
				printf("Assign complete!\n");
				break;
			case 8:
				CLEAR_STDIN;
				printf("Input data:");
				scanf("%c", &cur_ch);
				printf("Its parent's data:%c\n", Parent(T, cur_ch));
				printf("Parent complete!\n");
				break;
			case 9:
				CLEAR_STDIN;
				printf("Input data:");
				scanf("%c", &cur_ch);
				printf("Its left child's data:%c\n", LeftChild(T, cur_ch));
				printf("LeftChlid complete!\n");
				break;
			case 10:
				CLEAR_STDIN;
				printf("Input data:");
				scanf("%c", &cur_ch);
				printf("Its right sibling's data:%c\n", RightSibling(T, cur_ch));
				printf("RightSibling complete!\n");
				break;
			case 11:
				Print(T);
				printf("Print complete!\n");
				break;
			case 12:
				Traverse(T, vi);
				break;
			case 0:
				DestroyPTree(&T);
				exit(EXIT_SUCCESS);
			default:
				printf("Input error!\nInput again:");
		}
		CLEAR_STDIN;
		printf("press Return back to menu:");
		getchar();
		PRINT_MENU;
	}
	DestroyPTree(&T);
	return EXIT_SUCCESS;
}

