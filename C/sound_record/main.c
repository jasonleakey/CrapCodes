/*
 *
 *  File name         :	 main.c
 *  Establishment date:  2009-2-7
 *  Author            :	 jasonleakey
 *  Module function	  :  Main function, to record sound
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
#include <stdlib.h>
#include <unistd.h>//include read() and write()
#include <fcntl.h>	//include open()
#include <sys/ioctl.h>	//include ioctl()
#include <linux/soundcard.h>

#define LENGTH 4	//recording time
#define RATE 44100	//sampling rate
#define SIZE 16	//Digitalizing bit
#define CHANNEL 2	//sample channel quantities
#define RECORD_DEVICE "/dev/dsp"
#define RECORD_FILE "/home/jasonleakey/record.wav"

typedef int boolean;

int main(int argc, char **argv)
{
	//buffer to store recording data temporarily
	unsigned char chBuffer[LENGTH * RATE * SIZE * CHANNEL / 8];

	int nFd;	//file descriptor
	int nHandler;	//device descriptor
	int nArg;

	if (-1 == (nHandler = open(RECORD_DEVICE, O_RDWR)))
	{
		perror("Cannot open the record device!\n");
		return EXIT_FAILURE;
	}

	//set sample rate
	nArg = RATE;
	if (-1 == ioctl(nHandler, SOUND_PCM_WRITE_RATE, &nArg))
	{
		perror("cannot set sample rate!\n");
		close(nHandler);
		return EXIT_FAILURE;
	}

	//set digitalizing bits
	nArg = SIZE;
	if (-1 == ioctl(nHandler, SOUND_PCM_WRITE_BITS, &nArg))
	{
		perror("cannot set digitalizing bits!\n");
		close(nHandler);
		return EXIT_FAILURE;
	}

	//set sample channel mode
	nArg = CHANNEL;
	if (-1 == ioctl(nHandler, SOUND_PCM_WRITE_CHANNELS, &nArg))
	{
		perror("cannot set sample channel mode!\n");
		close(nHandler);
		return EXIT_FAILURE;
	}

	if (-1 == (nFd = open(RECORD_FILE, O_CREAT | O_WRONLY, 0777)))
	{
		perror("Cannot create the recording file!\n");
		close(nHandler);
		return EXIT_FAILURE;
	}

	for (;;)
	{
		printf("Recording...\n");
		//start recording from device and store it into buffer
		if (-1 == read(nHandler, chBuffer, sizeof(chBuffer)))
		{
			perror("cannot record from device!\n");
			close(nHandler);
			close(nFd);
			return EXIT_FAILURE;
		}

		printf("Playing...\n");
		//play sound from buffer
		if (-1 == write(nHandler, chBuffer, sizeof(chBuffer)))
		{
			perror("cannot play sound!\n");
			close(nHandler);
			close(nFd);
			return EXIT_FAILURE;
		}

		//I don't know why cannot I play this file???
		if (-1 == write(nFd, chBuffer, sizeof(chBuffer)))
		{
			perror("Cannot write sound to file!\n");
			close(nHandler);
			close(nFd);
			return EXIT_FAILURE;
		}

		//wait for stopping playing
		if (-1 == ioctl(nHandler, SOUND_PCM_SYNC, 0))
		{
			perror("cannot set SOUND_PCM_SYNC!\n");
			close(nHandler);
			close(nFd);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
