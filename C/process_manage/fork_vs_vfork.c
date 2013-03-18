/*
 *
 *  File name         :	 fork_vs_vfork.c
 *  Establishment date:  2009-2-10
 *  Author            :	 jasonleakey
 *  Module function	  :  compare fork() with vfork()
 *  Copyright (R) 2009 jasonleakey
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

#include <sys/types.h>
#include <unistd.h>	//exec() fork()
#include <stdlib.h>	//atexit(), exit()
#include <stdio.h>
#include <string.h>
#include <wait.h>	//wait()
#define MAX_PATH_LEN 40
static int g_var_fork = 0;
static int g_var_vfork = 0;

void use_fork(char *argv[])
{
	pid_t nPid;
	int nStatus;

	if ((nPid = fork()) < 0)
	{
		printf("Cannot create a new process!\n");
	}
	else if (0 == nPid)
	{
		printf("In the Child Process!Process ID:%d\n", getpid());
		//**Caution : only one function can be valid once in series of exec*()
		//because DATA,CODE,STACK SEGMENT are replaced by procedure given.

		//print files and directories in home directory
		//printf("execlp() Result:\n");
		//execlp("ls", "ls", "-l", "/home/jasonleakey", (char*)NULL);

		//print files list in current directory
		//printf("execl() Result:\n");
		//execl("/bin/ls", "ls", (char*)NULL);

		printf("execv() Result:\n");
		char chDir[MAX_PATH_LEN] = "/bin/";
		execv(strcat(chDir, argv[0]), &argv[1]);
		//printf("execvp() Result:\n");
		//execvp(argv[0], &argv[1]);
		_exit(0);
	}
	else
	{
		wait(&nStatus);
		printf("In the Parent Process!Process ID:%d\n", getpid());
	}
}

//Function Use: sources of the child process from fork() is copied from
//parent process
void test_fork(void)
{
	pid_t nPid;
	int nForkVar = 1;

	printf("Before invoking fork():\nProcess ID:%ld, g_var_fork=%d,"\
			"nForkVar=%d\n", (long)getpid(), g_var_fork, nForkVar);

	printf("After invoking fork():\n");
	if ((nPid = fork()) < 0)
	{
		printf("Cannot create a new process!\n");
	}
	else if (0 == nPid)
	{
		g_var_fork++;
		nForkVar++;
		printf("Process ID:%ld, g_var_fork=%d, nForkVar=%d\n",\
				(long)getpid(), g_var_fork, nForkVar);
		_exit(0);
	}

	printf("Process ID:%ld, g_var_fork=%d, nForkVar=%d\n",\
			(long)getpid(), g_var_fork, nForkVar);
}

//Function Use: sources of the child process from vfork() is shared with
//parent process
void test_vfork(void)
{
	pid_t nPid;
	int nVForkVar = 1;

	printf("Before invoking vfork:\n");
	printf("Process ID:%ld, g_var_vfork=%d, nVForkVar=%d\n",\
			(long)getpid(), g_var_vfork, nVForkVar);

	printf("After invoking vfork:\n");
	if ((nPid = vfork()) < 0)
	{
		printf("Cannot create a new process!\n");
	}
	else if (0 == nPid)
	{
		g_var_vfork++;
		nVForkVar++;
		printf("Process ID:%ld, g_var_vfork=%d, nVForkVar=%d\n",\
				(long)getpid(), g_var_vfork, nVForkVar);
		_exit(0);
	}

	printf("Process ID:%ld, g_var_vfork=%d, nVForkVar=%d\n",\
			(long)getpid(), g_var_vfork, nVForkVar);
}


//Function Use: this function is registered with atexit and will be
//executed before program terminates.
void do_at_exit_first(void)
{
	printf("The first function executed before the program terminates!\n");
}

void do_at_exit_second(void)
{
	printf("The second function executed before the program terminates!\n");
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s arg_list...", argv[0]);
		return 1;
	}

	use_fork(&argv[1]);
	printf("\n");
	test_fork();
	printf("\n");
	test_vfork();
	printf("\n");

	int bFlag_one = 0;	//store the result after invoking atexit
	int bFlag_second = 0;

	//register exit functions
	//Notice: function executing order is opposite to registering order.
	bFlag_one = atexit(do_at_exit_first);
	bFlag_second = atexit(do_at_exit_second);

	if (bFlag_one || bFlag_second)
	{
		perror("Cannot set exit function!\n");
		return EXIT_FAILURE;
	}

	return 0; //also can be replaced with exit(EXIT_SUCCESS);
}
