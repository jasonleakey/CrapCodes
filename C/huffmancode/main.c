/*
 * 		文件名称:	main.c
 * 		创建时间:	2008-12-18
 * 		程序作者:	jasonleakey
 * 		当前版本:	1.0
 * 		Copyright 2008 jasonleakey
 * 		<jasonleakey@sohu.com>
 * 		<QQ:174481438>
 * 		--------------------------------------------------------------------
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "huffmantree.h"

//Function use:
int min1(HuffmanTree t, int i)
{
	int j;
	int flag;
	unsigned int k = UINT_MAX;
	for (j = 1; j <= i; j++)
	{
		if (t[j].weight < k && 0 == t[j].parent)
		{
			k = t[j].weight;
			flag = j;
		}
	}
	t[flag].parent = 1;
	return flag;
}

void select1(HuffmanTree t, int i, int *s1, int *s2)
{
	int j;
	*s1 = min1(t, i);
	*s2 = min1(t, i);
	if (*s1 > *s2)
	{
		j = *s1;
		*s1 = *s2;
		*s2 = j;
	}
}

void HuffmanCoding_up(HuffmanTree *HT, HuffmanCode *HC, int *w, int n)
{
	int total_node_num;
	int i;
	int s1;
	int s2;
	int start;
	unsigned int c;
	unsigned int f;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
	{
		return;
	}
	//建立诸结点
	total_node_num = 2 * n - 1;
	*HT = (HuffmanTree) malloc((total_node_num + 1) * sizeof(HTNode));//0号单元未用
	if (NULL == cd)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	for (p = *HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{
		(*p).weight = *w;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	w = w - n;
	for (; i <= total_node_num; i++, p++)
	{
		(*p).parent = 0;
	}
	//建huffman树
	for (i = n + 1; i <= total_node_num; i++)
	{
		select1(*HT, i - 1, &s1, &s2);
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1;
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	//从叶子到根求每个字符的huffman编码
	*HC = (HuffmanCode) malloc((n + 1) * sizeof(HuffmanCNode));//0号单元不用
	if (NULL == cd)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	cd = (char *) malloc(n * sizeof(char));
	if (NULL == cd)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	cd[n - 1] = '\0';
	//逐个字符求huffman编码
	for (i = 1; i <= n; i++)
	{
		start = n - 1; //编码结点符位置
		for (c = i, f = (*HT)[i].parent; 0 != f; c = f, f = (*HT)[f].parent)
		{
			if (c == (*HT)[f].lchild)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		//为第i个字符编码分配空间
		(*HC)[i].weight = *w++;
		(*HC)[i].code = (char *) malloc((n - start) * sizeof(char));
		if (NULL == (*HC)[i].code)
		{
			perror("OVERFLOW");
			exit(EXIT_FAILURE);
		}
		strcpy((*HC)[i].code, &cd[start]);
	}
	free(cd);
}

//Function use: 从根结点起,遍历到叶子结点,求得huffman编码,huffman树HT已经求得
void HuffmanCoding_down(HuffmanTree *HT, HuffmanCode *HD, int* w, int n)
{
	int i;
	int total_node_num = 2 * n - 1;
	*HD = (HuffmanCode) malloc((n + 1) * sizeof(HuffmanCNode));
	if (NULL == *HD)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	char* cd = (char *) malloc(n * sizeof(char));
	if (NULL == cd)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	int c = total_node_num;
	int cdlen = 0;
	for (i = 1; i <= total_node_num; ++i)
	{
		(*HT)[i].weight = 0; //非叶子结点权值为0,作为标志
	}
	//应该是回溯法遍历huffman树,求得所有根结点到叶子结点的路径
	while (0 != c)
	{
		if (0 == (*HT)[c].weight) //如果是第一次访问
		{
			(*HT)[c].weight = 1;
			if (0 != (*HT)[c].lchild)
			{
				c = (*HT)[c].lchild;
				cd[cdlen++] = '0';
			}
			else if (0 == (*HT)[c].rchild)
			{
				(*HD)[c].code = (char*)malloc((cdlen + 1) * sizeof(char));
				if (NULL == (*HD)[c].code)
				{
					perror("OVERFLOW");
					exit(EXIT_FAILURE);
				}
				(*HD)[c].weight = c;
				cd[cdlen] = '\0';
				strcpy((*HD)[c].code, cd);
			}
		}
		else if (1 == (*HT)[c].weight)	//如果是第二次访问
		{
			(*HT)[c].weight = 2;
			if (0 != (*HT)[c].rchild)
			{
				c = (*HT)[c].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			(*HT)[c].weight = 0;  //回溯上一层
			c = (*HT)[c].parent;
			--cdlen;
		}
	}
	free(cd);
}

int main(int argc, char **argv)
{
	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCode HD;
	int *w;
	int n;
	int i;
	printf("请输入权值的个数(>1):");
	scanf("%d", &n);
	w = (int *) malloc(n * sizeof(int));
	if (NULL == w)
	{
		perror("OVERFLOW");
		exit(EXIT_FAILURE);
	}
	printf("请依次输入%d个不同权值(int):", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", w + i);
	}
	HuffmanCoding_up(&HT, &HC, w, n);
	printf("叶子到根的顺序\n");
	printf("权值---编码\n");
	for (i = 1; i <= n; i++)
	{
		printf("%4d---%s\n", HC[i].weight, HC[i].code);
	}
	printf("根到叶子的顺序\n");
	HuffmanCoding_down(&HT, &HD, w, n);
	printf("权值---编码\n");
	for (i = 1; i <= n; i++)
	{
		printf("%4d---%s\n", HD[i].weight, HC[i].code);
	}
	free(HC);
	free(HD);
	free(HT);
	free(w);
	w = NULL;
	return EXIT_SUCCESS;
}

