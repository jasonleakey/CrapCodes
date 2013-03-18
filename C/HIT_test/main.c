/*
 *  Establishment date:  2009-3-8
 *  Author            :	 jasonleakey
 *  Copyleft (R) 2009-3-8 jasonleakey
 *  <jasonleakey2005@gmail.com>
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
 *  main.c: all the following is HIT C program language tests in HIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_STR_LEN 82	//the 0 is not used and 82 for '\n'

#define PRINT_MENU\
	printf("41. 2004-1\n"\
		   "42. 2004-2\n"\
		   "43. 2004-3\n"\
		   "44. 2004-4\n"\
		   "45. 2004-5\n"\
		   "46. 2004-6\n"\
		   "51. 2005-1\n"\
		   "52. 2005-1\n"\
		   "53. 2005-3\n"\
		   "54. 2005-4\n"\
		   "55. 2005-5\n"\
		   "56. 2005-6\n"\
		   "57. 2005-7\n"\
		   "58. 2005-8\n"\
		   "59. 2005-9\n"\
		   "510.2005-10\n"\
		   "0.  exit\n"\
		   "Select:");

int test_04_1(void)
{
	int nMax = 0;
	int nCur = 0;
	int i = 0;
	printf("Input ten positive integer:");
	for (i = 0; i < 10; i++)
	{
		//input current number
		while (1 != scanf("%d%*c", &nCur) && nCur != EOF)
		{
			while ('\n' != getchar())
			{
				NULL;
			}
		}
		if (EOF == nCur)
		{
			return -1;
		}
		//compare with max num
		if (nCur > nMax)
		{
			nMax = nCur;
		}
	}
	printf("The max num is %d\n", nMax);

	return 0;
}

int test_04_2(void)
{
	int nSum = 0;
	int nCur = 0;
	int i = 0;
	printf("Input 100 nums:");
	for (i = 0; i < 100; i++)
	{
		while (1 != scanf("%d%*c", &nCur) && nCur != EOF)
		{
			while ('\n' == getchar())
			{
				NULL;
			}
		}
		if (EOF == nCur)
		{
			return -1;
		}
		nSum += nCur;
	}
	printf("The average is %0.2f\n", (float)nSum / 100);

	return 0;
}

int test_04_3(void)
{
	int year = 0;
	printf("Input year:");
	while (1 != scanf("%d%*c", &year) && year != EOF)
	{
		while ('\n' != getchar())
		{
			NULL;
		}
	}
	if (year < 0)
	{
		printf("Input Error!\n");
		return -1;
	}
	if ((0 == year % 4 && 0 != year % 100) || 0 == year % 400)
	{
		printf("%d is a leap year!\n", year);
	}
	else
	{
		printf("%d is not a leap year!\n", year);
	}
	return 0;
}

int test_04_4(void)
{
	int num = 0;
	int j = 0;	//separate a unit
	int sum = 0;
	for (num = 100; num < 1000; num++)
	{
		sum = 0;
		j = num / 100;
		sum += j * j * j;
		j = (num % 100) / 10;
		sum += j * j * j;
		j = num % 10;
		sum += j * j * j;
		if (sum == num)
		{
			printf("%d is a daffodil num\n", num);
		}
	}
	return 0;
}

int test_04_5(void)
{
	int x = 0;
	printf("Input x:");
	while (1 != scanf("%d%*c", &x) && x != EOF)
	{
		while ('\n' != getchar())
		{
			NULL;
		}
	}
	if (x < 1)
	{
		printf("y = %d", x);
	}
	else if (x >= 1 && x < 10)
	{
		printf("y = %d", 2 * x - 1);
	}
	else if (x >= 10)
	{
		printf("y = %d", 3 * x - 11);
	}
	return 0;
}

int test_04_6(void)
{
	int i = 1;
	long long sum = 0;
	for (i = 1; i < 100; i += 2)
	{
		sum += i * (i + 1) * (i + 2);
	}
	printf("1*2*3+3*4*5+...+99*100*101=%lld\n", sum);
	return 0;
}

int test_05_1(void)
{
	//sort by selection
	int nScore[10] = {0};
	int i = 0;
	int j = 0;
	int k = 0;
	int max = 0;
	printf("Input ten scores:");
	for (i = 0; i < 10; i++	)
	{
		while (1 != scanf("%d%*c", &nScore[i]) && nScore[i] != EOF)
		{
			while ('\n' != getchar())
			{
				NULL;
			}
		}
	}
	for (i = 0; i < 10; i++	)
	{
		max = nScore[i];
		k = i;
		for (j = i + 1; j < 10; j++)
		{
			if (nScore[j] > max)
			{
				max = nScore[j];
				k = j;
			}
		}
		if (k != i)
		{//exchange nScore[i] and the max value nScore[k]
			nScore[k] ^= nScore[i];
			nScore[i] ^= nScore[k];
			nScore[k] ^= nScore[i];
		}
	}
	printf("After sorted:");
	for (i = 0; i < 10; i++)
	{
		printf("%d ", nScore[i]);
	}
	printf("\n");
	return 0;
}

int test_05_2(void)
{
	int A[3][4] = {0};
	int B[4][3] = {0};
	int i = 0;
	int j = 0;
	//set a seed
	srand(time((time_t*)NULL));

	printf("before transposition, A:\n");
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			//create a random integer
			A[i][j] = rand() % 30;
			printf("%3d", A[i][j]);
		}
		printf("\n");
	}

	printf("After transposition B:\n");
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			B[i][j] = A[j][i];
		}
	}

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			printf("%3d", B[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int test_05_3(void)
{
	char s[MAX_STR_LEN];
	int nStrLen;
	int i;
	//get the string from stdin and store it into s
	//the s[0] is not used
	fgets(s, MAX_STR_LEN, stdin);
	nStrLen = strlen(s);
	if (0 == nStrLen)
	{
		printf("None is input!\n");
		return -1;
	}

	//


	return 0;
}

int main(int argc, char **argv)
{
	int nSel = 0;
	//do loop forever until user press CTRL+D
	//or select 0 to exit
	for (;;)
	{
		PRINT_MENU;
		while (1 != scanf("%d%*c", &nSel) && nSel != EOF)
		{
			while ('\n' != getchar())
			{
				NULL;
			}
		}
		switch (nSel)
		{
			case 0:
				exit(0);
			case 41:
				printf("Test 2004-1\n");
				test_04_1();
				break;
			case 42:
				printf("Test 2004-2\n");
				test_04_2();
				break;
			case 43:
				printf("Test 2004-3\n");
				test_04_3();
				break;
			case 44:
				printf("Test 2004-4\n");
				test_04_4();
				break;
			case 45:
				printf("Test 2004-5\n");
				test_04_5();
				break;
			case 46:
				printf("Test 2004-6\n");
				test_04_6();
				break;
			case 51:
				printf("Test 2005-1\n");
				test_05_1();
				break;
			case 52:
				printf("test 2005-2\n");
				test_05_2();
				break;
			case 53:
				printf("test 2005-3\n");
				test_05_3();
				break;
			default:
				printf("illegal input!\n");
				break;
		}
		printf("press ENTER to continue...\n");
		getchar();
	}

	return 0;
}

