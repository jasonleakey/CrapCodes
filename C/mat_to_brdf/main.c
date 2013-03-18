/*
 *  Date:   Jun 15, 2009
 *  Author:	jasonleakey
 *  Change Log:
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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "brdf.h"




int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int angleCount = 0;
	char dir_name[MAX_DIR_NAME_LEN] = "/home/jasonleakey/090610";
	char lineBuf[MAX_LINE_LEN];
	typedef char String[13];
	String sevenAngle[7];

	static angle_irr_t angleIrr[ANGLE_INFO_CNT];
	FILE* anglesStream = NULL;
	FILE* irrStream = NULL;
	FILE* brdfStream = NULL;
	char irrName[IRR_FILE_NAME_LEN];



	/*
	printf("Input path way:");
	scanf("%s", dir_name);
	*/
	if (-1 == (chdir(dir_name)))
	{
		fprintf(stderr, "chdir():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		return EXIT_FAILURE;
	}

	if (NULL == (anglesStream = fopen("/home/jasonleakey/090610/angles_new.txt", "r")))
	{
		fprintf(stderr, "fopen():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		return EXIT_FAILURE;
	}

	printf("current file pointer is %ld\n", ftell(anglesStream));

	for (i = 0; i < ANGLE_INFO_CNT; i++)
	{
		printf("current file pointer is %ld\n", ftell(anglesStream));
		printf("i = %d\n", i);
		memset(lineBuf, '\0', sizeof(lineBuf));
		if (NULL == fgets(lineBuf, MAX_LINE_LEN, anglesStream))
		{
			fprintf(stderr, "fgets():%s, Line %d in %s\n", strerror(errno),\
					__LINE__, __FILE__);
			fclose(anglesStream);
			return EXIT_FAILURE;
		}
		printf("lineBuf=%s\n", lineBuf);
		printf("strlen(lineBuf) = %d\n", strlen(lineBuf));

		j = 0;
		k = 0;
		angleCount = 0;
		while('\0' != lineBuf[j] && '\r' != lineBuf[j] && '\n' != lineBuf[j])
		{
			if (' ' == lineBuf[j])
			{
				sevenAngle[angleCount][k] = '\0';
				k = 0;
				angleCount++;
			}
			else
			{
				sevenAngle[angleCount][k++] = lineBuf[j];
			}
			j++;
		}


		angleIrr[i].alpha = atof(sevenAngle[0]);
		angleIrr[i].beta = atof(sevenAngle[1]);
		angleIrr[i].gamma = atof(sevenAngle[2]);
		angleIrr[i].Itheta = atof(sevenAngle[3]);
		angleIrr[i].Iphi = atof(sevenAngle[4]);
		angleIrr[i].Rtheta = atof(sevenAngle[5]);
		angleIrr[i].Rphi = atof(sevenAngle[6]);

		memset(irrName, '\0', sizeof(irrName));
		irrName[0] = 'M';
		int a_len = 0;
		int b_len = 0;
		int c_len = 0;
		if (angleIrr[i].alpha >= 0)
		{
			strcpy(&irrName[1], &sevenAngle[0][0]);
			a_len = strlen(&sevenAngle[0][0]);
		}
		else
		{
			strcpy(&irrName[1], &sevenAngle[0][1]);
			a_len = strlen(&sevenAngle[0][1]);
		}
		irrName[1 + a_len] = '-';
		if (angleIrr[i].beta >= 0)
		{
			strcpy(&irrName[2 + a_len], &sevenAngle[1][0]);
			b_len = strlen(&sevenAngle[1][0]);
		}
		else
		{
			strcpy(&irrName[2 + a_len], &sevenAngle[1][1]);
			b_len = strlen(&sevenAngle[1][1]);
		}
		irrName[2 + a_len + b_len] = '-';
		if (angleIrr[i].gamma >= 0)
		{
			strcpy(&irrName[3 + a_len + b_len], &sevenAngle[2][0]);
			c_len = strlen(&sevenAngle[2][0]);
		}
		else
		{
			strcpy(&irrName[3 + a_len + b_len], &sevenAngle[2][1]);
			c_len = strlen(&sevenAngle[2][1]);
		}
		strcpy(&irrName[3 + a_len + b_len + c_len], ".txt");

		strcpy(dir_name, "./");
		if (NULL == (irrStream = fopen(strcat(dir_name, irrName), "r")))
		{
			fclose(anglesStream);
			fprintf(stderr, "fopen() %s:%s, Line %d in %s\n", irrName, strerror(errno),\
					__LINE__, __FILE__);
			return EXIT_FAILURE;
		}


		for (m = 0; m < WAVE_INFO_CNT; m++)
		{
			memset(lineBuf, '\0', sizeof(lineBuf));
			if (NULL == fgets(lineBuf, MAX_LINE_LEN, irrStream))
			{
				fprintf(stderr, "fgets():%s, Line %d in %s\n", strerror(errno),\
						__LINE__, __FILE__);
				fclose(anglesStream);
				fclose(irrStream);
				return EXIT_FAILURE;
			}

			char* p = NULL;

			if (0 != strlen(lineBuf))
			{
				if (NULL != (p = strtok(lineBuf, " ")))
				{
					angleIrr[i].wave_irr[m].lambda = atof(p);
				}

				if (NULL != (p = strtok(NULL, "\r")))
				{
					angleIrr[i].wave_irr[m].irr = atof(p);
				}
			}
		}
	}

	if (NULL == (brdfStream = fopen("/home/jasonleakey/090610/M.brdf", "wb")))
	{
		fclose(anglesStream);
		fclose(irrStream);
		fprintf(stderr, "fopen():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
	}

	if (ANGLE_INFO_CNT > fwrite(angleIrr, sizeof(angle_irr_t), ANGLE_INFO_CNT, brdfStream))
	{
		fclose(anglesStream);
		fclose(irrStream);
		fclose(brdfStream);
		fprintf(stderr, "fwrite():%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
	}


	fclose(irrStream);
	fclose(anglesStream);
	return 0;
}
