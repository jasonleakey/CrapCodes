/*
 *  C_pattern_classification - TODO
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
#include <time.h>
#include "samples.h"


#define FREEALL(void) \
	NULL == trLab ? NULL : free(trLab);\
	NULL == trImg ? NULL : free(trImg);\
	NULL == tsLab ? NULL : free(tsLab);\
	NULL == tsImg ? NULL : free(tsImg);\
	for (k = 0; k < INPUT_VECTOR_NUM; k++)\
	{\
		NULL == InHidnWt[k] ? NULL : free(InHidnWt[k]);\
	}\
	for (k = 0; k < HIDN_VECTOR_NUM; k++)\
	{\
		NULL == HidnOutWt[k] ? NULL : free(HidnOutWt[k]);\
	}\
	NULL == InHidnWt ? NULL : free(InHidnWt);\
	NULL == HidnOutWt ? NULL : free(HidnOutWt);\
	NULL == HidnThresh ? NULL : free(HidnThresh);\
	NULL == OutThresh ? NULL : free(OutThresh);\
	NULL == inputVector ? NULL : free(inputVector);\
	NULL == hidnVector ? NULL : free(hidnVector);\
	NULL == outputVector ? NULL : free(outputVector);\
	NULL == ExpectedOutputVector ? NULL : free(ExpectedOutputVector);

#define QUANTIZE(output_vector) \
	int m = 0;\
	for (m = 0; m < OUTPUT_VECTOR_NUM; m++)\
	{\
		output_vector[m] = output_vector[m] > 0.55 ? 1.0 : 0.0;\
	}

#define BIT2DEC(output_vector) \
	(char)output_vector[0] << 3\
	| (char)output_vector[1] << 2\
	| (char)output_vector[2] << 1\
	| (char)output_vector[3]

extern void get_train_label(TrainLabel* train_label);
extern void get_train_image(TrainImg* train_image);
extern void get_test_label(TestLabel* test_label);
extern void get_test_image(TestImg* test_image);
extern void init(
        float** in_hidn_wet,
        float** hidn_out_wet,
        float* hidn_thresh,
        float* out_thresh);

extern void forward(
        const float* const input_vector,
        float* const hidn_vector,
        float* const output_vector,
        float** const in_hidn_wet,
        float** const hidn_out_wet,
        float* const hidn_thresh,
        float* const out_thresh);
extern void back_propagate(
        float* input_vector,
        float* hidn_vector,
        float* output_vector,
        float* expt_output_vector,
        float** in_hidn_wet,
        float** hidn_out_wet,
        float* hidn_thresh,
        float* out_thresh);

int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int nErrNum = 0; /* error number count */
	TrainLabel* trLab = NULL;
	TrainImg* trImg = NULL;
	TestLabel* tsLab = NULL;
	TestImg* tsImg = NULL;
	float* inputVector = NULL;
	float* hidnVector = NULL;
	float* outputVector = NULL;
	float* ExpectedOutputVector = NULL;
	float** InHidnWt = NULL;
	float** HidnOutWt = NULL;
	float* HidnThresh = NULL;
	float* OutThresh = NULL;
	long nStartTrainSec = 0;
	long nStartTestSec = 0;
	/*
	 * allocate space
	 */
	if (NULL == (trLab = (TrainLabel*) malloc(sizeof(TrainLabel)))
		|| NULL == (trImg = (TrainImg*) malloc(sizeof(TrainImg)))
		|| NULL == (tsLab = (TestLabel*) malloc(sizeof(TestLabel)))
		|| NULL == (tsImg = (TestImg*) malloc(sizeof(TestImg)))
		|| NULL == (HidnThresh = (float*) malloc(sizeof(float) * HIDN_VECTOR_NUM))
		|| NULL == (OutThresh = (float*) malloc(sizeof(float) * OUTPUT_VECTOR_NUM))
        || NULL == (inputVector = (float*) malloc(sizeof(float) * INPUT_VECTOR_NUM))
		|| NULL == (hidnVector = (float*) malloc(sizeof(float) * HIDN_VECTOR_NUM))
		|| NULL == (outputVector = (float*) malloc(sizeof(float) * OUTPUT_VECTOR_NUM))
		|| NULL == (ExpectedOutputVector = (float*) malloc(sizeof(float) * OUTPUT_VECTOR_NUM)))
	{
		fprintf(stderr, "malloc:%s, Line %d in %s\n", strerror(errno), __LINE__,
		        __FILE__);
		FREEALL();
		exit(1);
	}
	if (NULL == (InHidnWt = (float**) malloc(sizeof(float*) * INPUT_VECTOR_NUM)))
	{
		fprintf( stderr, "malloc:%s, Line %d in %s\n", strerror(errno), __LINE__,
		        __FILE__);
		FREEALL();
		exit(1);
	}
	for (i = 0; i < INPUT_VECTOR_NUM; i++)
	{
		if (NULL == (InHidnWt[i] = (float*) malloc(sizeof(float) * HIDN_VECTOR_NUM)))
		{
			fprintf( stderr, "error in InHidnWt malloc:%s, Line %d in %s\n", strerror(errno), __LINE__,
			        __FILE__);
			FREEALL();
			exit(1);
		}
	}
	if (NULL == (HidnOutWt = (float**) malloc(sizeof(float*) * HIDN_VECTOR_NUM)))
	{
		fprintf( stderr, "malloc HidnOutWt:%s, Line %d in %s\n", strerror(errno), __LINE__,
		        __FILE__);
		FREEALL();
	}
	for (i = 0; i < HIDN_VECTOR_NUM; i++)
	{
		if (NULL == (HidnOutWt[i] = (float*) malloc(sizeof(float) * OUTPUT_VECTOR_NUM)))
		{
			fprintf(stderr, "error in HidnOutWt:%s, Line %d in %s\n", strerror(
			        errno), __LINE__, __FILE__);
			FREEALL();
			exit(1);
		}
	}

	/*
	 * read samples
	 */
	get_train_label(trLab);
	get_train_image(trImg);
	get_test_label(tsLab);
	get_test_image(tsImg);


	/*
	 * initialize weight and threshold, and then normalize input vector
	 */
	init(InHidnWt, HidnOutWt, HidnThresh, OutThresh);

	nStartTrainSec = time(NULL);

	for (i = 0; i < TRAIN_SAMPLE_NUM; i++)
	{
		char nTrainedNum = 0;
		printf("Training Sample: %d Label: %d ", i + 1, trLab->label[i]);
		for (j = 0; j < ROWS; j++)
		{
			for (k = 0; k < COLUMNS; k++)
			{
				inputVector[j * COLUMNS + k] = trImg->img[i][j][k] / 255.0;
			}
		}
		for (j = 0; j < OUTPUT_VECTOR_NUM; j++)
		{
			ExpectedOutputVector[j] = trLab->label[i] >> (OUTPUT_VECTOR_NUM - j - 1) & 0x1;
		}

		forward(
		        inputVector,
		        hidnVector,
		        outputVector,
		        InHidnWt,
		        HidnOutWt,
		        HidnThresh,
		        OutThresh);

		back_propagate(
		        inputVector,
		        hidnVector,
		        outputVector,
		        ExpectedOutputVector,
		        InHidnWt,
		        HidnOutWt,
		        HidnThresh,
		        OutThresh);
		forward(
		        inputVector,
		        hidnVector,
		        outputVector,
		        InHidnWt,
		        HidnOutWt,
		        HidnThresh,
		        OutThresh);

		QUANTIZE(outputVector);
		nTrainedNum = BIT2DEC(outputVector);

		if (trLab->label[i] != nTrainedNum)
		{
			nErrNum++;
		}

		printf("Trained Number: %d\n", nTrainedNum);
	}

	printf("time: %lds, Error Number Count: %d, Error Rate = %.2f%%\n",
			time(NULL) - nStartTrainSec,
			nErrNum, (float) nErrNum / TRAIN_SAMPLE_NUM * 100);

	printf("press ENTER to begin test...");
	getchar();

	nStartTestSec = time(NULL);


	/*
	 * begin test
	 */
	nErrNum = 0;
	memset(inputVector, '\0', INPUT_VECTOR_NUM * sizeof(float));
	memset(ExpectedOutputVector, '\0', OUTPUT_VECTOR_NUM * sizeof(float));
	memset(outputVector, '\0', OUTPUT_VECTOR_NUM * sizeof(float));
	for (i = 0; i < TEST_SAMPLE_NUM; i++)
	{
		char nTrainedNum = 0;
		printf("Test Sample: %d Label: %d ", i + 1, tsLab->label[i]);
		for (j = 0; j < ROWS; j++)
		{
			for (k = 0; k < COLUMNS; k++)
			{
				/*
				 * 255.0 is the max gray value
				 */
				inputVector[j * COLUMNS + k] = tsImg->img[i][j][k] / 255.0;
			}
		}
		for (j = 0; j < OUTPUT_VECTOR_NUM; j++)
		{
			ExpectedOutputVector[j] = tsLab->label[i] >> (OUTPUT_VECTOR_NUM - j - 1) & 0x1;
		}

		forward(
		        inputVector,
		        hidnVector,
		        outputVector,
		        InHidnWt,
		        HidnOutWt,
		        HidnThresh,
		        OutThresh);

		/*
		 * make each output unit to be a integer
		 */
		QUANTIZE(outputVector);
		/*
		 * transform 4-bit to a number
		 */
		nTrainedNum = BIT2DEC(outputVector);

		if (tsLab->label[i] != nTrainedNum)
		{
			nErrNum++;
		}

		printf("Trained Number: %d\n", nTrainedNum);
	}

	printf("time: %lds, Error Number Count: %d, Error Rate = %.2f%%\n",
			time( NULL) - nStartTestSec,
			nErrNum, (float) nErrNum / TEST_SAMPLE_NUM * 100);

	FREEALL();
	return 0;
}
