/*
 *  Establishment date:  2009-4-20
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
 *  main.c:
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	char passwd[20];
	char *key;

	key = getpass("Input First Password:");

	strcpy(passwd, crypt(key, slat));

	printf("Password is :%s", )
	return 0;
}
