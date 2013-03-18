/*
 * main.c
 *
 *  Created on: 2008-10-27
 *      Author: jasonleakey
 */

#include <stdio.h>
#include <stdlib.h>
#include "bilink.h"

Status direct_insert_sort(BiLink *pL)
{
	if ((*pL) == NULL)
	{
		return ERROR;
	}
	else if ((*pL)->next == NULL)
	{
		;
	}
	else
	{
		BiLink p;
		p = (*pL)->next->next;
		while(NULL != p)
		{
			if (p->data <= p->data)
			{
				BiLink q, t = p->next;
				for (q = p->pre; q->data > p->data; q = q->pre)
				{
					;
				}
				p->pre->next = t;
				if (NULL != t)
				{
					t->pre = p->pre;
				}
				p->next = q->next;
				p->pre = q;
				q->next->pre = p;
				q->next = p;
				p = t;
				printf("p->data = %c,q->data = %c, t->data = %c", p->data, q->data, t->data);
			}
		}
	}
	return OK;
}

int main()
{
	char str[] = "jasonleakey";
	BiLink L = (BiLink)malloc(sizeof(BiNode));
	BiLink p = L;
	BiLink q;
	int i;
	if (L == NULL)
	{
		printf("No memory for L!\n");
		exit(1);
	}
	L->data = '0';
	L->next = L->pre = NULL;
	for (i = 0; 0 != str[i]; i++)
	{
		q = (BiLink)malloc(sizeof(BiNode));
		if (NULL == q)
		{
			printf("No memory for q!\n");
			exit(1);
		}
		q->data = str[i];
		q->next = NULL;
		q->pre = p;
		p->next = q;
		p = q;
	}
	printf("排序前:");
	for (p = L->next; NULL != p; p = p->next)
	{
		printf("%c", p->data);
	}
	printf("\n");
	direct_insert_sort(&L);
	printf("排序后:");
	for (p = L->next; NULL != p; p = p->next)
	{
		printf("%c", p->data);
	}
	printf("\n");
	for (p = L, q = L->next; q != NULL; q = q->next)
	{
		q = p->next;
		free(p);
		p = NULL;
		p = q;
	}
	return 0;
}
