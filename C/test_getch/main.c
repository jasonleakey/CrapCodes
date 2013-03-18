/*
 *  File name         :	 main.c
 *  Establishment date:  2009-2-6
 *  Author            :	 jasonleakey
 *  Copyright (R) 2009jasonleakey
 *  <jasonleakey2005@gmail.com>
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
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#define MAX_PSW_LENGTH 20

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

//Function Use: determine whether to open the echo function
//if 'bOption' is set to 0, then close echo;otherwise 1, open it
int set_disp_mode(int nFd, int bOption)
{
	int err;
	struct termios term;

	if (-1 == tcgetattr(nFd, &term))
	{
		perror("Cannot get the attribution of the terminal");
		return 1;
	}

	if (bOption)
	{
		term.c_lflag |= ECHOFLAGS;
	}
	else
	{
		term.c_lflag &= ~ECHOFLAGS;
	}

	err = tcsetattr(nFd, TCSAFLUSH, &term);
	if (-1 == err && EINTR == err)
	{
		perror("Cannot set the attribution of the terminal");
		return 1;
	}

	return 0;
}

//Function Use: get the password user input, and store it to an array
int getpasswd(char* passwd, int size)
{
	int c;
	int n = 0;

	printf("Please Input password:");

	do
	{
		c = getchar();

		if ('\n' != c || '\r' != c)
		{
			passwd[n++] = c;
		}
	} while ('\n' != c && '\r' != c && n < (size - 1));

	passwd[n] = '\0';

	return n;
}

int main()
{
	char passwd[MAX_PSW_LENGTH];

	set_disp_mode(STDIN_FILENO, 0);
	getpasswd(passwd, sizeof(passwd));

	printf("\nYour password is %s\n", passwd);
	printf("Press any key to continue...\n");


	set_disp_mode(STDIN_FILENO, 1);
	getchar();

	return 0;
}
