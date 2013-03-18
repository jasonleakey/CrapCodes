/*
 *      test_memory_struct.c
 *
 *      Copyright 2008 jasonleakey <jasonleakey@jasonleakey-laptop>
 *
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
#include <malloc.h>
#include <unistd.h>

/*
 * 内存结构如下:
 * Code Segment:
 * 		print_hello  	:0x08048414		| 低地址
 * 		main	     	:0x0804842D		|
 * 		print_goodbye	:0x0804862C		|
 *
 * Data Segment:
 * 		data_var_start	:0x08049a94
 * 		data_var_end	:0x08049a98
 * 							空一字
 * BSS  Segment:
 * 		bss_var_start	:0x08049AA0
 * 		bss_var_end		:0x08049AA4
 *
 *
 *
 * Heap Segment:
 * 		heap_start		:0x0804A008
 * 		heap_end		:0x0804A020
 *
 *
 * Stack Segment:
 * 		start_end		:0xBF9941CC
 * 		stack_start		:0xBF9941D0		| 高地址
 *
 *
 */

int bss_var1;
int bss_var2;
int data_var0 = 1;

int print_hello(void)
{
	printf("hello!\n");
	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	int print_goodbye(void);
	printf("below are addresses of types of process's mem\n");
	printf("Text location:\n");
	printf("%#x\n", &"55");
	printf("\tAddress of main(Code Segment):%p\n", main);
	printf("\tAddress of print_hello(Code Segment):%p\n", print_hello);
	printf("\tAddress of print_goodbye(Code Segment):%p\n", print_goodbye);

	printf("____________________________\n");
	int stack_var0 = 2;
	printf("Stack Location:\n");
	printf("\tInitial end of stack:%p\n", &stack_var0);

	int stack_var1 = 3;
	printf("\tnew end of stack:%p\n", &stack_var1);

	printf("____________________________\n");
	printf("Data Location:\n");
	printf("\tAddress of data_var(Data Segment):%p\n", &data_var0);
	static int data_var1 = 4;
	printf("\tNew end of data_var(Data Segment):%p\n", &data_var1);

	printf("____________________________\n");
	printf("BSS Location:\n");
	printf("\tthe content between Data and BSS is %x\n", *(&bss_var1 - 1));
	printf("\tInitial Address of bss:%p\n", &bss_var1);
	printf("\tNew address of bss:%p\n", &bss_var2);

	printf("____________________________\n");
	char *p_start = (char *) malloc(sizeof(char) * 20);
	printf("Heap Location:\n");
	printf("\tInitial end of heap:%p\n", p_start);

	int *p_end = (int *) malloc(sizeof(int) * 10);
	printf("\tNew end of heap:%p\n", p_end);

	printf("\taddress of &p_start is %p\n", &p_start);
	printf("\taddress of &p_end is %p", &p_end);

	free(p_start);
	free(p_end);
	p_start = NULL;
	p_end = NULL;
	return 0;
}

int print_goodbye(void)
{
	printf("Goodbye!\n");
	return EXIT_SUCCESS;
}
