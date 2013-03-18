/*
 * MAT-file creation program
 *
 * See the MATLAB External Interfaces/API Guide for compiling information.
 *
 * Calling syntax:
 *
 *   matcreat
 *
 * Create a MAT-file which can be loaded into MATLAB.
 *
 * This program demonstrates the use of the following functions:
 *
 *  matClose
 *  matGetVariable
 *  matOpen
 *  matPutVariable
 *  matPutVariableAsGlobal
 *
 * Copyright 1984-2005 The MathWorks, Inc.
 */
/* $Revision: 1.13.4.2 $ */
#include <stdio.h>
#include <string.h> /* For strcmp() */
#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS */
#include <mat.h>
#include "image.h"

int store_data(short scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		short imaging[IMG_FRM_CNT][ROW][COLUMN], subframe_t sub_frames[])
{
	int f = 0;
	int i = 0;
	int j = 0;
	static short A_frame[ROW * COLUMN];

	mode_t cur_mode = sub_frames[0].mode;
	WORD cur_count = sub_frames[0].frame_count / SUBFRAMES;
	if (cur_count < 0)
	{
		printf("invalid frame!\n");
		return -1;
	}
	else if (cur_count < SCL_FRM_CNT)
	{
		NULL; /*normal temperature frame*/
	}
	else if (cur_count < 2 * SCL_FRM_CNT)
	{
		cur_count -= SCL_FRM_CNT; /* high temperature frame */
	}
	else
	{
		cur_count -= (2 * SCL_FRM_CNT); /* imaging frame */
	}


	/* make up every pixel in each sub frame to a frame
	 * without the last sub frame because its particularity.*/
	for (f = 0; f < SUBFRAMES - 1; f++)
	{
		for (j = 0; j < SUBF_PIXEL_COUNT; j++)
		{
			A_frame[i + j] =\
				(short)sub_frames[f].img_data[j];
		}
		i += SUBF_PIXEL_COUNT;
	}

	/* the last sub frame involves useless 46-pixels((154*499 - 320*240)/2)
	 * not to be stored */
	for (j = 0; j < SUBF_PIXEL_COUNT - 46; j++)
	{
		A_frame[i + j] = \
			(short)sub_frames[f].img_data[j];
	}

	switch (cur_mode)
	{
		case LOW_T:
			/* store 19 frames of normal temperature */
			memcpy(scaling[0][cur_count], A_frame,\
					ROW * COLUMN * sizeof(short));
			break;
		case HIGH_T:
			/* store 19 frames of high temperature */
			memcpy(scaling[1][cur_count], A_frame,\
					ROW * COLUMN * sizeof(short));
			break;
		case IMAGING:
			/* store 135 imaging frames */
			memcpy(imaging[cur_count], A_frame,\
					ROW * COLUMN * sizeof(short));
			break;
		default:
			return -1;
	}

	return 0;
}

int main(int argc, char** argv)
{
	FILE* yha_stream = NULL;
	int t = 0;
	int size = 0;
	size_t sub_frame_size; // size of a sub frame
	char* yhafile = "C:\\78ok.yha";
	subframe_t sub_frames[SUBFRAMES];
	static short scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN];//scaling[2][19][240][320]
	static short imaging[IMG_FRM_CNT][ROW][COLUMN];//imaging[135][240][320]

	MATFile* pmatfile = NULL;
	mxArray* pImg = {NULL};
	char* chMatFileName = "C:\\img.mat";
	int dims[3] = {ROW, COLUMN, TTL_FRAME};
	int i = 0;
	int j = 0;
	int f = 0;
	short* pData = NULL;

	// check existence of the file
	if (NULL == (yha_stream = fopen(yhafile, "rb")))
	{
		printf("No such file!\n");
		return -3;
	}

	printf("sizeof(subframe_t)=%d\n", sub_frame_size = sizeof(subframe_t));
	// read a frame(or a photo) every time
	printf("current file pointer is %ld\n", ftell(yha_stream));
	while (SUBFRAMES == (size = fread(sub_frames,\
				sub_frame_size, SUBFRAMES, yha_stream)))
	{
		printf("read a frame.\n");
		if (-1 == store_data(scaling, imaging, sub_frames))
		{
			printf("Error mode in %s!\n", argv[1]);
			fclose(yha_stream);
			return -4;
		}
		printf("current file pointer is %ld\n", ftell(yha_stream));
		/*fseek(yha_stream, sub_frame_size * SCL_FRM_CNT, SEEK_CUR);*/
		/*printf("current file pointer is %ld\n", ftell(yha_stream));*/
		memset(sub_frames, 0.0, SUBFRAMES * sub_frame_size);
	}

	if (NULL == (pmatfile = matOpen(chMatFileName, "w")))
	{
		printf("cannot create mat file!\n");
		return -1;
	}


	printf("sizeof(mxArray)=%d\n", sizeof(mxArray));
	printf("sizeof(short)=%d", sizeof(short));
	if (NULL == (pImg = mxCreateNumericArray(3, dims, mxUINT16_CLASS, mxREAL)))
	{
		printf("%s:Out of memory on line %d\n", __FILE__, __LINE__);
		return -1;
	}

	pData = mxGetData(pImg);
	for (f = 0; f < SCL_FRM_CNT; f++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				pData[ROW * COLUMN * f + ROW * j + i] = scaling[0][f][i][j];
			}
		}
	}
	
	for (; f < SCL_FRM_CNT<<2; f++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				pData[ROW * COLUMN * f + ROW * j + i] = scaling[1][f - SCL_FRM_CNT][i][j];
			}
		}
	}
	
	for (; f < TTL_FRAME; f++)
	{
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COLUMN; j++)
			{
				pData[ROW * COLUMN * f + ROW * j + i] = imaging[f - 2 * SCL_FRM_CNT][i][j];
			}
		}
	}

	if (0 != matPutVariable(pmatfile, "img", pImg))
	{
		printf("%s :  Error using matPutVariable on line %d\n", __FILE__, __LINE__);
		return(EXIT_FAILURE);
	}

	mxDestroyArray(pImg);

	if (matClose(pmatfile) != 0)
	{
	    printf("Error closing file %s\n", chMatFileName);
	    return(EXIT_FAILURE);
	}

	fclose(yha_stream);
	return EXIT_SUCCESS;
}