/*
 *  Establishment date:  2009-5-6
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
 *  algo.c:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "image.h"

#define MAX(A, B) ((A) > (B) ? (A) : (B))

// the four dimensions within image[][][][]
// represents TYPE, frame, i, j in turn.
int find_blind(double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		point_t blind_point[])
{
	int t = 0;
	int f = 0;
	int i = 0;
	int j = 0;
	int bld_cnt = 0; //blind-pixel amount
	int bad_cnt = 0;
//	double sum = 0.0;
	static double V[TYPE][SCL_FRM_CNT][ROW][COLUMN] = {0.0};
	//average voltage matrix of pixels at TYPE T1
	static double V_[TYPE][ROW][COLUMN] = {0.0};
	static double V_nT1[ROW][COLUMN] = {0.0};
	static double V_s[ROW][COLUMN] = {0.0};
	double V_nT1_ = 0.0;
	double V_s_ = 0.0;


	memcpy(V, scaling, TYPE * SCL_FRM_CNT * ROW * COLUMN * sizeof(double));
	//calculate the voltage matrix for each frame.
	for (t = 0; t < TYPE; t++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				for (f = 0; f < SCL_FRM_CNT; f++)
				{
					V[t][f][i][j] *= (5000.0/4095);
					V_[t][i][j] += V[t][f][i][j];
				}
				V_[t][i][j] /= SCL_FRM_CNT;
			}
		}
	}

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			for (f = 0; f < SCL_FRM_CNT; f++)
			{
				V_nT1[i][j] += pow(V[0][f][i][j] - V_[0][i][j], 2);
			}
			V_nT1[i][j] = sqrt(V_nT1[i][j] / (SCL_FRM_CNT - 1));
			V_s[i][j] = V_[1][i][j] - V_[0][i][j];
			V_s_ += V_s[i][j];
		}
	}
	V_s_ /= (ROW * COLUMN);

	//pixel signals and its average.
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			/* remove bad pixel which's signal difference at two temperature is
			 * below 5mV.
			 */
			if (V_s[i][j] < 5)
			{
				blind_point[bld_cnt].x = i;
				blind_point[bld_cnt].y = j;
				bld_cnt++;
			}
		}
	}

	if (0 != bld_cnt)
	{
		/* there are blind pixels */
		V_s_ = 0.0;
		V_nT1_ = 0.0;
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				int s = 0;
				for (s = 0; s < bld_cnt && blind_point[s].x != i\
					&& blind_point[s].y != j; s++)
				{
					;
				}
				if (s >= bld_cnt)
				{
					V_s_ += V_s[i][j];
					V_nT1_ += V_nT1[i][j];
				}
			}
		}
		V_s_ /= (ROW * COLUMN - bld_cnt);
		V_nT1_ /= (ROW * COLUMN - bld_cnt);
	}

	bad_cnt = bld_cnt;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			int s = 0;
			for (s = 0; s < bad_cnt && blind_point[s].x != i\
				&& blind_point[s].y != j; s++)
			{
				;
			}
			if (s >= bad_cnt
				&& (V_s[i][j] > 2 * V_s_\
				|| V_s[i][j] < V_s_ / 2\
				|| V_nT1[i][j] > 3 * V_nT1_))
			{
				blind_point[bld_cnt].x = i;
				blind_point[bld_cnt].y = j;
				bld_cnt++;
			}
		}
	}

	return bld_cnt;
}

static int ifBlind(int cur, int x, int y, point_t blind_point[], int cnt)
{
	int k = 0;

	if (x < 0 || x >= COLUMN || y < 0 || y >= ROW)
	{
		return 0;
	}

	for (k = MAX(0, cur - COLUMN - 2); k < cnt; k++)
	{
		if (x == blind_point[k].x && y == blind_point[k].y)
		{
			return 1;
		}
	}

	return 0;
}

int remove_blind(double frames[][ROW][COLUMN], int frame_cnt,\
		point_t blind_point[], int cnt)
{
	int i = 0;
	int j = 0;
	int f = 0;
	int cur = 0;
	int k = 0;
	double adjacent_sum = 0.0;


	for (cur = 0; cur < cnt; cur++)
	{
		i = blind_point[cur].x;
		j = blind_point[cur].y;
		point_t adjacent[8] = {{i, j - 1}, {i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1},\
				{i, j + 1}, {i + 1, j + 1}, {i + 1, j}, {i + 1, j - 1}};
		for (f = 0; f < frame_cnt; f++)
		{
			frames[f][i][j] = 0.0;
			int valid_adjacent = 0;
			for (k = 0; k < 8; k++)
			{
				if (!ifBlind(cur, adjacent[k].x, adjacent[k].y, blind_point, cnt))
				{
					valid_adjacent++;
					frames[f][i][j] += frames[f][adjacent[k].x][adjacent[k].y];
				}
			}
			frames[f][i][j] /= valid_adjacent;
		}
	}

	return 0;
}


int store_data(double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		double imaging[IMG_FRM_CNT][ROW][COLUMN], subframe_t sub_frames[])
{
	int sf = 0;
	int i = 0;
	int j = 0;
	mode_t cur_mode = sub_frames[0].mode;
	WORD cur_count = sub_frames[0].frame_count / SUBFRAMES;
	if (cur_count < 0)
	{
		printf("invalid frame!\n");
		return -1;
	}
	else if (cur_count < SCL_FRM_CNT)
	{
		; /*normal temperature frame*/
	}
	else if (cur_count < 2 * SCL_FRM_CNT)
	{
		cur_count -= SCL_FRM_CNT; /* high temperature frame */
	}
	else
	{
		cur_count -= (2 * SCL_FRM_CNT); /* imaging frame */
	}
	double A_frame[ROW * COLUMN] = {0.0};

	/* make up every pixel in each sub frame to a frame
	 * without the last sub frame because its particularity.*/
	for (sf = 0; sf < SUBFRAMES - 1; sf++)
	{
		for (j = 0; j < SUBF_PIXEL_COUNT; j++)
		{
			A_frame[i + j] =\
				(double)sub_frames[sf].img_data[j];
		}
		i += SUBF_PIXEL_COUNT;
	}

	/* the last sub frame involves useless 46-pixels((154*499 - 320*240)/2)
	 * not to be stored */
	for (j = 0; j < SUBF_PIXEL_COUNT - 46; j++)
	{
		A_frame[i + j] = \
			(double)sub_frames[sf].img_data[j];
	}

	switch (cur_mode)
	{
		case LOW_T:
			/* store 19 frames of normal temperature */
			memcpy(scaling[0][cur_count], A_frame,\
					ROW * COLUMN * sizeof(double));
			break;
		case HIGH_T:
			/* store 19 frames of high temperature */
			memcpy(scaling[1][cur_count], A_frame,\
					ROW * COLUMN * sizeof(double));
			break;
		case IMAGING:
			/* store 135 imaging frames */
			memcpy(imaging[cur_count], A_frame,\
					ROW * COLUMN * sizeof(double));
			break;
		default:
			return -1;
	}

	return 0;
}

int get_coefficient(const double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		double G[ROW][COLUMN], double O[ROW][COLUMN])
{
	int t = 0;
	int f = 0;
	int i = 0;
	int j = 0;

	double E_HL[TYPE][ROW][COLUMN] = {0.0};
	double E_avr_HL[TYPE] = {0.0};
	double E = 0.0;

	for (t = 0; t < TYPE; t++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				for (f = 0; f < SCL_FRM_CNT; f++)
				{
					E_HL[t][i][j] += scaling[t][f][i][j];
				}
				E_HL[t][i][j] /= SCL_FRM_CNT;
				E_avr_HL[t] += E_HL[t][i][j];
			}
		}
		E_avr_HL[t] /= (ROW * COLUMN);
	}

	E = E_avr_HL[1] - E_avr_HL[0];

	//calculate the coefficients.
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			G[i][j] = E	/ (E_HL[1][i][j] - E_HL[0][i][j]);
			O[i][j] = (E_avr_HL[0] * E_HL[1][i][j] - E_avr_HL[1] * E_HL[0][i][j])\
					/ (E_HL[1][i][j] - E_HL[0][i][j]);
		}
	}

	return 0;
}

int correct_img(double imaging[IMG_FRM_CNT][ROW][COLUMN],\
		double G[ROW][COLUMN], double O[ROW][COLUMN])
{
	int i = 0;
	int j = 0;
	int k = 0;
	double temp = 0.0;

	for (k = 0; k < IMG_FRM_CNT; k++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				temp = imaging[k][i][j];
				imaging[k][i][j] = G[i][j] * imaging[k][i][j] + O[i][j];
				imaging[k][i][j] = temp - O[i][j] + 1024;
			}
		}
	}

	return 0;
}

int output_txt(double matrix[][ROW][COLUMN], int frames, char type)
{
	int i = 0;
	int j = 0;
	char* txtname = NULL;
	char chNum[30];
	FILE* fp = NULL;

	switch (type)
	{
		case 'I':
			txtname = "input.txt";
			break;
		case 'O':
			txtname = "output.txt";
			break;
		case 'G':
			txtname = "G.txt";
			break;
		case 'B':
			txtname = "O.txt";
			break;
		default:
			printf("unknown type!\n");
			return -1;
	}

	if (NULL == (fp = fopen(txtname, "w"))	)
	{
		printf("Error opening txt!\n");
		return -1;
	}

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COLUMN; j++)
		{
			memset(chNum, '\0', 30);
			sprintf(chNum, "%4.6f ", matrix[0][i][j]);
			fwrite(chNum, sizeof(char), strlen(chNum), fp);
		}
		char k = '\n';
		fwrite(&k, 1, 1, fp);
	}

	fclose(fp);

	return 0;
}


/* create unchanged Bitmaps */
int create_BMPs(double image[][ROW][COLUMN], int frame_count, char type)
{
	int i = 0;
	int j = 0;
	int k = 0;
	FILE *fp = NULL;
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	char filename[frame_count][20];
	BYTE RGB_value[3] = {0};
	char prefix = type;
	char* suffix = ".bmp";

	fh.bfType = 0x4d42;
	fh.bfSize = 230454; /* 54 + 320 * 240 * 24 / 8 = 0x038438*/
	fh.bfReserved1 = 0;
	fh.bfReserved2 = 0;
	fh.bfOffBits = 0x36;

	ih.biSize = 0x28;
	ih.biWidth = 320;
	ih.biHeight = 240;
	ih.biPlanes = 0x01;
	ih.biBitCount = 24; /* 24-bit Bitmap */
	ih.biCompression = 0; /* no compression */
	ih.biSizeImage = 230400; /* 320 * 240 * 24 / 8 = 0x038400 */
	ih.biXPelsPerMeter = 0;
	ih.biYPelsPerMeter = 0;
	ih.biClrUsed = 0;
	ih.biClrImportant = 0;



	for (k = 0; k < frame_count; k++)
	{
		filename[k][0] = prefix;
		sprintf(&filename[k][1], "%d", k); /* transform k to string format */
		if (NULL == (fp = fopen(strcat(&filename[k][1], suffix) - 1, "wb")))
		{
			printf("cannot create old bmps!\n");
			return -1;
		}

		/* write file header */
		if (fwrite(&fh, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
		{
			printf("cannot write file header to old bmps!\n");
			fclose(fp);
			return -1;
		}

		/* write information header */
		if (fwrite(&ih, sizeof(BITMAPINFOHEADER), 1, fp) < 1)
		{
			printf("cannot write info header to old bmps!\n");
			fclose(fp);
			return -1;
		}

		/* store data into bmp from left to right,from bottom to top */
		for (i = ROW - 1; i > -1; i--)
		{
			for (j = 0; j < COLUMN; j++)
			{
				/* transform gray level to RGB format of same value */
				RGB_value[2] = RGB_value[1] = RGB_value[0] =\
					(BYTE)(image[k][i][j] * 255 / ((2<<12) - 1));
				fwrite(&RGB_value, sizeof(RGB_value), 1, fp);
			}
		}

		fclose(fp);
		fp = NULL;
	}

	return 0;
}




