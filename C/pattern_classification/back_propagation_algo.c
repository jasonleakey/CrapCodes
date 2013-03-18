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
#include <math.h>
#include <time.h>
#include "samples.h"

/*
 * generate random number between (-1, 1)
 */
#define frand(void) ((float)rand() / (RAND_MAX / 2) - 1.0)

void init(float** in_hidn_wet,
		float** hidn_out_wet,
		float* hidn_thresh,
		float* out_thresh)
{
	int i = 0;
	int j = 0;

	srand((unsigned int)time(NULL));
	/*
	 * initialize weight and threshold
	 */
	for (i = 0; i < INPUT_VECTOR_NUM; i++)
	{
		for (j = 0; j < HIDN_VECTOR_NUM; j++)
		{
			in_hidn_wet[i][j] = frand();
		}
	}
	for (i = 0; i < HIDN_VECTOR_NUM; i++)
	{
		for (j = 0; j < OUTPUT_VECTOR_NUM; j++)
		{
			hidn_out_wet[i][j] = frand();
		}
	}
	for (i = 0; i < HIDN_VECTOR_NUM; i++)
	{
		hidn_thresh[i] = frand();
	}
	for (i = 0; i < OUTPUT_VECTOR_NUM; i++)
	{
		out_thresh[i] = frand();
	}
}

void forward(const float* const input_vector,
				float* const hidn_vector,
				float* const output_vector,
				float** const in_hidn_wet,
				float** const hidn_out_wet,
				float* const hidn_thresh,
				float* const out_thresh)
{
	float sum = 0.0;
	int i = 0;
	int j = 0;

	/*
	 * compute the output of each hidden unit.
	 */
	for (j = 0; j < HIDN_VECTOR_NUM; j++)
	{
		sum = 0.0;
		for (i = 0; i < INPUT_VECTOR_NUM; i++)
		{
			sum += in_hidn_wet[i][j] * input_vector[i];
		}
		hidn_vector[j] = 1 / (1 + exp(-(sum + hidn_thresh[j])));
	}

	/*
	 * compute the output of each output unit
	 */
	for (j = 0; j < OUTPUT_VECTOR_NUM; j++)
	{
		sum = 0.0;
		for (i = 0; i < HIDN_VECTOR_NUM; i++)
		{
			sum += hidn_out_wet[i][j] * hidn_vector[i];
		}
		output_vector[j] = 1 / (1 + exp(-(sum + out_thresh[j])));
	}
}

/*
 * back propagation algorithm
 */
void back_propagate(float* input_vector,
					float* hidn_vector,
					float* output_vector,
					float* expt_output_vector,
					float** in_hidn_wet,
					float** hidn_out_wet,
					float* hidn_thresh,
					float* out_thresh)
{
	int i = 0;
	int j = 0;
	int k = 0;
	float sum = 0.0;
	float out_err[OUTPUT_VECTOR_NUM] = {0.0}; /* output layer error */
	float hidn_err[HIDN_VECTOR_NUM] = {0.0}; /* hidden layer error */

	/*
	 * compute error for each output unit
	 */
	for (j = 0; j < OUTPUT_VECTOR_NUM; j++)
	{
		out_err[j] = output_vector[j] * (1 - output_vector[j])\
				* (expt_output_vector[j] - output_vector[j]);
	}
	/*
	 * compute error for each hidden unit
	 */
	for (j = 0; j < HIDN_VECTOR_NUM; j++)
	{
		sum = 0.0;
		for (k = 0; k < OUTPUT_VECTOR_NUM; k++)
		{
			sum += out_err[k] * hidn_out_wet[j][k];
		}
		hidn_err[j] = hidn_vector[j] * (1 - hidn_vector[j]) * sum;
	}


	/*
	 * update weight in the network
	 */
	for (i = 0; i < INPUT_VECTOR_NUM; i++)
	{
		for (j = 0; j < HIDN_VECTOR_NUM; j++)
		{
			in_hidn_wet[i][j] += LEARN_RATE * hidn_err[j] * input_vector[i];
		}
	}
	for (j = 0; j < HIDN_VECTOR_NUM; j++)
	{
		for (k = 0; k < OUTPUT_VECTOR_NUM; k++)
		{
			hidn_out_wet[j][k] += LEARN_RATE * out_err[k] * hidn_vector[j];
		}
	}

	/*
	 * update bias in network
	 */
	for (j = 0; j < HIDN_VECTOR_NUM; j++)
	{
		hidn_thresh[j] += (LEARN_RATE * hidn_err[j]);
	}
	for (k = 0; k < OUTPUT_VECTOR_NUM; k++)
	{
		out_thresh[k] += LEARN_RATE * hidn_err[k];
	}
}
