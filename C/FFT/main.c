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
#include <errno.h>
#include "complex.h"

extern COMPLEX* FFT(COMPLEX* a, int len);
extern COMPLEX** FFT2(COMPLEX** a, int row, int col);

int main(int argc, char **argv)
{
	int dim = 0;
	int m = 0;
	int n = 0;
	int i = 0;
	int j = 0;
	FILE* datfile = NULL;

	printf("Dimension(1 or 2):");
	while (1 != scanf("%d", &dim) && dim == EOF)
	{
		;
	}
	if (1 != dim && 2 != dim)
	{
		printf("invalid input! Dimension should be 1 or 2\n");
		return -1;
	}

	if (NULL == (datfile = fopen(dim == 1 ? "fft.dat" : "fft2.dat", "r")))
	{
		fprintf(stderr, "fopen:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		return -1;
	}
	if (1 == dim)
	{
		fscanf(datfile, "%d", &n);
		printf("vector number:%d\n", n);
		COMPLEX *Ak = (COMPLEX*)malloc(sizeof(COMPLEX) * n);
		COMPLEX *Xn = NULL;
		for (i = 0; i < n; i++)
		{
			fscanf(datfile, "%f,%f", &Ak[i].real, &Ak[i].img);
		}
		printf("Input vector:\n");
		for (i = 0; i < n; i++)
		{
			printf("%.2f%+.2fi\n", Ak[i].real, Ak[i].img);
		}

		Xn = FFT(Ak, n);
		printf("output vector:\n");
		for (i = 0; i < n; i++)
		{
			printf("%.2f%+.2fi\n", Xn[i].real, Xn[i].img);
		}
		free(Ak);
		free(Xn);
	}
	else
	{
		fscanf(datfile, "%d %d", &m, &n);
		printf("row length: %d, column length: %d\n", m, n);
		COMPLEX** Ak = NULL;
		if (NULL == (Ak  = (COMPLEX**)malloc(m * sizeof(COMPLEX**))))
		{
			fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
					__LINE__, __FILE__);
			exit(-1);
		}
		COMPLEX** Xn = NULL;
		printf("Input matrix:\n");
		for (i = 0; i < m; i++)
		{
			if (NULL == (Ak[i] = (COMPLEX*)malloc(sizeof(COMPLEX) * n)))
			{
				fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno),\
						__LINE__, __FILE__);
				exit(-1);
			}
			for (j = 0; j < n; j++)
			{
				fscanf(datfile, "%f,%f", &Ak[i][j].real, &Ak[i][j].img);
				printf("%.2f%+.2fi ", Ak[i][j].real, Ak[i][j].img);
			}
			printf("\n");
		}

		Xn = FFT2(Ak, m, n);
		printf("output matrix:\n");
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				printf("%.2f%+.2fi ", Xn[i][j].real, Xn[i][j].img);
			}
			printf("\n");
		}
		free(Ak);
		free(Xn);
	}

	fclose(datfile);
	return 0;
}
