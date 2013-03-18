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

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/soundcard.h>

#define AUDIO_DEVICE "/dev/dsp"
//arguments are different depending on sound,
//that can be get with command 'file'
#define SAMPLE_SIZE 16 //there are two kinds of bits, 8 bits and 16 bits
#define SAMPLE_RATE 48000  //Sample rate
#define SAMPLE_CHANNEL 1	//if 1,channel is set to be stereo; else mono

int play_sound(char* pchFileName)
{
	struct stat stat_buf;
	unsigned char* pchBuf = NULL;
	int nHandler;
	int nFd;
	int nResult;
	int nArg;
	int nStatus;

	//open the music file
	if (-1 == (nFd = open(pchFileName, O_RDONLY)))
	{
		perror("Cannot open music file!\n");
		return -1;
	}

	//store the file's information in stat_buf
	if (-1 == fstat(nFd, &stat_buf))
	{
		close(nFd);
		return -1;
	}

	//if the size of file is 0, then return Error
	if (0 == stat_buf.st_size)
	{
		close(nFd);
		return -1;
	}


	if (NULL == (pchBuf = (unsigned char*)malloc(stat_buf.st_size)))
	{
		close(nFd);
		return -1;
	}

	//store its info to the buffer
	if (read(nFd, pchBuf, stat_buf.st_size) < 0)
	{
		free(pchBuf);
		close(nFd);
		return -1;
	}

	if (-1 == (nHandler = open(AUDIO_DEVICE, O_WRONLY)))
	{
		perror("Cannot open the Audio_device!\n");
		return -1;
	}

	//set sampling rate
	nArg = SAMPLE_RATE;
	if (-1 == (nStatus = ioctl(nHandler, SOUND_PCM_WRITE_RATE, &nArg)))
	{
		perror("Error from SOUND_PCM_WRITE_RATE ioctl!\n");
		return -1;
	}

	//设置量化位数
	nArg = SAMPLE_SIZE;
	if (-1 == (nStatus = ioctl(nHandler, SOUND_PCM_WRITE_BITS, &nArg)))
	{
		perror(("Error from SOUND_PCM_WRITE_BITS ioctl!\n"));
		return -1;
	}

	//set sound track channels
	nArg = SAMPLE_CHANNEL;
	if (-1 == (nStatus = ioctl(nHandler, SOUND_PCM_WRITE_CHANNELS, &nArg)))
	{
		perror("Unable to set SOUND_PCM_WRITE_CHANNELS ioctl!\n");
		return -1;
	}

	//start playing
	printf("Playing...\n");
	if (-1 == (nResult = write(nHandler, pchBuf, stat_buf.st_size)))
	{
		perror("Fail to play the sound!\n");
		return -1;
	}
	printf("Over...\n");

	free(pchBuf);
	close(nFd);
	close(nHandler);

	return nResult;
}

int main(int argc, char **argv)
{
	play_sound("/home/jasonleakey/音乐/新仙剑奇侠传/M003.wav");

	return 0;
}
