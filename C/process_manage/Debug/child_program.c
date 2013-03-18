/*
 *      child_program.c
 *      
 *      Copyright 2009 jasonleakey <jasonleakey@jasonleakey-laptop>
 *      
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
#include <unistd.h>	//getpid()
#include <signal.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	pid_t nPid;
	int exit_code;
	
	nPid = getpid();
	srand((unsigned)nPid);
	//generate exit code at ramdom
	exit_code = (int)(rand() % 256);
	
	sleep(2);
	
	//determine how to exit by argv
	if (0 != (atoi(*(argv + 1)) % 2))
	{
		printf("Child Process ID:%d receive signal SIGKILL\n", nPid);
		kill(nPid, 9);	
	}
	else
	{
		printf("Child Process ID:%d normally exit,"\
			"exit_code is %#x\n", nPid, exit_code);
		exit(exit_code);
	}
	
	return 0;
}
