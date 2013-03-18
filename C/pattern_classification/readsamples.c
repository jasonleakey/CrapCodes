/*
 *  C_pattern_classification - TODO
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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "samples.h"

/*
 * change a big endian integer to a little endian one
 */
#define B2L_INT32(A) (A = (((unsigned int)(A) & 0xff000000) >> 24) | \
                   (((unsigned int)(A) & 0x00ff0000) >> 8) | \
                   (((unsigned int)(A) & 0x0000ff00) << 8) | \
                   (((unsigned int)(A) & 0x000000ff) << 24))

void get_train_label(TrainLabel* train_label)
{
	FILE* fp = NULL;
	int nReadSize = 0;
	if (NULL == (fp = fopen("./train-labels.idx1-ubyte", "r")))
	{
		fprintf(stderr, "fopen:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(1);
	}
	if ((nReadSize = fread(train_label, sizeof(TrainLabel), 1, fp)) < 1)
	{
		ferror(fp);
		fprintf(stderr, "fread:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	B2L_INT32(train_label->labhd.m_nMagicNum);
	B2L_INT32(train_label->labhd.m_nItemNum);

	if (train_label->labhd.m_nMagicNum != LABEL_MAGIC_NUMBER)
	{
		fprintf(stderr, "illege LABEL_MAGIC_NUMBER:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}
	fclose(fp);
}

void get_train_image(TrainImg* train_image)
{
	FILE* fp = NULL;
	int nReadSize = 0;
	if (NULL == (fp = fopen("./train-images.idx3-ubyte", "r")))
	{
		fprintf(stderr, "fopen:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(1);
	}
	if ((nReadSize = fread(train_image, sizeof(TrainImg), 1, fp)) < 1)
	{
		ferror(fp);
		fprintf(stderr, "fread:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	B2L_INT32(train_image->imghd.m_nMagicNum);
	B2L_INT32(train_image->imghd.m_nImgNum);
	B2L_INT32(train_image->imghd.m_nRow);
	B2L_INT32(train_image->imghd.m_nCol);

	if (train_image->imghd.m_nMagicNum != IMAGE_MAGIC_NUMBER\
		|| train_image->imghd.m_nImgNum != TRAIN_SAMPLE_NUM\
		|| train_image->imghd.m_nRow != ROWS\
		|| train_image->imghd.m_nCol != COLUMNS)
	{
		fprintf(stderr, "illegal IMAGE_MAGIC_NUMBER:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	fclose(fp);
}

void get_test_label(TestLabel* test_label)
{
	FILE* fp = NULL;
	int nReadSize = 0;
	if (NULL == (fp = fopen("./t10k-labels.idx1-ubyte", "r")))
	{
		fprintf(stderr, "fopen:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(1);
	}
	if ((nReadSize = fread(test_label, sizeof(TestLabel), 1, fp)) < 1)
	{
		ferror(fp);
		fprintf(stderr, "fread:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	B2L_INT32(test_label->labhd.m_nMagicNum);
	B2L_INT32(test_label->labhd.m_nItemNum);

	if (test_label->labhd.m_nMagicNum != LABEL_MAGIC_NUMBER)
	{
		fprintf(stderr, "illege LABEL_MAGIC_NUMBER:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}
	fclose(fp);
}

void get_test_image(TestImg* test_image)
{
	FILE* fp = NULL;
	int nReadSize = 0;
	if (NULL == (fp = fopen("./t10k-images.idx3-ubyte", "r")))
	{
		fprintf(stderr, "fopen:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		exit(1);
	}
	if ((nReadSize = fread(test_image, sizeof(TestImg), 1, fp)) < 1)
	{
		ferror(fp);
		fprintf(stderr, "fread:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	B2L_INT32(test_image->imghd.m_nMagicNum);
	B2L_INT32(test_image->imghd.m_nImgNum);
	B2L_INT32(test_image->imghd.m_nRow);
	B2L_INT32(test_image->imghd.m_nCol);

	if (test_image->imghd.m_nMagicNum != IMAGE_MAGIC_NUMBER\
		|| test_image->imghd.m_nImgNum != TEST_SAMPLE_NUM\
		|| test_image->imghd.m_nRow != ROWS\
		|| test_image->imghd.m_nCol != COLUMNS)
	{
		fprintf(stderr, "illegal IMAGE_MAGIC_NUMBER:%s, Line %d in %s\n", strerror(errno),\
				__LINE__, __FILE__);
		fclose(fp);
		exit(1);
	}

	fclose(fp);
}
