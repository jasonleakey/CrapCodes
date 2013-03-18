/*
 *
 *  File name         :	 main.c
 *  Establishment date:  2009-2-6
 *  Author            :	 jasonleakey
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

#include <stdio.h>
#include <unistd.h> //definition of usleep(usec),let procedure to sleep usec
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/kd.h> //definition of KIOCSOUND

//internal speaker is a part of console
#define SPEAKER_DEVICE "/dev/console"

int main(int argc, char **argv)
{
	int fd;	//file description entry after opening the speaker
	int i;
	int freq;

	if (2 != argc)
	{
		printf("Usage: %s frequence \n", argv[0]);
		return 1;
	}

	//get frequence of speaking
	freq = atoi(argv[1]);

	if (freq <= 0 || freq > 10000)
	{
		printf("the frequence must be in the range from 0 to 10000!\n");
		return 1;
	}

	if (-1 == (fd = open(SPEAKER_DEVICE, O_WRONLY)))
	{
		perror("Cannot open the speaker device!\n");
		return 1;
	}

	for (i = 0; i < 10; ++i)
	{
		printf("debug...\n");
		//calculate frequence to be set
		int set_freq = 1190000/freq;
		if (-1 == ioctl(fd, KIOCSOUND, set_freq))
		{
			perror("Cannot play sound!\n");
			return 1;
		}
		if (-1 == usleep(200000))	//playing time is 200 msec
		{
			perror("Sleep Error!\n");
			return 1;
		}
		ioctl(fd, KIOCSOUND, 0);
		usleep(100000);
	}

	return 0;

}
