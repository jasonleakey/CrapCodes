/*
 *  C_FFT - TODO
 *
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include "complex.h"
#define PI 3.1415926

COMPLEX *FFT(COMPLEX *a, int n)
{
	int i = 0;
	int k = 0;
	if (1 == n)
	{
		return a;
	}
	COMPLEX W = {1.0, 0.0};
	COMPLEX Wn = {cos(2 * PI / n), -sin(2 * PI / n)};

	COMPLEX* a0 = NULL;
	COMPLEX* a1 = NULL;
	if (NULL == (a0 = (COMPLEX*)malloc(sizeof(COMPLEX) * n))
			|| NULL == (a1 = (COMPLEX *)malloc(sizeof(COMPLEX) * n)))
	{
		fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(-1);
	}
	memset(a0, '\0', sizeof(COMPLEX) * (n / 2));
	memset(a1, '\0', sizeof(COMPLEX) * (n / 2));

	for (i = 0; i < n / 2; i++)
	{
		ComCpy(&a0[i], &a[2 * i]);
		ComCpy(&(a1[i]), &(a[2 * i + 1]));
	}

	COMPLEX* y0 = FFT(a0, n / 2);
	COMPLEX* y1 = FFT(a1, n / 2);
	COMPLEX* y = NULL;
	if (NULL == (y = (COMPLEX*)malloc(sizeof(COMPLEX) * n)))
	{
		fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(-1);
	}
	memset(y, '\0', sizeof(COMPLEX) * (n / 2));

	for (k = 0; k < n / 2; k++)
	{
		COMPLEX result = {0.0, 0.0};
		ComMul(&W, &y1[k], &result);
		ComAdd(&y0[k], &result, &y[k]);
		ComSub(&y0[k], &result, &y[k + n / 2]);
		ComMul(&W, &Wn, &result);
		ComCpy(&W, &result);
	}

	return y;
}

COMPLEX** FFT2(COMPLEX** a, int row, int col)
{
	int i = 0;
	int j = 0;
	COMPLEX** yRow = NULL;
	if (NULL == (yRow = (COMPLEX**)malloc(row * sizeof(COMPLEX**))))
	{
		fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(-1);
	}
	COMPLEX **y2 = NULL;
	if (NULL == (y2 = (COMPLEX**)malloc(row * sizeof(COMPLEX**))))
	{
		fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		free(yRow);
		exit(-1);
	}
	for (i = 0; i < row; i++)
	{
		if (NULL == (y2[i] = (COMPLEX*)malloc(sizeof(COMPLEX) * col)))
		{
			fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
					__LINE__, __FILE__);
			exit(-1);
		}
	}

	for (i = 0; i < row; i++)
	{
		yRow[i] = FFT(a[i], col);
	}

	for (j = 0; j < col; j++)
	{
		COMPLEX* colVector = NULL;
		COMPLEX* fftColVector = NULL;
		if (NULL == (colVector = (COMPLEX*)malloc(sizeof(COMPLEX) * row)))
		{
			fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
					__LINE__, __FILE__);
			exit(-1);
		}
		for (i = 0; i < row; i++)
		{
			colVector[i] = yRow[i][j];
		}
		fftColVector = FFT(colVector, row);
		for (i = 0; i < row; i++)
		{
			y2[i][j] = fftColVector[i];
		}
		free(colVector);
	}

	return y2;
}
