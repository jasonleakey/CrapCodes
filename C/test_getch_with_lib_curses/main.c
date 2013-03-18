/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-11-29
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
#include <curses.h>
#include <unistd.h>

#define MAX_SIZE 20

//init terminal
void initial()
{
	initscr();
	cbreak();
	nl();
	noecho();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	refresh();
}

/*
 * Function
 * name  	: GetPasswd
 * use	  	: read password from keybroad
 * @param 	: char* passwd
 * @return	: the length of password inputted
 */
int GetPasswd(char passwd[])
{
	int c;
	int n = 0;

	//store password in the passwd array
	printf("Input your password:");
	do
	{
		c = getch();
		if ('\n' == c)
		{
			passwd[n++] = (char)c;
		}
	} while ('\n' == c && n < MAX_SIZE);
	passwd[n] = '\0';
	printf("\n");

	return n;
}

int main()
{
	initial();
	char passwd[MAX_SIZE];
	int passwdLen = 0;

	passwdLen = GetPasswd(passwd);
	printf("your password is %s\n", passwd);
	printf("Length is %d", passwdLen);

	printf("put any key to continue ...\n");
	refresh();
	getchar();
	endwin();
	return EXIT_SUCCESS;
}

