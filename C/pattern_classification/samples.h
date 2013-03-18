/*
 *  C_pattern_classification - training samples and test samples header
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
 */

#ifndef SAMPLES_H_
#define SAMPLES_H_

#include <errno.h>
#include <string.h>

#define LABEL_MAGIC_NUMBER 0x00000801
#define IMAGE_MAGIC_NUMBER 0x00000803
#define ROWS 28
#define COLUMNS 28
#define INPUT_VECTOR_NUM (ROWS * COLUMNS) /* the length of input vector */
#define HIDN_VECTOR_NUM 100 /* the length of hidden nodes */
#define OUTPUT_VECTOR_NUM 4 /* the length of output vector */
#define TRAIN_SAMPLE_NUM 60000
#define TEST_SAMPLE_NUM 10000
#define LEARN_RATE 0.8

typedef struct {
	int m_nMagicNum;
	unsigned int m_nImgNum;
	unsigned int m_nRow;
	unsigned int m_nCol;
} ImageHeader;

typedef struct {
	int m_nMagicNum;
	unsigned int m_nItemNum;
} LabelHeader;

typedef struct {
	ImageHeader imghd;
	unsigned char img[TRAIN_SAMPLE_NUM][ROWS][COLUMNS];
} TrainImg;

typedef struct {
	ImageHeader imghd;
	unsigned char img[TEST_SAMPLE_NUM][ROWS][COLUMNS];
} TestImg;

typedef struct {
	LabelHeader labhd;
	unsigned char label[TRAIN_SAMPLE_NUM];
} TrainLabel;

typedef struct {
	LabelHeader labhd;
	unsigned char label[TEST_SAMPLE_NUM];
} TestLabel;



#endif /* SAMPLES_H_ */
